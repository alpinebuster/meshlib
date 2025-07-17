#include <emscripten/bind.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector4.h>

#include "MRVector.h"

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( Vector4Module )
{
    bindTypedVector4<Vector4b>( "Vector4b", "b" );
    bindTypedVector4<Vector4f>( "Vector4f", "f" );
    bindTypedVector4<Vector4i>( "Vector4i", "i" );
    bindTypedVector4<Vector4ll>( "Vector4ll", "ll" );
    bindTypedVector4<Vector4d>( "Vector4d", "d" );
}
