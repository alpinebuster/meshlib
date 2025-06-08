#include <emscripten/bind.h>

#include "MRMesh/MRColor.h"
#include "MRMesh/MRVector3.h"
#include "MRMesh/MRVector4.h"

using namespace emscripten;
using namespace MR;


// ------------------------------------------------------------------------
// Color constructed and operated on using integers
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS(ColorModule) {
    class_<Color>("Color")
        .constructor<>()
        .constructor<int, int, int>()      //  r, g, b (By default, a = 1.0)
        .constructor<int, int, int, int>() //  r, g, b, a
        // FIXME: Cannot register multiple constructors with identical number of parameters (1) for class 'Color'
        // .constructor<const Vector3<int>&>()
        .constructor<const Vector4<int>&>()

        .property("r", &Color::r)
        .property("g", &Color::g)
        .property("b", &Color::b)
        .property("a", &Color::a)

        .function("getUInt32", &Color::getUInt32)
        .function("scaledAlpha", &Color::scaledAlpha)
        .function("get", select_overload<const uint8_t&(int) const>(&Color::operator[]))
        .function("set", select_overload<uint8_t&(int)>(&Color::operator[]))

        .class_function("white", &Color::white)
        .class_function("black", &Color::black)
        .class_function("gray",  &Color::gray)
        .class_function("red",   &Color::red)
        .class_function("green", &Color::green)
        .class_function("blue",  &Color::blue)
        .class_function("yellow",&Color::yellow)
        .class_function("brown", &Color::brown)
        .class_function("purple",&Color::purple)
        .class_function("transparent", &Color::transparent);

    function("ColorAdd", select_overload<Color(const Color&, const Color&)>(&operator+));
    function("ColorSub", select_overload<Color(const Color&, const Color&)>(&operator-));
    function("ColorMul", select_overload<Color(float, const Color&)>(&operator*));
    function("ColorMulRev", select_overload<Color(const Color&, float)>(&operator*));
    function("ColorDiv", select_overload<Color(const Color&, float)>(&operator/));
    function("ColorBlend", &blend);
}
