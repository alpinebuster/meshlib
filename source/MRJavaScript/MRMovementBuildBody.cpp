#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMovementBuildBody.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRVector3.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MovementBuildBodyModule )
{
	class_<MovementBuildBodyParams>( "MovementBuildBodyParams" )
		.constructor<>()

		.property( "allowRotation", &MovementBuildBodyParams::allowRotation )
		.property( "center", &MovementBuildBodyParams::center )      // OptionalVector3f
		.property( "bodyNormal", &MovementBuildBodyParams::bodyNormal )  // OptionalVector3f
		.property( "b2tXf", &MovementBuildBodyParams::b2tXf,  allow_raw_pointers() ) // AffineXf3f*
		;

	function( "makeMovementBuildBody", &makeMovementBuildBody, allow_raw_pointers() );
}
