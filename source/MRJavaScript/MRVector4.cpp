#include <emscripten/bind.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector4.h>

#include "MRVector.h"

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( Vector4fModule )
{
    value_array<std::pair<Vector4b, Vector4b>>( "Vector4bPair" )
        .element( &std::pair<Vector4b, Vector4b>::first )
        .element( &std::pair<Vector4b, Vector4b>::second );
    bindTypedVector4<Vector4b>( "Vector4b", "b" );

    value_array<std::pair<Vector4f, Vector4f>>( "Vector4fPair" )
        .element( &std::pair<Vector4f, Vector4f>::first )
        .element( &std::pair<Vector4f, Vector4f>::second );
    bindTypedVector4<Vector4f>( "Vector4f", "f" );

    value_array<std::pair<Vector4i, Vector4i>>( "Vector4iPair" )
        .element( &std::pair<Vector4i, Vector4i>::first )
        .element( &std::pair<Vector4i, Vector4i>::second );
    bindTypedVector4<Vector4i>( "Vector4i", "i" );

    value_array<std::pair<Vector4ll, Vector4ll>>( "Vector4llPair" )
        .element( &std::pair<Vector4ll, Vector4ll>::first )
        .element( &std::pair<Vector4ll, Vector4ll>::second );
    bindTypedVector4<Vector4ll>( "Vector4ll", "ll" );

    value_array<std::pair<Vector4d, Vector4d>>( "Vector4dPair" )
        .element( &std::pair<Vector4d, Vector4d>::first )
        .element( &std::pair<Vector4d, Vector4d>::second );
    bindTypedVector4<Vector4d>( "Vector4d", "d" );
}
