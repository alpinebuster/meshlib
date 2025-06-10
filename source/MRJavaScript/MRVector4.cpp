#include <emscripten/bind.h>

#include "MRMesh/MRVector4.h"
#include "MRMesh/MRConstants.h"

using namespace emscripten;
using namespace MR;

// ------------------------------------------------------------------------
// 1. Bind the Embind interface for `Vector4<float>` (i.e., Vector4f)
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS(Vector4fModule) {
    class_<Vector4<float>>("Vector4F")
        .constructor<>()
        .constructor<float, float, float, float>()

        .property( "x", &Vector4<float>::x )
        .property( "y", &Vector4<float>::y )
        .property( "z", &Vector4<float>::z )
        .property( "w", &Vector4<float>::w )

        .function( "lengthSq", &Vector4<float>::lengthSq )
        .function( "length", &Vector4<float>::length )
        .function( "normalized", &Vector4<float>::normalized )
        .function( "proj3d", &Vector4<float>::proj3d )
        .function( "isFinite", &Vector4<float>::isFinite )
        .function("get", select_overload<const float&(int) const>(&Vector4<float>::operator[]))
        .function( "set", select_overload<float& ( int )>( &Vector4<float>::operator[] ) )

        .class_function("diagonal", &Vector4<float>::diagonal);

    // Bind the free function related to `Vector4<float>`
    function("distanceSq4F", select_overload<float(const Vector4<float>&, const Vector4<float>&)>(&distanceSq<float>));
    function("distance4F", select_overload<float(const Vector4<float>&, const Vector4<float>&)>(&distance<float>));
    function("dot4F", select_overload<float(const Vector4<float>&, const Vector4<float>&)>(&dot<float>));
    function("sqr4F", select_overload<float(const Vector4<float>&)>(&sqr<float>));
    function("mult4F", select_overload<Vector4<float>(const Vector4<float>&, const Vector4<float>&)>(&mult<float>));
    function("div4F", select_overload<Vector4<float>(const Vector4<float>&, const Vector4<float>&)>(&div<float>));
}

// ------------------------------------------------------------------------
// 2. Bind the Embind interface for `Vector4<int>` (i.e., Vector4I)
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS(Vector4iModule) {
    class_<Vector4<int>>("Vector4I")
        .constructor<>()
        .constructor<int, int, int, int>()

        .property( "x", &Vector4<int>::x )
        .property("y", &Vector4<int>::y)
        .property("z", &Vector4<int>::z)
        .property( "w", &Vector4<int>::w )

        .function( "lengthSq", &Vector4<int>::lengthSq )
        // Integers are not bound to `length()` and `normalized()`
        .function("get", select_overload<const int&(int) const>(&Vector4<int>::operator[]))
        .function("set", select_overload<int&(int)>(&Vector4<int>::operator[]))
        .class_function("diagonal", &Vector4<int>::diagonal);

    // Bind the free function related to `Vector4<int>`
    function("distanceSq4I", select_overload<int(const Vector4<int>&, const Vector4<int>&)>(&distanceSq<int>));
    function("distance4I", select_overload<int(const Vector4<int>&, const Vector4<int>&)>(&distance<int>));
    function("dot4I", select_overload<int(const Vector4<int>&, const Vector4<int>&)>(&dot<int>));
    function("sqr4I", select_overload<int(const Vector4<int>&)>(&sqr<int>));
    function("mult4I", select_overload<Vector4<int>(const Vector4<int>&, const Vector4<int>&)>(&mult<int>));
    function("div4I", select_overload<Vector4<int>(const Vector4<int>&, const Vector4<int>&)>(&div<int>));
}
