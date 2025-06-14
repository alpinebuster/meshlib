// #include <vector>
// #include <limits>
// #include <cmath>
// #include <algorithm>

// #include <emscripten/bind.h>
// #include <emscripten/val.h>

// #include <MRMesh/MRVector2.h>
// #include <MRMesh/MRVector3.h>
// #include <MRMesh/MRBox.h>

// using namespace emscripten;
// using namespace MR;

// // Helper function for squaring
// template<typename T>
// T sqr(const T& x) { return x * x; }

// // Type aliases for convenience
// using Box2f = Box<Vector2f>;
// using Box3f = Box<Vector3f>;

// // Embind bindings
// EMSCRIPTEN_BINDINGS(box_module) {
//     class_<Box2f>("Box2f")
//         // Constructors
//         .constructor<>()
//         .constructor<const Vector2f&, const Vector2f&>()
        
//         // Static factory methods
//         .class_function("fromMinAndSize", &Box2f::fromMinAndSize)
//         .class_function("getMinBoxCorner", &Box2f::getMinBoxCorner)
//         .class_function("getMaxBoxCorner", &Box2f::getMaxBoxCorner)
        
//         // Properties (using property for direct access)
//         .property("min", &Box2f::min)
//         .property("max", &Box2f::max)
        
//         // Methods
//         .function("valid", &Box2f::valid)
//         .function("center", &Box2f::center)
//         .function("corner", &Box2f::corner)
//         .function("size", &Box2f::size)
//         .function("diagonal", &Box2f::diagonal)
//         .function("volume", &Box2f::volume)
//         .function("include", select_overload<void(const Vector2f&)>(&Box2f::include))
//         .function("includeBox", select_overload<void(const Box2f&)>(&Box2f::include))
//         .function("contains", select_overload<bool(const Vector2f&) const>(&Box2f::contains))
//         .function("containsBox", select_overload<bool(const Box2f&) const>(&Box2f::contains))
//         .function("getBoxClosestPointTo", &Box2f::getBoxClosestPointTo)
//         .function("intersects", &Box2f::intersects)
//         .function("intersection", &Box2f::intersection)
//         .function("intersect", &Box2f::intersect, return_value_policy::reference())
//         .function("getDistanceSqToBox", select_overload<float(const Box2f&) const>(&Box2f::getDistanceSq))
//         .function("getDistanceSqToPoint", select_overload<float(const Vector2f&) const>(&Box2f::getDistanceSq))
//         .function("expanded", &Box2f::expanded)
//         .function("insignificantlyExpanded", &Box2f::insignificantlyExpanded);

//     // Bind Box3f (3D Box)
//     class_<Box3f>("Box3f")
//         // Constructors
//         .constructor<>()
//         .constructor<const Vector3f&, const Vector3f&>()
        
//         // Static factory methods
//         .class_function("fromMinAndSize", &Box3f::fromMinAndSize)
//         .class_function("getMinBoxCorner", &Box3f::getMinBoxCorner)
//         .class_function("getMaxBoxCorner", &Box3f::getMaxBoxCorner)
        
//         // Properties
//         .property("min", &Box3f::min)
//         .property("max", &Box3f::max)
        
//         // Methods
//         .function("valid", &Box3f::valid)
//         .function("center", &Box3f::center)
//         .function("corner", &Box3f::corner)
//         .function("size", &Box3f::size)
//         .function("diagonal", &Box3f::diagonal)
//         .function("volume", &Box3f::volume)
//         .function("include", select_overload<void(const Vector3f&)>(&Box3f::include))
//         .function("includeBox", select_overload<void(const Box3f&)>(&Box3f::include))
//         .function("contains", select_overload<bool(const Vector3f&) const>(&Box3f::contains))
//         .function("containsBox", select_overload<bool(const Box3f&) const>(&Box3f::contains))
//         .function("getBoxClosestPointTo", &Box3f::getBoxClosestPointTo)
//         .function("intersects", &Box3f::intersects)
//         .function("intersection", &Box3f::intersection)
//         .function("intersect", &Box3f::intersect, return_value_policy::reference())
//         .function("getDistanceSqToBox", select_overload<float(const Box3f&) const>(&Box3f::getDistanceSq))
//         .function("getDistanceSqToPoint", select_overload<float(const Vector3f&) const>(&Box3f::getDistanceSq))
//         .function("expanded", &Box3f::expanded)
//         .function("insignificantlyExpanded", &Box3f::insignificantlyExpanded);
// }
