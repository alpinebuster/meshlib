#include <emscripten/bind.h>

#include <MRMesh/MRVector2.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( Vector2FModule )
{
    class_<Vector2<float>>( "Vector2F" )
        .constructor<>()                      // Default constructor (0,0)
        .constructor<float, float>()          // From two floats
        .constructor<const Vector2<float>&>() // Copy constructor

        // Properties - direct access to x,y components
        .property( "x", &Vector2<float>::x )
        .property( "y", &Vector2<float>::y )

        // Vector operations
        .function( "length", &Vector2<float>::length )
        .function( "lengthSq", &Vector2<float>::lengthSq )
        .function( "normalized", &Vector2<float>::normalized )
        .function( "perpendicular", &Vector2<float>::perpendicular )
        .function( "isFinite", &Vector2<float>::isFinite )
        .function( "furthestBasisVector", &Vector2<float>::furthestBasisVector )
        .function( "get", select_overload<const float& ( int ) const>( &Vector2<float>::operator[] ) )
        .function( "set", select_overload<float& ( int )>( &Vector2<float>::operator[] ) )

        .class_function( "diagonal", &Vector2<float>::diagonal )
        .class_function( "plusX", &Vector2<float>::plusX )
        .class_function( "plusY", &Vector2<float>::plusY )
        .class_function( "minusX", &Vector2<float>::minusX )
        .class_function( "minusY", &Vector2<float>::minusY );
}

EMSCRIPTEN_BINDINGS( Vector2IModule )
{
    class_<Vector2<int>>( "Vector2I" )
        .constructor<>()
        .constructor<int, int>()
        .constructor<const Vector2<int>&>()

        // Properties
        .property( "x", &Vector2<int>::x )
        .property( "y", &Vector2<int>::y )

        // Vector operations
        .function( "length", &Vector2<int>::length )
        .function( "lengthSq", &Vector2<int>::lengthSq )
        .function( "perpendicular", &Vector2<int>::perpendicular )
        .function( "furthestBasisVector", &Vector2<int>::furthestBasisVector )
        .function( "get", select_overload<const int& ( int ) const>( &Vector2<int>::operator[] ) )
        .function( "set", select_overload<int& ( int )>( &Vector2<int>::operator[] ) )

        .class_function( "diagonal", &Vector2<int>::diagonal )
        .class_function( "plusX", &Vector2<int>::plusX )
        .class_function( "plusY", &Vector2<int>::plusY )
        .class_function( "minusX", &Vector2<int>::minusX )
        .class_function( "minusY", &Vector2<int>::minusY );
}

EMSCRIPTEN_BINDINGS( Vector2BModule )
{
    class_<Vector2<bool>>( "Vector2B" )
        .constructor<>()
        .constructor<bool, bool>()
        .constructor<const Vector2<bool>&>()

        // Properties
        .property( "x", &Vector2<bool>::x )
        .property( "y", &Vector2<bool>::y )

        // Vector operations
        .function( "length", &Vector2<bool>::length )
        .function( "lengthSq", &Vector2<bool>::lengthSq )
        .function( "get", select_overload<const bool& ( int ) const>( &Vector2<bool>::operator[] ) )
        .function( "set", select_overload<bool& ( int )>( &Vector2<bool>::operator[] ) )

        .class_function( "diagonal", &Vector2<bool>::diagonal )
        .class_function( "plusX", &Vector2<bool>::plusX )
        .class_function( "plusY", &Vector2<bool>::plusY )
        .class_function( "minusX", &Vector2<bool>::minusX )
        .class_function( "minusY", &Vector2<bool>::minusY );
}
