#include <string>
#include <vector>
#include <memory>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRExpected.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRVectorTraits.h>
#include <MRMesh/MRMeshFillHole.h>
#include <MRVoxels/MRFixUndercuts.h>
#include <MRMesh/MRSurroundingContour.h>
#include <MRMesh/MRFillContourByGraphCut.h>
#include <MRMesh/MREdgeMetric.h>

#include "MRMesh.h"
#include "MRUtils.h"
#include "MREdgeMetric.h"

using namespace emscripten;
using namespace MR;

namespace MRJS
{

// Convert C++ vector to JavaScript Float32Array
val vector3fToFloat32Array( const std::vector<Vector3f>& vec )
{
	// REF: [Memory Views](`https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html#memory-views`)
	return val( typed_memory_view( vec.size() * 3, reinterpret_cast< const float* >( vec.data() ) ) );
}

EMSCRIPTEN_BINDINGS( MeshModule )
{
	// ------------------------------------------------------------------------
	// Bindings for `Mesh`
	// ------------------------------------------------------------------------
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


// ------------------------------------------------------------------------
// Wrappers for `Mesh`
// ------------------------------------------------------------------------
MeshWrapper::MeshWrapper( const Mesh& m ) : mesh( m ) {}

Mesh* MeshWrapper::getMeshPtr() { return &mesh; }

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
// val MeshWrapper::fromTrianglesMemoryView( const float* vertexPtr,
// 										  size_t        numVerts,
// 										  const uint32_t* triPtr,
// 										  size_t         numTris )
// {

// }

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

val MeshWrapper::segmentByPoints(
	const std::vector<float>& coordinates, const std::vector<float>& dir,
	const EdgeMetricWrapper& edgeMetricWrapper )
{
	val result = val::object();

	// TODO: More performance gains? 
	Mesh meshCopy;
	meshCopy.topology = mesh.topology;
	meshCopy.points = mesh.points;

	// Input validation
	if ( meshCopy.points.empty() )
	{
		result.set( "success", false );
		result.set( "error", std::string( "Mesh not initialized!" ) );

		return result;
	}

	try
	{
		auto edgeMetric_ = edgeMetricWrapper.getMetric();
		// Parse coordinates into Vector3f points
		std::vector<Vector3f> inputPoints = MRJS::parseJSCoordinates( coordinates );

		if ( inputPoints.size() < 2 )
		{
			result.set( "success", false );
			result.set( "error", std::string( "Segmenting mesh needs exactly 2 or 3 input points!" ) );

			return result;
		}

		// Step 1: Find closest vertices on the mesh for each input point using `findProjection()`
		std::vector<VertId> keyVertices;
		keyVertices.reserve( inputPoints.size() );

		MeshPart m = MeshPart( meshCopy );

		meshCopy.getAABBTree();
		for ( const Vector3f& point : inputPoints )
		{
			MeshProjectionResult closestVert = findProjection( point, m );
			if ( !closestVert.valid() )
			{
				result.set( "success", false );
				result.set( "error", std::string( "Could not find valid vertex for input point" ) );

				return result;
			}
			keyVertices.push_back( meshCopy.getClosestVertex( closestVert.proj ) );
		}

		// Step 2: Use the direction provided by JavaScript
		Vector3f contourDirection( dir[0], dir[1], dir[2] );

		// Normalize the direction vector to ensure it's a unit vector
		float dirLength = contourDirection.length();
		if ( dirLength < 1e-6f )
		{
			result.set( "success", false );
			result.set( "error", std::string( "Direction vector is too small or zero" ) );

			return result;
		}
		contourDirection /= dirLength;

		// Step 3: Create surrounding contour
		auto contourResult = surroundingContour( meshCopy, keyVertices, edgeMetric_, contourDirection );

		if ( !contourResult )
		{
			result.set( "success", false );
			result.set( "error", std::string( "Failed to create surrounding contour: " ) + contourResult.error() );

			return result;
		}

		// Step 4: Convert EdgeLoop to EdgePath for `fillContourLeftByGraphCut()`
		EdgeLoop contour = contourResult.value();
		EdgePath contourPath( contour.begin(), contour.end() );

		// Step 5: Fill the contour to get the segmented region
		Mesh segMesh;
		FaceBitSet segmentedFaces = fillContourLeftByGraphCut( meshCopy.topology, contourPath, edgeMetric_ );
		segMesh.addMeshPart( {meshCopy, &segmentedFaces} );

		// Step 6: Convert results to JavaScript-friendly format using emscripten val
		val meshData = MRJS::exportMeshMemoryView( segMesh );

		// FIXME: `Uint32Array` error for threejs
		// Since `EdgeId` has an implicit conversion operator to int, and it is internally represented as an int
		// We can directly reinterpret `EdgeId*` as `int*`
		const int* contourData = reinterpret_cast<const int*>( contour.data() );
		size_t contourSize = contour.size();
		val contourEdgesArray = val( typed_memory_view( contourSize, contourData ) );

		// Build the result object
		result.set( "success", true );
		result.set( "contourEdges", contourEdgesArray );
		result.set( "mesh", meshData );
	}
	catch ( const std::exception& e )
	{
		result.set( "success", false );
		result.set( "error", std::string( "Exception during segmentation: " ) + e.what() );
	}

	return result;
}

val MeshWrapper::fixUndercuts(const Vector3f& upDirection) const
{
	val returnObj = val::object();

	FixUndercuts::FixParams fixParams;
	fixParams.findParameters.upDirection = upDirection.normalized();

	// TODO: More performance gains? 
	Mesh meshCopy;
	// meshCopy.topology = mesh.topology;
	// meshCopy.points = mesh.points;
	meshCopy.addMeshPart( mesh );
	
	auto result = FixUndercuts::fix(
		meshCopy,
		// {.findParameters = {.upDirection = upDirection}} // NOTE: This also works!!!
		fixParams
	);

	val meshData = MRJS::exportMeshMemoryView( meshCopy );
	returnObj.set( "success", true );
	returnObj.set( "mesh", meshData );
	returnObj.set( "message", "Undercuts fixed successfully!" );

    return returnObj;
}

val MeshWrapper::fillHoles() const
{
	auto holeEdges = mesh.topology.findHoleRepresentiveEdges();
	// TODO: More performance gains? 
	Mesh meshCopy;
	meshCopy.topology = mesh.topology;
	meshCopy.points = mesh.points;

	for ( EdgeId e : holeEdges )
	{
		FillHoleParams params;
		fillHole( meshCopy, e, params );
	}

    return MRJS::exportMeshMemoryView( meshCopy );
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
	// ------------------------------------------------------------------------
	// Bindings for `MeshWrapper`
	// ------------------------------------------------------------------------
	class_<MeshWrapper>( "MeshWrapper" )
		.smart_ptr<std::shared_ptr<MeshWrapper>>( "shared_ptr<MeshWrapper>" ) 
		.constructor<>()
		.constructor<const Mesh&>()
		.class_function( "fromTriangles", &MeshWrapper::fromTriangles )

		.property( "mesh", &MeshWrapper::mesh )
		.function( "getMesh", &MeshWrapper::getMeshPtr, allow_raw_pointers() )

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

		.function( "segmentByPoints", &MeshWrapper::segmentByPoints )
		.function( "fixUndercuts", &MeshWrapper::fixUndercuts )
		.function( "fillHoles", &MeshWrapper::fillHoles )

		// Spatial queries
		.function( "projectPoint", &MeshWrapper::projectPoint )

		// Transformations
		.function( "transform", &MeshWrapper::transform )
		.function( "pack", &MeshWrapper::pack );
}

} //namespace MRJS
