#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRArrow.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( ArrowModule )
{
    // NOTE: Why use `optional_override`?
    // 1) The `optional_override()` function lets `Emscripten` correctly handle lambdas and support default parameters in JavaScript.
    // 2) It avoids directly exporting C++ functions with default arguments, since **the JS side can’t see C++ default values**.
        function( "makeArrow", optional_override( []( const Vector3f& base, const Vector3f& vert,
        float thickness = 0.05f,
        float coneRadius = 0.1f,
        float coneSize = 0.2f,
        int qual = 32 ) -> Mesh
    {
        return makeArrow( base, vert, thickness, coneRadius, coneSize, qual );
    } ) );

    function( "makeBasisAxes", optional_override( []( float size = 1.0f,
        float thickness = 0.05f,
        float coneRadius = 0.1f,
        float coneSize = 0.2f,
        int qual = 32 ) -> Mesh
    {
        return makeBasisAxes( size, thickness, coneRadius, coneSize, qual );
    } ) );
}

