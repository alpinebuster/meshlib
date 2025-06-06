#include <emscripten/bind.h>

#include <MRMesh/MRVector3.h>
#include <MRMesh/MRConstants.h>

using namespace emscripten;
using namespace MR;

// ------------------------------------------------------------------------
// 1. Bind the Embind interface for Vector3<float> (i.e., Vector3f)
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS(Vector3f_module) {
    class_<Vector3<float>>("Vector3f")
        // Constructor: Parameterless construction and construction of three floating-point parameters (x,y,z)
        .constructor<>()
        .constructor<float, float, float>()

        // Expose the member variables x, y, and z as attributes to the JS
        .property("x", &Vector3<float>::x)
        .property("y", &Vector3<float>::y)
        .property( "z", &Vector3<float>::z )

        // Member function binding
        .function("lengthSq", &Vector3<float>::lengthSq)
        .function("length", &Vector3<float>::length)
        .function("normalized", &Vector3<float>::normalized)
        .function("furthestBasisVector", &Vector3<float>::furthestBasisVector)
        .function("perpendicular", &Vector3<float>::perpendicular)
        .function("unsignZeroValues", &Vector3<float>::unsignZeroValues)
        .function("isFinite", &Vector3<float>::isFinite)
        // The subscript operator cannot be directly bound as operator[],
        // let's change it to two functions, get(i), set(i,val).
        .function( "get", select_overload<const float& ( int ) const>( &Vector3<float>::operator[] ) )
        .function( "set", select_overload<float& ( int )>( &Vector3<float>::operator[] ) )

        // Bind the static factory function
        .class_function("diagonal", &Vector3<float>::diagonal)
        .class_function("plusX", &Vector3<float>::plusX)
        .class_function("plusY", &Vector3<float>::plusY)
        .class_function("plusZ", &Vector3<float>::plusZ)
        .class_function("minusX", &Vector3<float>::minusX)
        .class_function("minusY", &Vector3<float>::minusY)
        .class_function("minusZ", &Vector3<float>::minusZ)
        ;

    // Below, bind the free functions related to Vector3<float> as well
    function("distanceSq_f", select_overload<float(const Vector3<float>&, const Vector3<float>&)>(&distanceSq<float>));
    function("distance_f", select_overload<float(const Vector3<float>&, const Vector3<float>&)>(&distance<float>));
    function("cross_f", select_overload<Vector3<float>(const Vector3<float>&, const Vector3<float>&)>(&cross<float>));
    function("dot_f", select_overload<float(const Vector3<float>&, const Vector3<float>&)>(&dot<float>));
    function("sqr_f", select_overload<float(const Vector3<float>&)>(&sqr<float>));
    function("mixed_f", select_overload<float(const Vector3<float>&, const Vector3<float>&, const Vector3<float>&)>(&mixed<float>));
    function("mult_f", select_overload<Vector3<float>(const Vector3<float>&, const Vector3<float>&)>(&mult<float>));
    function("div_f", select_overload<Vector3<float>(const Vector3<float>&, const Vector3<float>&)>(&div<float>));
    function("angle_f", select_overload<float(const Vector3<float>&, const Vector3<float>&)>(&angle<float>));
    function("unitVector3_f", select_overload<Vector3<float>(float, float)>(&unitVector3<float>));
}

// ------------------------------------------------------------------------
// 2. Bind the Embind interface for Vector3<int> (i.e., Vector3i)
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS(Vector3i_module) {
    class_<Vector3<int>>("Vector3i")
        .constructor<>()
        .constructor<int, int, int>()
        .property("x", &Vector3<int>::x)
        .property("y", &Vector3<int>::y)
        .property("z", &Vector3<int>::z)
        .function("lengthSq", &Vector3<int>::lengthSq)
        // For integer vectors, length() is not provided because it returns auto (the length of the integer has no practical meaning), and it is not bound here
        // Nor bind normalized, furthestBasisVector, perpendicular (they do not work for integers)
        .function("get", select_overload<const int&(int) const>(&Vector3<int>::operator[]))
        .function("set", select_overload<int&(int)>(&Vector3<int>::operator[]))
        .class_function("diagonal", &Vector3<int>::diagonal)
        ;

    // Bind the free functions related to Vector3<int>
    function("distanceSq_i", select_overload<int(const Vector3<int>&, const Vector3<int>&)>(&distanceSq<int>));
    function("sqr_i", select_overload<int(const Vector3<int>&)>(&sqr<int>));
    // The cross, dot, mixed, mult, div, etc. can also be bound to integers, but it should be noted that the result type is also an integer
    function("cross_i", select_overload<Vector3<int>(const Vector3<int>&, const Vector3<int>&)>(&cross<int>));
    function("dot_i", select_overload<int(const Vector3<int>&, const Vector3<int>&)>(&dot<int>));
    function("mixed_i", select_overload<int(const Vector3<int>&, const Vector3<int>&, const Vector3<int>&)>(&mixed<int>));
    function("mult_i", select_overload<Vector3<int>(const Vector3<int>&, const Vector3<int>&)>(&mult<int>));
    function("div_i", select_overload<Vector3<int>(const Vector3<int>&, const Vector3<int>&)>(&div<int>));
    function("angle_i", select_overload<int(const Vector3<int>&, const Vector3<int>&)>(&angle<int>));
    function("unitVector3_i", select_overload<Vector3<int>(int, int)>(&unitVector3<int>));
}
