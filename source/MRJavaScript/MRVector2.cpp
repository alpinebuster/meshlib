#include <emscripten/bind.h>

#include <MRMesh/MRVector2.h>

#include "MRVector.h"

using namespace emscripten;
using namespace MR;


// ------------------------------------------------------------------------
// Bind the Embind interface for `Vector2*`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( Vector2Module )
{
    bindTypedVector2<Vector2i>( "Vector2i" );
    bindTypedVector2<Vector2b>( "Vector2b" );
    bindTypedVector2<Vector2ll>( "Vector2ll" );
    bindTypedVector2<Vector2f>( "Vector2f" );
    bindTypedVector2<Vector2d>( "Vector2d" );
}
