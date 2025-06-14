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

#include "MRMesh.h"

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
			obj.set( "mesh", MRJS::MeshWrapper( result.value() ) );
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
				obj.set( "mesh", MRJS::MeshWrapper( result.value() ) );
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
	class_<MeshLoadWrapper>( "MeshLoad" )
		.class_function( "fromFile", &MeshLoadWrapper::fromFile )
		.class_function( "fromBinaryData", &MeshLoadWrapper::fromBinaryData );
}
