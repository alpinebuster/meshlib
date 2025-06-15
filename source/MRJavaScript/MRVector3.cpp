#include <emscripten/bind.h>

#include <MRMesh/MRVector3.h>
#include <MRMesh/MRConstants.h>

using namespace emscripten;
using namespace MR;

// Encapsulate the `MR::unitVector3` function to accepts parameters of type int and converts them to float
Vector3<int> unitVector3FromInt( int azimuth, int altitude )
{
    float azimuthF = static_cast< float >( azimuth );
    float altitudeF = static_cast< float >( altitude );

    // Call the original `MR::unitVector3` function to obtain the floating-point result
    Vector3<float> floatResult = unitVector3( azimuthF, altitudeF );
    // Convert the floating-point result to int
    return {
        static_cast< int >( floatResult.x ),
        static_cast< int >( floatResult.y ),
        static_cast< int >( floatResult.z )
    };
}

// ------------------------------------------------------------------------
// 1. Bind the Embind interface for Vector3<float> (i.e., Vector3F)
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( Vector3FModule )
{
    class_<Vector3<float>>( "Vector3F" )
        // Constructor: Parameterless construction and construction of three floating-point parameters (x,y,z)
        .constructor<>()
        .constructor<float, float, float>()

        // Expose the member variables x, y, and z as attributes to the JS
        .property( "x", &Vector3<float>::x )
        .property( "y", &Vector3<float>::y )
        .property( "z", &Vector3<float>::z )

        // Member function binding
        .function( "lengthSq", &Vector3<float>::lengthSq )
        .function( "length", &Vector3<float>::length )
        .function( "normalized", &Vector3<float>::normalized )
        .function( "furthestBasisVector", &Vector3<float>::furthestBasisVector )
        .function( "perpendicular", &Vector3<float>::perpendicular )
        .function( "unsignZeroValues", &Vector3<float>::unsignZeroValues )
        .function( "isFinite", &Vector3<float>::isFinite )
        // The subscript operator cannot be directly bound as operator[],
        // let's change it to two functions, get(i), set(i,val).
        .function( "get", select_overload<const float& ( int ) const>( &Vector3<float>::operator[] ) )
        .function( "set", select_overload<float& ( int )>( &Vector3<float>::operator[] ) )

        // Bind the static factory function
        .class_function( "diagonal", &Vector3<float>::diagonal )
        .class_function( "plusX", &Vector3<float>::plusX )
        .class_function( "plusY", &Vector3<float>::plusY )
        .class_function( "plusZ", &Vector3<float>::plusZ )
        .class_function( "minusX", &Vector3<float>::minusX )
        .class_function( "minusY", &Vector3<float>::minusY )
        .class_function( "minusZ", &Vector3<float>::minusZ );

    // Bind `std::pair<Vector3f, Vector3f>`
    value_array<std::pair<Vector3<float>, Vector3<float>>>( "Vector3FPair" )
        .element( &std::pair<Vector3<float>, Vector3<float>>::first )
        .element( &std::pair<Vector3<float>, Vector3<float>>::second );

    // Below, bind the free functions related to Vector3<float> as well
    function( "distanceSqF", select_overload<float( const Vector3<float>&, const Vector3<float>& )>( &distanceSq<float> ) );
    function( "distanceF", select_overload<float( const Vector3<float>&, const Vector3<float>& )>( &distance<float> ) );
    function( "crossF", select_overload<Vector3<float>( const Vector3<float>&, const Vector3<float>& )>( &cross<float> ) );
    function( "dotF", select_overload<float( const Vector3<float>&, const Vector3<float>& )>( &dot<float> ) );
    function( "sqrF", select_overload<float( const Vector3<float>& )>( &sqr<float> ) );
    function( "mixedF", select_overload<float( const Vector3<float>&, const Vector3<float>&, const Vector3<float>& )>( &mixed<float> ) );
    function( "multF", select_overload<Vector3<float>( const Vector3<float>&, const Vector3<float>& )>( &mult<float> ) );
    function( "divF", select_overload<Vector3<float>( const Vector3<float>&, const Vector3<float>& )>( &div<float> ) );
    function( "angleF", select_overload<float( const Vector3<float>&, const Vector3<float>& )>( &angle<float> ) );
    function( "unitVector3F", select_overload<Vector3<float>( float, float )>( &unitVector3<float> ) );
}

