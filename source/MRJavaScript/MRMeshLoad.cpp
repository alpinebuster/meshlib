#include <string>
#include <vector>
#include <memory>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshLoad.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRExpected.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRVectorTraits.h>

using namespace emscripten;
using namespace MR;

// Helper function to convert Expected<T> to JavaScript-friendly result
template<typename T>
val expectedToJs( const Expected<T>& expected )
{
	if ( expected.has_value() )
	{
		val obj = val::object();
		obj.set( "success", true );
		obj.set( "value", expected.value() );
		return obj;
	}
	else
	{
		val obj = val::object();
		obj.set( "success", false );
		obj.set( "error", expected.error() );
		return obj;
	}
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

// Wrapper class for Mesh to provide JavaScript-friendly interface
class MeshWrapper {
public:
	Mesh mesh;

	MeshWrapper() = default;
	MeshWrapper( const Mesh& m ) : mesh( m ) {}

	// Static factory methods for creating meshes from various sources
	static val fromTriangles( const val& vertexCoords, const val& triangles )
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
	val getBoundingBox() const
	{
		return box3fToObject( mesh.getBoundingBox() );
	}

	val getVertexPosition( int vertId ) const
	{
		if ( vertId >= 0 && vertId < ( int )mesh.points.size() )
		{
			return vector3fToArray( mesh.points[VertId( vertId )] );
		}
		return val::null();
	}

	void setVertexPosition( int vertId, const val& position )
	{
		if ( vertId >= 0 && vertId < ( int )mesh.points.size() )
		{
			mesh.points[VertId( vertId )] = arrayToVector3f( position );
			mesh.invalidateCaches(); // Important: invalidate caches after modification
		}
	}

	int getVertexCount() const
	{
		return ( int )mesh.topology.lastValidVert() + 1;
	}

	int getFaceCount() const
	{
		return ( int )mesh.topology.lastValidFace() + 1;
	}

	double getVolume() const
	{
		return mesh.volume();
	}

	double getArea() const
	{
		return mesh.area();
	}

	val findCenter() const
	{
		return vector3fToArray( mesh.findCenterFromBBox() );
	}

	// Face operations
	val getFaceVertices( int faceId ) const
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

	val getFaceNormal( int faceId ) const
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

	// Point projection
	val projectPoint( const val& point, float maxDistance = std::numeric_limits<float>::max() ) const
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
	void transform( const val& matrix )
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
	void pack()
	{
		mesh.pack();
	}
};

// Wrapper for MeshLoad functions
class MeshLoadWrapper {
public:
	// Load from file path (for environments that support file system)
	static val fromFile( const std::string& filePath )
	{
		auto result = MeshLoad::fromAnySupportedFormat( filePath );
		if ( result.has_value() )
		{
			val obj = val::object();
			obj.set( "success", true );
			obj.set( "mesh", MeshWrapper( result.value() ) );
			return obj;
		}
		else
		{
			val obj = val::object();
			obj.set( "success", false );
			obj.set( "error", result.error() );
			return obj;
		}
	}

	// Load from binary data (more useful for web applications)
	static val fromBinaryData( const val& data, const std::string& extension )
	{
		try
		{
			// Convert JavaScript Uint8Array to string stream
			std::string binaryStr;
			int length = data["length"].as<int>();
			binaryStr.reserve( length );

			for ( int i = 0; i < length; ++i )
			{
				binaryStr += static_cast< char >( data[i].as<uint8_t>() );
			}

			std::istringstream stream( binaryStr, std::ios::binary );

			// Choose appropriate loader based on extension
			Expected<Mesh> result;
			std::string ext = extension;
			std::transform( ext.begin(), ext.end(), ext.begin(), ::tolower );

			if ( ext == ".stl" || ext == "stl" )
			{
				result = MeshLoad::fromAnyStl( stream );
			}
			else if ( ext == ".obj" || ext == "obj" )
			{
				result = MeshLoad::fromObj( stream );
			}
			else if ( ext == ".off" || ext == "off" )
			{
				result = MeshLoad::fromOff( stream );
			}
			else if ( ext == ".ply" || ext == "ply" )
			{
				result = MeshLoad::fromPly( stream );
			}
			else
			{
				val obj = val::object();
				obj.set( "success", false );
				obj.set( "error", "Unsupported file format: " + extension );
				return obj;
			}

			if ( result.has_value() )
			{
				val obj = val::object();
				obj.set( "success", true );
				obj.set( "mesh", MeshWrapper( result.value() ) );
				return obj;
			}
			else
			{
				val obj = val::object();
				obj.set( "success", false );
				obj.set( "error", result.error() );
				return obj;
			}

		}
		catch ( const std::exception& e )
		{
			val obj = val::object();
			obj.set( "success", false );
			obj.set( "error", std::string( e.what() ) );
			return obj;
		}
	}
};

// Embind declarations
EMSCRIPTEN_BINDINGS( MeshLoadModule )
{
	// Bind MeshWrapper class
	class_<MeshWrapper>( "Mesh" )
		.constructor<>()
		// .constructor<const Mesh&>()
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

		// Spatial queries
		.function( "projectPoint", &MeshWrapper::projectPoint )

		// Transformations
		.function( "transform", &MeshWrapper::transform )
		.function( "pack", &MeshWrapper::pack );

	// Bind MeshLoadWrapper class
	class_<MeshLoadWrapper>( "MeshLoad" )
		.class_function( "fromFile", &MeshLoadWrapper::fromFile )
		.class_function( "fromBinaryData", &MeshLoadWrapper::fromBinaryData );
}
