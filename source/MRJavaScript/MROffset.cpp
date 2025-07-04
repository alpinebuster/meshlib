#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MREnums.h>
#include <MRVoxels/MROffset.h>

#include "MRUtils.h"

using namespace emscripten;
using namespace MR;

// Helper function to handle the Expected<Mesh> return type
// Emscripten works better with simple return types, so we'll unwrap the Expected
val thickenMeshWrapper( const Mesh& mesh, float offset, const GeneralOffsetParameters& params )
{
	auto result = thickenMesh( mesh, offset, params );

	if ( result.has_value() )
	{
		val meshData = MRJS::exportMeshData( result.value() );

		// Return the mesh wrapped in an object that indicates success
		val returnObj = val::object();
		returnObj.set( "success", true );
		returnObj.set( "mesh", meshData );

		return returnObj;
	}
	else
	{
		// Return an error object with the error message
		val returnObj = val::object();
		returnObj.set( "success", false );
		returnObj.set( "error", result.error() );

		return returnObj;
	}
}

EMSCRIPTEN_BINDINGS( ThickenMeshModule )
{
	class_<OffsetParameters>( "OffsetParameters" )
		.constructor<>()

		.property( "signDetectionMode", &OffsetParameters::signDetectionMode )
		.property( "closeHolesInHoleWindingNumber", &OffsetParameters::closeHolesInHoleWindingNumber )
		.property( "windingNumberThreshold", &OffsetParameters::windingNumberThreshold )
		.property( "windingNumberBeta", &OffsetParameters::windingNumberBeta )
		.property( "memoryEfficient", &OffsetParameters::memoryEfficient );

	class_<SharpOffsetParameters, base<OffsetParameters>>( "SharpOffsetParameters" )
		.constructor<>()

		.property( "minNewVertDev", &SharpOffsetParameters::minNewVertDev )
		.property( "maxNewRank2VertDev", &SharpOffsetParameters::maxNewRank2VertDev )
		.property( "maxNewRank3VertDev", &SharpOffsetParameters::maxNewRank3VertDev )
		.property( "maxOldVertPosCorrection", &SharpOffsetParameters::maxOldVertPosCorrection );

	class_<GeneralOffsetParameters, base<SharpOffsetParameters>>( "GeneralOffsetParameters" )
		.constructor<>()

		.property( "mode", &GeneralOffsetParameters::mode );

	enum_<OffsetMode>( "OffsetMode" )
		.value( "Smooth", OffsetMode::Smooth )     // OpenVDB dual marching cubes
		.value( "Standard", OffsetMode::Standard )   // Standard marching cubes
		.value( "Sharpening", OffsetMode::Sharpening ) // Marching cubes with sharpening
		;
	enum_<SignDetectionMode>( "SignDetectionMode" )
		.value( "Unsigned", SignDetectionMode::Unsigned )
		.value( "OpenVDB", SignDetectionMode::OpenVDB )
		.value( "ProjectionNormal", SignDetectionMode::ProjectionNormal )
		.value( "WindingRule", SignDetectionMode::WindingRule )
		.value( "HoleWindingRule", SignDetectionMode::HoleWindingRule );

	// Expose the wrapper function instead of the original
	// This gives us better error handling in JavaScript
	function( "thickenMesh", &thickenMeshWrapper );
}