// ------------------------------------------------------------------------
// 2. Bind the Embind interface for Vector3<int> (i.e., Vector3I)
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( Vector3IModule )
{
    class_<Vector3<int>>( "Vector3I" )
        .constructor<>()
        .constructor<int, int, int>()

        .property( "x", &Vector3<int>::x )
        .property( "y", &Vector3<int>::y )
        .property( "z", &Vector3<int>::z )

        .function( "lengthSq", &Vector3<int>::lengthSq )
        // NOTE: For integer vectors, `length()`, `normalized()`, `furthestBasisVector()`, `perpendicular()`, `unsignZeroValues()` and `isFinite()` is not working
        .function( "length", &Vector3<int>::length )
        .function( "normalized", optional_override([](const Vector3<int>& self) -> Vector3<float> {
            return Vector3<float>(
                static_cast<float>(self.x), 
                static_cast<float>(self.y), 
                static_cast<float>(self.z)
            ).normalized();
        }))
        .function( "furthestBasisVector", &Vector3<int>::furthestBasisVector )
        .function( "perpendicular", optional_override([](const Vector3<int>& self) -> std::pair<Vector3<float>, Vector3<float>> {
            // Convert the integer vector to floating-point
            Vector3<float> floatVec(
                static_cast<float>(self.x), 
                static_cast<float>(self.y), 
                static_cast<float>(self.z)
            );
            
            // Call the perpendicular method on the floating-point version
            auto result = floatVec.perpendicular();
            
            // Return the pair of perpendicular vectors as floating-point vectors
            return result;
        }))
        .function( "unsignZeroValues", optional_override([](Vector3<int>& self) -> Vector3<float> {
            Vector3<float> floatVec(
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
        .function( "isFinite", optional_override([](Vector3<int>& v) {
            Vector3<float> floatVec(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z));
            return floatVec.isFinite();
        }))
        .function( "get", select_overload<const int& ( int ) const>( &Vector3<int>::operator[] ) )
        .function( "set", select_overload<int& ( int )>( &Vector3<int>::operator[] ) )

        .class_function( "diagonal", &Vector3<int>::diagonal )
        .class_function( "plusX", &Vector3<int>::plusX )
        .class_function( "plusY", &Vector3<int>::plusY )
        .class_function( "plusZ", &Vector3<int>::plusZ )
        .class_function( "minusX", &Vector3<int>::minusX )
        .class_function( "minusY", &Vector3<int>::minusY )
        .class_function( "minusZ", &Vector3<int>::minusZ );

    value_array<std::pair<Vector3<int>, Vector3<int>>>( "Vector3IPair" )
        .element( &std::pair<Vector3<int>, Vector3<int>>::first )
        .element( &std::pair<Vector3<int>, Vector3<int>>::second );

    // Bind the free functions related to Vector3<int>
    function( "distanceSqI", select_overload<int( const Vector3<int>&, const Vector3<int>& )>( &distanceSq<int> ) );
    function( "sqrI", select_overload<int( const Vector3<int>& )>( &sqr<int> ) );
    // The cross, dot, mixed, mult, div, etc. can also be bound to integers, but it should be noted that the result type is also an integer
    function( "crossI", select_overload<Vector3<int>( const Vector3<int>&, const Vector3<int>& )>( &cross<int> ) );
    function( "dotI", select_overload<int( const Vector3<int>&, const Vector3<int>& )>( &dot<int> ) );
    function( "mixedI", select_overload<int( const Vector3<int>&, const Vector3<int>&, const Vector3<int>& )>( &mixed<int> ) );
    function( "multI", select_overload<Vector3<int>( const Vector3<int>&, const Vector3<int>& )>( &mult<int> ) );
    function( "divI", select_overload<Vector3<int>( const Vector3<int>&, const Vector3<int>& )>( &div<int> ) );
    function( "angleI", select_overload<int( const Vector3<int>&, const Vector3<int>& )>( &angle<int> ) );
    // We don't use `function( "unitVector3I", select_overload<Vector3<int>( int, int )>( &unitVector3<int> ) );` directly as `std::cos` and `std::sin` doesn't supports `int`
    function( "unitVector3I", &unitVector3FromInt );
}

// ------------------------------------------------------------------------
// 3. Bind the Embind interface for Vector3<double> (i.e., Vector3D)
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( Vector3DModule )
{
    class_<Vector3<double>>( "Vector3D" )
        .constructor<>()
        .constructor<double, double, double>()

        .property( "x", &Vector3<double>::x )
        .property( "y", &Vector3<double>::y )
        .property( "z", &Vector3<double>::z )

        .function( "lengthSq", &Vector3<double>::lengthSq )
        .function( "length", &Vector3<double>::length )
        .function( "normalized", &Vector3<double>::normalized )
        .function( "furthestBasisVector", &Vector3<double>::furthestBasisVector )
        .function( "perpendicular", &Vector3<double>::perpendicular )
        .function( "unsignZeroValues", &Vector3<double>::unsignZeroValues )
        .function( "isFinite", &Vector3<double>::isFinite )
        .function( "get", select_overload<const double& ( int ) const>( &Vector3<double>::operator[] ) )
        .function( "set", select_overload<double& ( int )>( &Vector3<double>::operator[] ) )

        .class_function( "diagonal", &Vector3<double>::diagonal )
        .class_function( "plusX", &Vector3<double>::plusX )
        .class_function( "plusY", &Vector3<double>::plusY )
        .class_function( "plusZ", &Vector3<double>::plusZ )
        .class_function( "minusX", &Vector3<double>::minusX )
        .class_function( "minusY", &Vector3<double>::minusY )
        .class_function( "minusZ", &Vector3<double>::minusZ );

    // Bind `std::pair<Vector3d, Vector3d>`
    value_array<std::pair<Vector3<double>, Vector3<double>>>( "Vector3DPair" )
        .element( &std::pair<Vector3<double>, Vector3<double>>::first )
        .element( &std::pair<Vector3<double>, Vector3<double>>::second );

    // Below, bind the free functions related to Vector3<double> as well
    function( "distanceSqD", select_overload<double( const Vector3<double>&, const Vector3<double>& )>( &distanceSq<double> ) );
    function( "distanceD", select_overload<double( const Vector3<double>&, const Vector3<double>& )>( &distance<double> ) );
    function( "crossD", select_overload<Vector3<double>( const Vector3<double>&, const Vector3<double>& )>( &cross<double> ) );
    function( "dotD", select_overload<double( const Vector3<double>&, const Vector3<double>& )>( &dot<double> ) );
    function( "sqrD", select_overload<double( const Vector3<double>& )>( &sqr<double> ) );
    function( "mixedD", select_overload<double( const Vector3<double>&, const Vector3<double>&, const Vector3<double>& )>( &mixed<double> ) );
    function( "multD", select_overload<Vector3<double>( const Vector3<double>&, const Vector3<double>& )>( &mult<double> ) );
    function( "divD", select_overload<Vector3<double>( const Vector3<double>&, const Vector3<double>& )>( &div<double> ) );
    function( "angleD", select_overload<double( const Vector3<double>&, const Vector3<double>& )>( &angle<double> ) );
    function( "unitVector3D", select_overload<Vector3<double>( double, double )>( &unitVector3<double> ) );
}

// ------------------------------------------------------------------------
// 4. Bind the Embind interface for Vector3<long long> (i.e., Vector3LL)
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( Vector3LLModule )
{
    class_<Vector3<long long>>( "Vector3LL" )
        .constructor<>()
        .constructor<long long, long long, long long>()

        .property( "x", &Vector3<long long>::x )
        .property( "y", &Vector3<long long>::y )
        .property( "z", &Vector3<long long>::z )

        .function( "lengthSq", &Vector3<long long>::lengthSq )
        .function( "length", &Vector3<long long>::length )
        .function( "normalized",  optional_override([](const Vector3<long long>& self) -> Vector3<float> {
            return Vector3<float>(
                static_cast<float>(self.x), 
                static_cast<float>(self.y), 
                static_cast<float>(self.z)
            ).normalized();
        }))
        .function( "furthestBasisVector", &Vector3<long long>::furthestBasisVector )
        .function( "perpendicular", optional_override([](const Vector3<long long>& self) -> std::pair<Vector3<float>, Vector3<float>> {
            Vector3<float> floatVec(
                static_cast<float>(self.x), 
                static_cast<float>(self.y), 
                static_cast<float>(self.z)
            );

            auto result = floatVec.perpendicular();
            return result;
        }))
        .function( "unsignZeroValues", optional_override([](Vector3<long long>& self) -> Vector3<float> {
            Vector3<float> floatVec(
                static_cast<float>(self.x),
                static_cast<float>(self.y), 
                static_cast<float>(self.z)
            );
            
            floatVec.unsignZeroValues();
            return floatVec;
        } ) )
        .function( "isFinite", optional_override([](Vector3<long long>& v) {
            Vector3<float> floatVec(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z));
            return floatVec.isFinite();
        }))
        .function( "get", select_overload<const long long& ( int ) const>( &Vector3<long long>::operator[] ) )
        .function( "set", select_overload<long long& ( int )>( &Vector3<long long>::operator[] ) )

        .class_function( "diagonal", &Vector3<long long>::diagonal )
        .class_function( "plusX", &Vector3<long long>::plusX )
        .class_function( "plusY", &Vector3<long long>::plusY )
        .class_function( "plusZ", &Vector3<long long>::plusZ )
        .class_function( "minusX", &Vector3<long long>::minusX )
        .class_function( "minusY", &Vector3<long long>::minusY )
        .class_function( "minusZ", &Vector3<long long>::minusZ );

    // Bind `std::pair<Vector3d, Vector3d>`
    value_array<std::pair<Vector3<long long>, Vector3<long long>>>( "Vector3LLPair" )
        .element( &std::pair<Vector3<long long>, Vector3<long long>>::first )
        .element( &std::pair<Vector3<long long>, Vector3<long long>>::second );

    // Below, bind the free functions related to Vector3<long long> as well
    function( "distanceSqLL", select_overload<long long( const Vector3<long long>&, const Vector3<long long>& )>( &distanceSq<long long> ) );
    function( "distanceLL", select_overload<long long( const Vector3<long long>&, const Vector3<long long>& )>( &distance<long long> ) );
    function( "crossLL", select_overload<Vector3<long long>( const Vector3<long long>&, const Vector3<long long>& )>( &cross<long long> ) );
    function( "dotLL", select_overload<long long( const Vector3<long long>&, const Vector3<long long>& )>( &dot<long long> ) );
    function( "sqrLL", select_overload<long long( const Vector3<long long>& )>( &sqr<long long> ) );
    function( "mixedLL", select_overload<long long( const Vector3<long long>&, const Vector3<long long>&, const Vector3<long long>& )>( &mixed<long long> ) );
    function( "multLL", select_overload<Vector3<long long>( const Vector3<long long>&, const Vector3<long long>& )>( &mult<long long> ) );
    function( "divLL", select_overload<Vector3<long long>( const Vector3<long long>&, const Vector3<long long>& )>( &div<long long> ) );
    function( "angleLL", select_overload<long long( const Vector3<long long>&, const Vector3<long long>& )>( &angle<long long> ) );
    function( "unitVector3LL", optional_override([](long long x, long long y) -> Vector3d {
        double dx = static_cast<double>(x);
        double dy = static_cast<double>(y);
        return unitVector3(dx, dy);
    }));
}
