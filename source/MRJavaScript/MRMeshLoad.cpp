#include <string>
#include <vector>
#include <memory>

#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRExpected.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRVectorTraits.h>
#include <MRMesh/MRMeshLoad.h>

#include "MRMesh.h"

using namespace emscripten;
using namespace MR;


class MeshLoadWrapper {
public:
	// NOTE: Load from emscripten **virtual** file path
	// 
	// In JS:
	//   `FS.createDataFile("/", "model_name.stl", data, true, true);`
	// 
	static val fromFile( const std::string& filePath )
	{
		Expected<Mesh> result = MeshLoad::fromAnySupportedFormat( filePath );
		if ( result.has_value() )
		{
			val obj = val::object();
			obj.set( "success", true );
			obj.set( "mesh", result.value() );
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

	// Load from binary data (e.g. STL, more useful for web applications)
	static val fromBinaryData( uintptr_t dataPtr, size_t length, const std::string& extension )
	{
		try
		{
			// ### v1 ###
			// ❌ Slowest: requires element-by-element access and type conversion
			// ❌ High overhead: every time data[i].as<uint8_t>() there is JS call overhead
			// ✅ No manual memory management required
			// 
			// Convert JavaScript Uint8Array to string stream
			// // std::string binaryStr;
			// Instead of converting to string, work directly with the raw data
			// std::vector<uint8_t> binaryData;
			// // binaryStr.reserve( length );
			// binaryData.reserve(length);
			// for ( int i = 0; i < length; ++i )
			// {
			// 	// binaryStr += static_cast< char >( data[i].as<uint8_t>() );
			// 	// binaryData.push_back(data[i].as<uint8_t>());
			// 	binaryData[i] = data[i].as<uint8_t>();
			// }
			// std::istringstream stream( binaryStr, std::ios::binary );

			// ### v2 ###
			// const size_t length = data["length"].as<size_t>();
			// std::vector<uint8_t> binaryData(length);
			// for ( int i = 0; i < length; ++i )
			// {
			// 	binaryData[i] = data[i].as<uint8_t>();
			// }

			// ### v3 ###
			// ✅ Fastest: only 2 memory copies (JS → WASM memory, WASM memory → vector)
			// ✅ Memory efficient: direct manipulation of raw pointers
			// ✅ No type conversion overhead: pass pointer and length directly
			uint8_t* data = reinterpret_cast<uint8_t*>( dataPtr );
			std::vector<uint8_t> binaryData( data, data + length );

			std::stringstream stream( std::ios::in | std::ios::out | std::ios::binary );
			stream.write( reinterpret_cast<const char*>( binaryData.data()), length );

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
				obj.set( "mesh", result.value() );

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


EMSCRIPTEN_BINDINGS( MeshLoadWrapperModule )
{
	class_<MeshLoadWrapper>( "MeshLoadWrapper" )
		.class_function( "fromFile", &MeshLoadWrapper::fromFile )
		.class_function( "fromBinaryData", &MeshLoadWrapper::fromBinaryData );
}
