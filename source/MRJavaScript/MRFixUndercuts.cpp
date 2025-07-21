#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRBox.h>
#include <MRVoxels/MRFixUndercuts.h>

#include "MRUtils.h"

using namespace emscripten;
using namespace MR;
using namespace FixUndercuts;


FindParams createFindParamsImpl( float upX, float upY, float upZ, float wallAngle )
{
	return FindParams( Vector3f( upX, upY, upZ ), wallAngle );
}

FixParams createFixParamsImpl( const FindParams& findParams, float voxelSize, float bottomExtension, bool smooth )
{
	FixParams params;
	params.findParameters = findParams;
	params.voxelSize = voxelSize;
	params.bottomExtension = bottomExtension;
	params.smooth = smooth;

	return params;
}

val fixUndercutsImplTest( Mesh& mesh, const Vector3f& upDirection, float voxelSize = 0.0f, float bottomExtension = 0.0f )
{
	size_t originalVertCount = mesh.topology.numValidVerts();
	size_t originalFaceCount = mesh.topology.numValidFaces();

	val returnObj = val::object();

	Mesh meshCopy;
	meshCopy = mesh;

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

val fixUndercutsImpl( Mesh& mesh, const Vector3f& upDirection, float voxelSize = 0.0f, float bottomExtension = 0.0f )
{
	// NOTE: We're passing the mesh by reference - it gets modified in place
	auto result = fix( mesh, { .findParameters = {.upDirection = upDirection.normalized()},.voxelSize = voxelSize,.bottomExtension = bottomExtension } );

	val returnObj = val::object();
	if ( result )
	{
		val meshData = MRJS::exportMeshMemoryView( mesh );

		// The mesh has been modified in place
		returnObj.set( "success", true );
		returnObj.set( "mesh", meshData );
	}
	else
	{
		returnObj.set( "success", false );
		returnObj.set( "error", std::string( result.error() ) );
	}

	return returnObj;
}

// Alternative wrapper that throws exceptions instead of returning error objects
void fixUndercutsImplThrows( Mesh& mesh, const Vector3f& upDirection, float voxelSize = 0.0f, float bottomExtension = 0.0f )
{
	auto result = fix( mesh, { {upDirection}, voxelSize, bottomExtension } );

	if ( !result )
	{
		// Convert the C++ error into a JavaScript exception
		std::string errorMsg = "fixUndercuts failed: " + std::string( result.error() );
		emscripten::val::global( "Error" ).new_( errorMsg ).throw_();
	}
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


	function( "fixUndercutsImpl", &fixUndercutsImpl, allow_raw_pointers() );
	function( "fixUndercutsImplTest", &fixUndercutsImplTest, allow_raw_pointers() );
	function( "fixUndercutsImplThrows", &fixUndercutsImplThrows, allow_raw_pointers() );

	function( "calculateRecommendedVoxelSizeImpl", optional_override( [] ( const Mesh& mesh, float qualityFactor = 1.0f ) -> float
	{
		auto bbox = mesh.getBoundingBox();
		float meshSize = bbox.size().length();

		return meshSize / ( 100.0f * qualityFactor );
	} ) );

    function( "createFindParamsImpl", &createFindParamsImpl, allow_raw_pointers() );
    function( "createFixParamsImpl", &createFixParamsImpl, allow_raw_pointers() );
}
