#include <MRPch/MRWasm.h>

#include <MRMesh/MRMatrix3.h>
#include <MRMesh/MRMatrix3Decompose.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( Matrix3DecomposeModule )
{
	function( "isRigidf", &isRigid<float> );
	function( "isRigidd", &isRigid<double> );

	function( "decomposeMatrix3f", &decomposeMatrix3<float> );
	function( "decomposeMatrix3d", &decomposeMatrix3<double> );
}
