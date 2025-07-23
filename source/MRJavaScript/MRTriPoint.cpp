#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRTriPoint.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( TriPointModule )
{
	class_<TriPointf>( "TriPointf" )
		.constructor<>();
	
	class_<TriPointd>( "TriPointd" )
		.constructor<>();
}
