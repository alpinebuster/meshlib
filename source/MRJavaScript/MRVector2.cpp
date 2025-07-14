#include <emscripten/bind.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>

#include "MRVector.h"

using namespace emscripten;
using namespace MR;


// ------------------------------------------------------------------------
// Bind the Embind interface for `Vector2*`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( Vector2Module )
{
    value_array<std::pair<Vector2i, Vector2i>>( "Vector2iPair" )
        .element( &std::pair<Vector2i, Vector2i>::first )
        .element( &std::pair<Vector2i, Vector2i>::second );
    bindTypedVector2<Vector2i>( "Vector2i" );

    value_array<std::pair<Vector2f, Vector2f>>( "Vector2fPair" )
        .element( &std::pair<Vector2f, Vector2f>::first )
        .element( &std::pair<Vector2f, Vector2f>::second );
    bindTypedVector2<Vector2f>( "Vector2f" );

    value_array<std::pair<Vector2ll, Vector2ll>>( "Vector2llPair" )
        .element( &std::pair<Vector2ll, Vector2ll>::first )
        .element( &std::pair<Vector2ll, Vector2ll>::second );
    bindTypedVector2<Vector2ll>( "Vector2ll" );

    value_array<std::pair<Vector2b, Vector2b>>( "Vector2bPair" )
        .element( &std::pair<Vector2b, Vector2b>::first )
        .element( &std::pair<Vector2b, Vector2b>::second );
    bindTypedVector2<Vector2b>( "Vector2b" );

    value_array<std::pair<Vector2d, Vector2d>>( "Vector2dPair" )
        .element( &std::pair<Vector2d, Vector2d>::first )
        .element( &std::pair<Vector2d, Vector2d>::second );
    bindTypedVector2<Vector2d>( "Vector2d" );
}
