#include <emscripten/bind.h>

#include <MRMesh/MRVector3.h>
#include <MRMesh/MRConstants.h>

#include "MRVector.h"

using namespace emscripten;
using namespace MR;


// ------------------------------------------------------------------------
// Bind the Embind interface for `Vector3*`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( Vector3Module )
{
    value_array<std::pair<Vector3f, Vector3f>>( "Vector3fPair" )
        .element( &std::pair<Vector3f, Vector3f>::first )
        .element( &std::pair<Vector3f, Vector3f>::second );
    bindTypedVector3<Vector3f>( "Vector3f", "f" );

    value_array<std::pair<Vector3b, Vector3b>>( "Vector3bPair" )
        .element( &std::pair<Vector3b, Vector3b>::first )
        .element( &std::pair<Vector3b, Vector3b>::second );
    bindTypedVector3<Vector3b>( "Vector3b", "b" );

    value_array<std::pair<Vector3i, Vector3i>>( "Vector3iPair" )
        .element( &std::pair<Vector3i, Vector3i>::first )
        .element( &std::pair<Vector3i, Vector3i>::second );
    bindTypedVector3<Vector3i>( "Vector3i", "i" );

    value_array<std::pair<Vector3ll, Vector3ll>>( "Vector3llPair" )
        .element( &std::pair<Vector3ll, Vector3ll>::first )
        .element( &std::pair<Vector3ll, Vector3ll>::second );
    bindTypedVector3<Vector3ll>( "Vector3ll", "ll" );

    value_array<std::pair<Vector3d, Vector3d>>( "Vector3dPair" )
        .element( &std::pair<Vector3d, Vector3d>::first )
        .element( &std::pair<Vector3d, Vector3d>::second );
    bindTypedVector3<Vector3d>( "Vector3d", "d" );
}
