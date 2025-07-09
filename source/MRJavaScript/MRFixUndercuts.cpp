#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRBox.h>
#include <MRVoxels/MRFixUndercuts.h>

#include "MRUtils.h"

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

val fixUndercutsWrapperTest( Mesh& mesh, const Vector3f& upDirection, float voxelSize = 0.0f, float bottomExtension = 0.0f )
{
	size_t originalVertCount = mesh.topology.numValidVerts();
	size_t originalFaceCount = mesh.topology.numValidFaces();

	val returnObj = val::object();

	Mesh meshCopy;
	meshCopy.addMeshPart( mesh );
	// meshCopy.topology = mesh.topology;
	// meshCopy.points = mesh.points;

	size_t copyVertCount = meshCopy.topology.numValidVerts();
	size_t copyFaceCount = meshCopy.topology.numValidFaces();

	if ( copyVertCount != originalVertCount || copyFaceCount != originalFaceCount )
	{
		returnObj.set( "success", false );
		returnObj.set( "error", "Mesh copy failed!" );
		return returnObj;
	}

	FixParams fixParams;
	fixParams.findParameters.upDirection = upDirection.normalized();
	fixParams.voxelSize = voxelSize;
	fixParams.bottomExtension = bottomExtension;

	int progressSteps = 0;
	fixParams.cb = [&progressSteps, &returnObj] ( float progress ) -> bool
	{
		progressSteps++;
		if ( progress > 0.7 )
		{
			returnObj.set( ( "debug_progress_" + std::to_string( progressSteps ) ).c_str(), progress );
		}
		return true;
	};
	auto result = fix( meshCopy, fixParams );
	meshCopy.invalidateCaches();

	if ( result )
	{
		size_t processedVertCount = meshCopy.topology.numValidVerts();
		size_t processedFaceCount = meshCopy.topology.numValidFaces();

		returnObj.set( "debug_originalVertCount", ( int )originalVertCount );
		returnObj.set( "debug_originalFaceCount", ( int )originalFaceCount );
		returnObj.set( "debug_copiedVertCount", ( int )copyVertCount );
		returnObj.set( "debug_copiedFaceCount", ( int )copyFaceCount );
		returnObj.set( "debug_processedVertCount", ( int )processedVertCount );
		returnObj.set( "debug_processedFaceCount", ( int )processedFaceCount );

		try
		{
			val meshData = MRJS::exportMeshMemoryView( meshCopy );
			val originalMeshData = MRJS::exportMeshMemoryView( mesh );

			returnObj.set( "success", true );
			returnObj.set( "mesh", meshData );
			returnObj.set( "originalMesh", originalMeshData );
			returnObj.set( "message", "Undercuts fixed successfully!" );
		}
		catch ( const std::exception& e )
		{
			returnObj.set( "success", false );
			returnObj.set( "error", std::string( "Export failed: " ) + e.what() );
		}
	}
	else
	{
		returnObj.set( "success", false );
		returnObj.set( "error", std::string( result.error() ) );
	}

	return returnObj;
}
// FIXME: Why pass mesh from JS will cause the result has no vertices & indices?
// 
// `Expected<void>` is tricky because it represents
// either success (with no return value) or failure (with an error message)
val fixUndercutsWrapper( Mesh& mesh, const Vector3f& upDirection, float voxelSize = 0.0f, float bottomExtension = 0.0f )
{
	// TODO: More performance gains? 
	Mesh meshCopy;
	meshCopy.topology = mesh.topology;
	meshCopy.points = mesh.points;

	// NOTE: We're passing the mesh by reference - it gets modified in place
	auto result = fix( meshCopy, { .findParameters = {.upDirection = upDirection},.voxelSize = voxelSize,.bottomExtension = bottomExtension } );

	val returnObj = val::object();
	if ( result )
	{
		val meshData = MRJS::exportMeshMemoryView( meshCopy );
		val originMeshData = MRJS::exportMeshMemoryView( mesh );

		// Success case: the operation completed without errors
		// The mesh has been modified in place, so we just report success
		returnObj.set( "success", true );
		returnObj.set( "mesh", meshData );
		returnObj.set( "originMesh", originMeshData );
		returnObj.set( "upDirection", upDirection );
		returnObj.set( "upDirectionNormalized", upDirection.normalized() );
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

	if ( !result )
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
	function( "fixUndercutsTest", &fixUndercutsWrapperTest );

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
