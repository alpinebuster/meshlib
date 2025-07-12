#include <emscripten/bind.h>

#include <MRMesh/MRVector3.h>
#include <MRMesh/MRConstants.h>

using namespace emscripten;
using namespace MR;

// Encapsulate the `MR::unitVector3` function to accepts parameters of type int and converts them to float
Vector3i unitVector3FromInt( int azimuth, int altitude )
{
    float azimuthF = static_cast< float >( azimuth );
    float altitudeF = static_cast< float >( altitude );

    // Call the original `MR::unitVector3` function to obtain the floating-point result
    Vector3f floatResult = unitVector3( azimuthF, altitudeF );
    // Convert the floating-point result to int
    return {
        static_cast< int >( floatResult.x ),
        static_cast< int >( floatResult.y ),
        static_cast< int >( floatResult.z )
    };
}

EMSCRIPTEN_BINDINGS( Vector3Module )
{
    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector3f`
    // ------------------------------------------------------------------------
    value_array<std::pair<Vector3f, Vector3f>>( "Vector3fPair" )
        .element( &std::pair<Vector3f, Vector3f>::first )
        .element( &std::pair<Vector3f, Vector3f>::second );
    class_<Vector3f>( "Vector3f" )
        // Constructor: Parameterless construction and construction of three floating-point parameters (x,y,z)
        .constructor<>()
        .constructor<float, float, float>()

        // Expose the member variables x, y, and z as attributes to the JS
        .property( "x", &Vector3f::x )
        .property( "y", &Vector3f::y )
        .property( "z", &Vector3f::z )

        // Member function binding
        .function( "lengthSq", &Vector3f::lengthSq )
        .function( "length", &Vector3f::length )
        .function( "normalized", &Vector3f::normalized )
        .function( "furthestBasisVector", &Vector3f::furthestBasisVector )
        .function( "perpendicular", &Vector3f::perpendicular )
        .function( "unsignZeroValues", &Vector3f::unsignZeroValues )
        .function( "isFinite", &Vector3f::isFinite )
        // The subscript operator cannot be directly bound as operator[],
        // let's change it to two functions, get(i), set(i,val).
        .function( "get", select_overload<const float& ( int ) const>( &Vector3f::operator[] ) )
        .function( "set", select_overload<float& ( int )>( &Vector3f::operator[] ) )

        // Bind the static factory function
        .class_function( "diagonal", &Vector3f::diagonal )
        .class_function( "plusX", &Vector3f::plusX )
        .class_function( "plusY", &Vector3f::plusY )
        .class_function( "plusZ", &Vector3f::plusZ )
        .class_function( "minusX", &Vector3f::minusX )
        .class_function( "minusY", &Vector3f::minusY )
        .class_function( "minusZ", &Vector3f::minusZ );

    // Below, bind the free functions related to Vector3f as well
    function( "distanceSqf", select_overload<float( const Vector3f&, const Vector3f& )>( &distanceSq<float> ) );
    function( "distancef", select_overload<float( const Vector3f&, const Vector3f& )>( &distance<float> ) );
    function( "crossf", select_overload<Vector3f( const Vector3f&, const Vector3f& )>( &cross<float> ) );
    function( "dotf", select_overload<float( const Vector3f&, const Vector3f& )>( &dot<float> ) );
    function( "sqrf", select_overload<float( const Vector3f& )>( &sqr<float> ) );
    function( "mixedf", select_overload<float( const Vector3f&, const Vector3f&, const Vector3f& )>( &mixed<float> ) );
    function( "multf", select_overload<Vector3f( const Vector3f&, const Vector3f& )>( &mult<float> ) );
    function( "divf", select_overload<Vector3f( const Vector3f&, const Vector3f& )>( &div<float> ) );
    function( "anglef", select_overload<float( const Vector3f&, const Vector3f& )>( &angle<float> ) );
    function( "unitVector3f", select_overload<Vector3f( float, float )>( &unitVector3<float> ) );


    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector3b`
    // ------------------------------------------------------------------------
    value_array<std::pair<Vector3b, Vector3b>>( "Vector3bPair" )
        .element( &std::pair<Vector3b, Vector3b>::first )
        .element( &std::pair<Vector3b, Vector3b>::second );
    class_<Vector3b>( "Vector3b" )
        .constructor<>()
        .constructor<bool, bool, bool>()

        .property( "x", &Vector3b::x )
        .property( "y", &Vector3b::y )
        .property( "z", &Vector3b::z )

        .function( "lengthSq", &Vector3b::lengthSq )
        .function( "length", &Vector3b::length )
        .function( "get", select_overload<const bool& ( int ) const>( &Vector3b::operator[] ) )
        .function( "set", select_overload<bool& ( int )>( &Vector3b::operator[] ) )

        .class_function( "diagonal", &Vector3b::diagonal )
        .class_function( "plusX", &Vector3b::plusX )
        .class_function( "plusY", &Vector3b::plusY )
        .class_function( "plusZ", &Vector3b::plusZ )
        .class_function( "minusX", &Vector3b::minusX )
        .class_function( "minusY", &Vector3b::minusY )
        .class_function( "minusZ", &Vector3b::minusZ );

    // Bind the free functions related to Vector3b
    function( "distanceSqb", select_overload<bool( const Vector3b&, const Vector3b& )>( &distanceSq<bool> ) );
    function( "sqrb", select_overload<bool( const Vector3b& )>( &sqr<bool> ) );


    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector3i`
    // ------------------------------------------------------------------------
    value_array<std::pair<Vector3i, Vector3i>>( "Vector3iPair" )
        .element( &std::pair<Vector3i, Vector3i>::first )
        .element( &std::pair<Vector3i, Vector3i>::second );
    class_<Vector3i>( "Vector3i" )
        .constructor<>()
        .constructor<int, int, int>()

        .property( "x", &Vector3i::x )
        .property( "y", &Vector3i::y )
        .property( "z", &Vector3i::z )

        .function( "lengthSq", &Vector3i::lengthSq )
        // NOTE: For integer vectors, `length()`, `normalized()`, `furthestBasisVector()`, `perpendicular()`, `unsignZeroValues()` and `isFinite()` is not working
        .function( "length", &Vector3i::length )
        .function( "normalized", optional_override([](const Vector3i& self) -> Vector3f {
            return Vector3f(
                static_cast<float>(self.x), 
                static_cast<float>(self.y), 
                static_cast<float>(self.z)
            ).normalized();
        }))
        .function( "furthestBasisVector", &Vector3i::furthestBasisVector )
        .function( "perpendicular", optional_override([](const Vector3i& self) -> std::pair<Vector3f, Vector3f> {
            // Convert the integer vector to floating-point
            Vector3f floatVec(
                static_cast<float>(self.x), 
                static_cast<float>(self.y), 
                static_cast<float>(self.z)
            );
            
            // Call the perpendicular method on the floating-point version
            auto result = floatVec.perpendicular();
            
            // Return the pair of perpendicular vectors as floating-point vectors
            return result;
        }))
        .function( "unsignZeroValues", optional_override([](Vector3i& self) -> Vector3f {
            Vector3f floatVec(
                static_cast<float>(self.x),
                static_cast<float>(self.y), 
                static_cast<float>(self.z)
            );
            
            floatVec.unsignZeroValues();
            // Convert back to integers
            // Note: this conversion will truncate any fractional parts
            // self.x = static_cast<int>(floatVec.x);
            // self.y = static_cast<int>(floatVec.y);
            // self.z = static_cast< int >( floatVec.z );

            return floatVec;
        } ) )
        .function( "isFinite", optional_override([](Vector3i& v) {
            Vector3f floatVec(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z));
            return floatVec.isFinite();
        }))
        .function( "get", select_overload<const int& ( int ) const>( &Vector3i::operator[] ) )
        .function( "set", select_overload<int& ( int )>( &Vector3i::operator[] ) )

        .class_function( "diagonal", &Vector3i::diagonal )
        .class_function( "plusX", &Vector3i::plusX )
        .class_function( "plusY", &Vector3i::plusY )
        .class_function( "plusZ", &Vector3i::plusZ )
        .class_function( "minusX", &Vector3i::minusX )
        .class_function( "minusY", &Vector3i::minusY )
        .class_function( "minusZ", &Vector3i::minusZ );

    // Bind the free functions related to Vector3i
    function( "distanceSqi", select_overload<int( const Vector3i&, const Vector3i& )>( &distanceSq<int> ) );
    function( "sqri", select_overload<int( const Vector3i& )>( &sqr<int> ) );
    // The cross, dot, mixed, mult, div, etc. can also be bound to integers, but it should be noted that the result type is also an integer
    function( "crossi", select_overload<Vector3i( const Vector3i&, const Vector3i& )>( &cross<int> ) );
    function( "doti", select_overload<int( const Vector3i&, const Vector3i& )>( &dot<int> ) );
    function( "mixedi", select_overload<int( const Vector3i&, const Vector3i&, const Vector3i& )>( &mixed<int> ) );
    function( "multi", select_overload<Vector3i( const Vector3i&, const Vector3i& )>( &mult<int> ) );
    function( "divi", select_overload<Vector3i( const Vector3i&, const Vector3i& )>( &div<int> ) );
    function( "anglei", select_overload<int( const Vector3i&, const Vector3i& )>( &angle<int> ) );
    // We don't use `function( "unitVector3I", select_overload<Vector3i( int, int )>( &unitVector3<int> ) );` directly as `std::cos` and `std::sin` doesn't supports `int`
    function( "unitVector3i", &unitVector3FromInt );


    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector3ll`
    // ------------------------------------------------------------------------
    value_array<std::pair<Vector3ll, Vector3ll>>( "Vector3llPair" )
        .element( &std::pair<Vector3ll, Vector3ll>::first )
        .element( &std::pair<Vector3ll, Vector3ll>::second );
    class_<Vector3ll>( "Vector3ll" )
        .constructor<>()
        .constructor<long long, long long, long long>()

        .property( "x", &Vector3ll::x )
        .property( "y", &Vector3ll::y )
        .property( "z", &Vector3ll::z )

        .function( "lengthSq", &Vector3ll::lengthSq )
        .function( "length", &Vector3ll::length )
        .function( "normalized",  optional_override([](const Vector3ll& self) -> Vector3f {
            return Vector3f(
                static_cast<float>(self.x), 
                static_cast<float>(self.y), 
                static_cast<float>(self.z)
            ).normalized();
        }))
        .function( "furthestBasisVector", &Vector3ll::furthestBasisVector )
        .function( "perpendicular", optional_override([](const Vector3ll& self) -> std::pair<Vector3f, Vector3f> {
            Vector3f floatVec(
                static_cast<float>(self.x), 
                static_cast<float>(self.y), 
                static_cast<float>(self.z)
            );

            auto result = floatVec.perpendicular();
            return result;
        }))
        .function( "unsignZeroValues", optional_override([](Vector3ll& self) -> Vector3f {
            Vector3f floatVec(
                static_cast<float>(self.x),
                static_cast<float>(self.y), 
                static_cast<float>(self.z)
            );
            
            floatVec.unsignZeroValues();
            return floatVec;
        } ) )
        .function( "isFinite", optional_override([](Vector3ll& v) {
            Vector3f floatVec(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z));
            return floatVec.isFinite();
        }))
        .function( "get", select_overload<const long long& ( int ) const>( &Vector3ll::operator[] ) )
        .function( "set", select_overload<long long& ( int )>( &Vector3ll::operator[] ) )

        .class_function( "diagonal", &Vector3ll::diagonal )
        .class_function( "plusX", &Vector3ll::plusX )
        .class_function( "plusY", &Vector3ll::plusY )
        .class_function( "plusZ", &Vector3ll::plusZ )
        .class_function( "minusX", &Vector3ll::minusX )
        .class_function( "minusY", &Vector3ll::minusY )
        .class_function( "minusZ", &Vector3ll::minusZ );

    // Below, bind the free functions related to Vector3ll as well
    function( "distanceSqll", select_overload<long long( const Vector3ll&, const Vector3ll& )>( &distanceSq<long long> ) );
    function( "distancell", select_overload<long long( const Vector3ll&, const Vector3ll& )>( &distance<long long> ) );
    function( "crossll", select_overload<Vector3ll( const Vector3ll&, const Vector3ll& )>( &cross<long long> ) );
    function( "dotll", select_overload<long long( const Vector3ll&, const Vector3ll& )>( &dot<long long> ) );
    function( "sqrll", select_overload<long long( const Vector3ll& )>( &sqr<long long> ) );
    function( "mixedll", select_overload<long long( const Vector3ll&, const Vector3ll&, const Vector3ll& )>( &mixed<long long> ) );
    function( "multll", select_overload<Vector3ll( const Vector3ll&, const Vector3ll& )>( &mult<long long> ) );
    function( "divll", select_overload<Vector3ll( const Vector3ll&, const Vector3ll& )>( &div<long long> ) );
    function( "anglell", select_overload<long long( const Vector3ll&, const Vector3ll& )>( &angle<long long> ) );
    function( "unitVector3ll", optional_override([](long long x, long long y) -> Vector3d {
        double dx = static_cast<double>(x);
        double dy = static_cast<double>(y);
        return unitVector3(dx, dy);
    }));


    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector3d`
    // ------------------------------------------------------------------------
    value_array<std::pair<Vector3d, Vector3d>>( "Vector3DPair" )
        .element( &std::pair<Vector3d, Vector3d>::first )
        .element( &std::pair<Vector3d, Vector3d>::second );
    class_<Vector3d>( "Vector3d" )
        .constructor<>()
        .constructor<double, double, double>()

        .property( "x", &Vector3d::x )
        .property( "y", &Vector3d::y )
        .property( "z", &Vector3d::z )

        .function( "lengthSq", &Vector3d::lengthSq )
        .function( "length", &Vector3d::length )
        .function( "normalized", &Vector3d::normalized )
        .function( "furthestBasisVector", &Vector3d::furthestBasisVector )
        .function( "perpendicular", &Vector3d::perpendicular )
        .function( "unsignZeroValues", &Vector3d::unsignZeroValues )
        .function( "isFinite", &Vector3d::isFinite )
        .function( "get", select_overload<const double& ( int ) const>( &Vector3d::operator[] ) )
        .function( "set", select_overload<double& ( int )>( &Vector3d::operator[] ) )

        .class_function( "diagonal", &Vector3d::diagonal )
        .class_function( "plusX", &Vector3d::plusX )
        .class_function( "plusY", &Vector3d::plusY )
        .class_function( "plusZ", &Vector3d::plusZ )
        .class_function( "minusX", &Vector3d::minusX )
        .class_function( "minusY", &Vector3d::minusY )
        .class_function( "minusZ", &Vector3d::minusZ );

    // Below, bind the free functions related to Vector3d as well
    function( "distanceSqd", select_overload<double( const Vector3d&, const Vector3d& )>( &distanceSq<double> ) );
    function( "distanced", select_overload<double( const Vector3d&, const Vector3d& )>( &distance<double> ) );
    function( "crossd", select_overload<Vector3d( const Vector3d&, const Vector3d& )>( &cross<double> ) );
    function( "dotd", select_overload<double( const Vector3d&, const Vector3d& )>( &dot<double> ) );
    function( "sqrd", select_overload<double( const Vector3d& )>( &sqr<double> ) );
    function( "mixedd", select_overload<double( const Vector3d&, const Vector3d&, const Vector3d& )>( &mixed<double> ) );
    function( "multd", select_overload<Vector3d( const Vector3d&, const Vector3d& )>( &mult<double> ) );
    function( "divd", select_overload<Vector3d( const Vector3d&, const Vector3d& )>( &div<double> ) );
    function( "angled", select_overload<double( const Vector3d&, const Vector3d& )>( &angle<double> ) );
    function( "unitVector3d", select_overload<Vector3d( double, double )>( &unitVector3<double> ) );
}
