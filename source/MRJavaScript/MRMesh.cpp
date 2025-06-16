#include <string>
#include <vector>
#include <memory>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRExpected.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRVectorTraits.h>
#include <MRMesh/MRMeshFillHole.h>

#include "MRMesh.h"

using namespace emscripten;
using namespace MR;

namespace MRJS
{

// ------------------------------------------------------------------------
// `Mesh`
// ------------------------------------------------------------------------
// Convert C++ vector to JavaScript Float32Array
val vector3fToFloat32Array( const std::vector<Vector3f>& vec )
{
	// REF: [Memory Views](`https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html#memory-views`)
	return val( typed_memory_view( vec.size() * 3, reinterpret_cast< const float* >( vec.data() ) ) );
}

EMSCRIPTEN_BINDINGS( MeshModule )
{
	class_<Mesh>( "Mesh" )
		.constructor<>()
		.function( "signedDistance", select_overload<float( const Vector3f& ) const>( &Mesh::signedDistance ) );

	function( "computeVertexNormals", +[] ( const Mesh& mesh )
	{
		std::vector<Vector3f> normals;
		for ( VertId v{ 0 }; v < mesh.topology.vertSize(); ++v )
		{
			if ( mesh.topology.hasVert( v ) )
			{
				normals.push_back( mesh.normal( v ) );
			}
		}
		return vector3fToFloat32Array( normals );
	} );
}


// ------------------------------------------------------------------------
// Wrappers for `Mesh`
// ------------------------------------------------------------------------
// Helper function to create Vector3f from JavaScript array
Vector3f arrayToVector3f( const val& arr )
{
	return Vector3f( arr[0].as<float>(), arr[1].as<float>(), arr[2].as<float>() );
}

// Helper function to convert Vector3f to JavaScript array
val vector3fToArray( const Vector3f& v )
{
	val arr = val::array();
	arr.set( 0, v.x );
	arr.set( 1, v.y );
	arr.set( 2, v.z );
	return arr;
}

// Helper function to convert Box3F to JavaScript object
val box3fToObject( const Box<Vector3<float>>& box )
{
	val obj = val::object();
	obj.set( "min", vector3fToArray( box.min ) );
	obj.set( "max", vector3fToArray( box.max ) );
	return obj;
}

// Wrapper class for Mesh to provide JavaScript-friendly interface
MeshWrapper::MeshWrapper( const Mesh& m ) : mesh( m )
{
}

// Static factory methods for creating meshes from various sources
val MeshWrapper::fromTriangles( const val& vertexCoords, const val& triangles )
{
	try
	{
		// Convert JavaScript arrays to C++ vectors
		VertCoords coords;
		int numVerts = vertexCoords["length"].as<int>();
		coords.resize( numVerts );

		for ( int i = 0; i < numVerts; ++i )
		{
			val vertex = vertexCoords[i];
			coords[VertId( i )] = arrayToVector3f( vertex );
		}

		// Convert triangles array
		Triangulation triangulation;
		int numTris = triangles["length"].as<int>();

		for ( int i = 0; i < numTris; ++i )
		{
			val tri = triangles[i];
			triangulation.push_back( {
				VertId( tri[0].as<int>() ),
				VertId( tri[1].as<int>() ),
				VertId( tri[2].as<int>() )
			} );
		}

		auto mesh = Mesh::fromTriangles( std::move( coords ), triangulation );
		val result = val::object();
		result.set( "success", true );
		result.set( "mesh", MeshWrapper( mesh ) );

		return result;
	}
	catch ( const std::exception& e )
	{
		val result = val::object();
		result.set( "success", false );
		result.set( "error", std::string( e.what() ) );

		return result;
	}
}

// Geometric queries
val MeshWrapper::getBoundingBox() const
{
	return box3fToObject( mesh.getBoundingBox() );
}

val MeshWrapper::getVertexPosition( int vertId ) const
{
	if ( vertId >= 0 && vertId < ( int )mesh.points.size() )
	{
		return vector3fToArray( mesh.points[VertId( vertId )] );
	}
	return val::null();
}

void MeshWrapper::setVertexPosition( int vertId, const val& position )
{
	if ( vertId >= 0 && vertId < ( int )mesh.points.size() )
	{
		mesh.points[VertId( vertId )] = arrayToVector3f( position );
		mesh.invalidateCaches(); // Important: invalidate caches after modification
	}
}

int MeshWrapper::getVertexCount() const
{
	return ( int )mesh.topology.lastValidVert() + 1;
}

int MeshWrapper::getFaceCount() const
{
	return ( int )mesh.topology.lastValidFace() + 1;
}

double MeshWrapper::getVolume() const
{
	return mesh.volume();
}

double MeshWrapper::getArea() const
{
	return mesh.area();
}

val MeshWrapper::findCenter() const
{
	return vector3fToArray( mesh.findCenterFromBBox() );
}

// Face operations
val MeshWrapper::getFaceVertices( int faceId ) const
{
	if ( faceId >= 0 && faceId < ( int )mesh.topology.lastValidFace() + 1 )
	{
		FaceId f( faceId );
		if ( mesh.topology.hasFace( f ) )
		{
			val result = val::array();
			EdgeId e = mesh.topology.edgeWithLeft( f );

			for ( int i = 0; i < 3; ++i )
			{ // Assuming triangular faces
				result.set( i, ( int )mesh.topology.org( e ) );
				e = mesh.topology.next( e );
			}
			return result;
		}
	}
	return val::null();
}

val MeshWrapper::getFaceNormal( int faceId ) const
{
	if ( faceId >= 0 && faceId < ( int )mesh.topology.lastValidFace() + 1 )
	{
		FaceId f( faceId );
		if ( mesh.topology.hasFace( f ) )
		{
			return vector3fToArray( mesh.normal( f ) );
		}
	}
	return val::null();
}

val MeshWrapper::fillHoles() const
{
	auto holeEdges = mesh.topology.findHoleRepresentiveEdges();
	Mesh meshCopy = mesh;
	for ( EdgeId e : holeEdges )
	{
		FillHoleParams params;
		fillHole( meshCopy, e, params );
	}

    // === Export point data ===
	auto _points = meshCopy.points;
	size_t pointCount = _points.size();
	size_t totalPointElements = pointCount * 3;
    const float* pointData = reinterpret_cast<const float*>(_points.data());

    // Create a JavaScript array directly and populate it - avoiding intermediate conversion steps
    val pointsArray = val::array();
    // Pre-allocate the array length to improve performance
    pointsArray.set("length", totalPointElements);
    // Batch setting values - faster than pushing them one by one
    for (size_t i = 0; i < totalPointElements; ++i) {
        pointsArray.set(i, val(pointData[i]));
    }

    // === Export triangle data ===
	Triangulation _tri = meshCopy.topology.getTriangulation();
	size_t triangleCount = _tri.size();
	size_t totalTriElements = triangleCount * 3; // Each triangle has three indexes
	const int* triData = reinterpret_cast<const int*>(_tri.data());

	val triangleArray = val::array();
    triangleArray.set("length", totalTriElements);
	for (size_t i = 0; i < totalTriElements; ++i) {
		triangleArray.set(i, val(triData[i]));
	}
	
    val meshData = val::object();
    meshData.set("vertices", pointsArray);
    meshData.set("vertexCount", pointCount);
    meshData.set("indices", triangleArray);
    meshData.set("triangleCount", triangleCount);

    return meshData;
}

// Point projection
val MeshWrapper::projectPoint( const val& point, float maxDistance ) const
{
	Vector3f p = arrayToVector3f( point );
	MeshProjectionResult result = mesh.projectPoint( p, maxDistance * maxDistance ); // Note: function expects squared distance

	if ( result.valid() )
	{
		val obj = val::object();
		obj.set( "success", true );
		// obj.set( "point", vector3fToArray( result.proj ) );
		// obj.set( "faceId", ( int )result->face );
		// obj.set( "distance", std::sqrt( result->distSq ) );
		return obj;
	}
	else
	{
		val result = val::object();
		result.set( "success", false );
		result.set( "error", "No projection found within distance" );

		return result;
	}
}

// Transformation
void MeshWrapper::transform( const val& matrix )
{
	// Assuming 4x4 transformation matrix as flat array of 16 elements
	if ( matrix["length"].as<int>() == 16 )
	{
		AffineXf3f xf;
		// Fill transformation matrix from JavaScript array
		for ( int i = 0; i < 4; ++i )
		{
			for ( int j = 0; j < 4; ++j )
			{
				if ( i < 3 && j < 3 )
				{
					xf.A[i][j] = matrix[i * 4 + j].as<float>();
				}
				else if ( i < 3 && j == 3 )
				{
					xf.b[i] = matrix[i * 4 + j].as<float>();
				}
			}
		}
		mesh.transform( xf );
	}
}

// Pack mesh (optimize memory layout)
void MeshWrapper::pack()
{
	mesh.pack();
}


EMSCRIPTEN_BINDINGS( MeshWrapperModule )
{
	class_<MeshWrapper>( "MeshWrapper" )
		.constructor<>()
		.constructor<const Mesh&>()
		.class_function( "fromTriangles", &MeshWrapper::fromTriangles )

		// Geometric properties
		.function( "getBoundingBox", &MeshWrapper::getBoundingBox )
		.function( "getVertexCount", &MeshWrapper::getVertexCount )
		.function( "getFaceCount", &MeshWrapper::getFaceCount )
		.function( "getVolume", &MeshWrapper::getVolume )
		.function( "getArea", &MeshWrapper::getArea )
		.function( "findCenter", &MeshWrapper::findCenter )

		// Vertex operations
		.function( "getVertexPosition", &MeshWrapper::getVertexPosition )
		.function( "setVertexPosition", &MeshWrapper::setVertexPosition )

		// Face operations
		.function( "getFaceVertices", &MeshWrapper::getFaceVertices )
		.function( "getFaceNormal", &MeshWrapper::getFaceNormal )

		.function( "fillHoles", &MeshWrapper::fillHoles )

		// Spatial queries
		.function( "projectPoint", &MeshWrapper::projectPoint )

		// Transformations
		.function( "transform", &MeshWrapper::transform )
		.function( "pack", &MeshWrapper::pack );
}

} //namespace MRJS
