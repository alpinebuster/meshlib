#include <emscripten/bind.h>

#include "MRMesh/MRVector4.h"
#include "MRMesh/MRConstants.h"

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( Vector4fModule )
{
    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector4b`
    // ------------------------------------------------------------------------
    class_<Vector4b>( "Vector4b" )
        .constructor<>();


    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector4i`
    // ------------------------------------------------------------------------
    class_<Vector4i>( "Vector4i" )
        .constructor<>()
        .constructor<int, int, int, int>()

        .property( "x", &Vector4i::x )
        .property( "y", &Vector4i::y )
        .property( "z", &Vector4i::z )
        .property( "w", &Vector4i::w )

        .function( "lengthSq", &Vector4i::lengthSq )
        // Integers are not bound to `length()` and `normalized()`
        .function( "get", select_overload<const int& ( int ) const>( &Vector4i::operator[] ) )
        .function( "set", select_overload<int& ( int )>( &Vector4i::operator[] ) )
        .class_function( "diagonal", &Vector4i::diagonal );

    // Bind the free function related to `Vector4i`
    function( "distanceSq4i", select_overload<int( const Vector4i&, const Vector4i& )>( &distanceSq<int> ) );
    function( "distance4i", select_overload<int( const Vector4i&, const Vector4i& )>( &distance<int> ) );
    function( "dot4i", select_overload<int( const Vector4i&, const Vector4i& )>( &dot<int> ) );
    function( "sqr4i", select_overload<int( const Vector4i& )>( &sqr<int> ) );
    function( "mult4i", select_overload<Vector4i( const Vector4i&, const Vector4i& )>( &mult<int> ) );
    function( "div4i", select_overload<Vector4i( const Vector4i&, const Vector4i& )>( &div<int> ) );


    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector4ll`
    // ------------------------------------------------------------------------
    class_<Vector4ll>( "Vector4ll" )
        .constructor<>();


    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector4f`
    // ------------------------------------------------------------------------
    class_<Vector4f>( "Vector4f" )
        .constructor<>()
        .constructor<float, float, float, float>()

        .property( "x", &Vector4f::x )
        .property( "y", &Vector4f::y )
        .property( "z", &Vector4f::z )
        .property( "w", &Vector4f::w )

        .function( "lengthSq", &Vector4f::lengthSq )
        .function( "length", &Vector4f::length )
        .function( "normalized", &Vector4f::normalized )
        .function( "proj3d", &Vector4f::proj3d )
        .function( "isFinite", &Vector4f::isFinite )
        .function( "get", select_overload<const float& ( int ) const>( &Vector4f::operator[] ) )
        .function( "set", select_overload<float& ( int )>( &Vector4f::operator[] ) )

        .class_function( "diagonal", &Vector4f::diagonal );

    // Bind the free function related to `Vector4f`
    function( "distanceSq4f", select_overload<float( const Vector4f&, const Vector4f& )>( &distanceSq<float> ) );
    function( "distance4f", select_overload<float( const Vector4f&, const Vector4f& )>( &distance<float> ) );
    function( "dot4f", select_overload<float( const Vector4f&, const Vector4f& )>( &dot<float> ) );
    function( "sqr4f", select_overload<float( const Vector4f& )>( &sqr<float> ) );
    function( "mult4f", select_overload<Vector4f( const Vector4f&, const Vector4f& )>( &mult<float> ) );
    function( "div4f", select_overload<Vector4f( const Vector4f&, const Vector4f& )>( &div<float> ) );
    
    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector4d`
    // ------------------------------------------------------------------------
    class_<Vector4d>( "Vector4d" )
        .constructor<>();
}
