#include <emscripten/bind.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector3.h>

#include "MRVector.h"

using namespace emscripten;
using namespace MR;


// ------------------------------------------------------------------------
// Bind the Embind interface for `Vector3*`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( Vector3Module )
{
    bindTypedVector3<Vector3f>( "Vector3f", "f" );
    bindTypedVector3<Vector3b>( "Vector3b", "b" );
    bindTypedVector3<Vector3i>( "Vector3i", "i" );
    bindTypedVector3<Vector3ll>( "Vector3ll", "ll" );
    bindTypedVector3<Vector3d>( "Vector3d", "d" );
}
