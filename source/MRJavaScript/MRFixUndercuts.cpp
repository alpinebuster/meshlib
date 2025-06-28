#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRBox.h>
#include <MRVoxels/MRFixUndercuts.h>

using namespace emscripten;
using namespace MR;
using namespace FixUndercuts;


FindParams createFindParams( float upX, float upY, float upZ, float wallAngle )
{
	return FindParams( Vector3f( upX, upY, upZ ), wallAngle );
}

FixParams createFixParams( const FindParams& findParams, float voxelSize, float bottomExtension, bool smooth )
{
	FixParams params;
	params.findParameters = findParams;
	params.voxelSize = voxelSize;
	params.bottomExtension = bottomExtension;
	params.smooth = smooth;

	return params;
}

// `Expected<void>` is tricky because it represents
// either success (with no return value) or failure (with an error message)
val fixUndercutsWrapper( Mesh& mesh, const Vector3f& upDirection, float voxelSize = 0.0f, float bottomExtension = 0.0f )
{
	// NOTE: We're passing the mesh by reference - it gets modified in place
	auto result = fix( mesh, { {upDirection}, voxelSize, bottomExtension } );

	val returnObj = val::object();
	if ( result.has_value() )
	{
		// Success case: the operation completed without errors
		// The mesh has been modified in place, so we just report success
		returnObj.set( "success", true );
		returnObj.set( "message", "Undercuts fixed successfully, the input mesh changed!" );
	}
	else
	{
		// Error case: something went wrong during the operation
		// The mesh might be in an undefined state, so this is important to catch
		returnObj.set( "success", false );
		returnObj.set( "error", std::string( result.error() ) );
	}

	return returnObj;
}

// Alternative wrapper that throws exceptions instead of returning error objects
// This gives JavaScript developers a choice in how they want to handle errors
void fixUndercutsThrows( Mesh& mesh, const Vector3f& upDirection, float voxelSize = 0.0f, float bottomExtension = 0.0f )
{
	auto result = fix( mesh, { {upDirection}, voxelSize, bottomExtension } );

	if ( !result.has_value() )
	{
		// Convert the C++ error into a JavaScript exception
		// This follows JavaScript conventions where errors are typically thrown
		std::string errorMsg = "fixUndercuts failed: " + std::string( result.error() );
		emscripten::val::global( "Error" ).new_( errorMsg ).throw_();
	}
	// If we reach here, the operation succeeded and the mesh has been modified
}


EMSCRIPTEN_BINDINGS( FixUndercutsModule )
{
	value_object<FindParams>( "FindParams" )
		.field( "upDirection", &FindParams::upDirection )
		.field( "wallAngle", &FindParams::wallAngle );

	class_<FixParams>( "FixParams" )
		.constructor<>()
		.property( "findParameters", &FixParams::findParameters )
		.property( "voxelSize", &FixParams::voxelSize )
		.property( "bottomExtension", &FixParams::bottomExtension )
		.property( "smooth", &FixParams::smooth );

	// Expose the wrapper that returns a result object
	// This approach gives JavaScript maximum control over error handling
	function( "fixUndercuts", &fixUndercutsWrapper );
	// Also expose the exception-throwing version for developers who prefer try/catch
	function( "fixUndercutsThrows", &fixUndercutsThrows );

	// Utility function to help JavaScript developers understand voxel size implications
	// This addresses the "if voxelSize == 0.0f it will be counted automatically" comment
	function( "calculateRecommendedVoxelSize", optional_override( [] ( const Mesh& mesh, float qualityFactor = 1.0f ) -> float
	{
		auto bbox = mesh.getBoundingBox();
		float meshSize = bbox.size().length();

		return meshSize / ( 100.0f * qualityFactor );
	} ) );
	
    function("createFindParams", &createFindParams);
    function("createFixParams", &createFixParams);
}
