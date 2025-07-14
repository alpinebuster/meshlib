#include <emscripten/bind.h>

#include <MRMesh/MRVector2.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( Vector2Module )
{
    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector2b`
    // ------------------------------------------------------------------------
    class_<Vector2b>( "Vector2b" )
        .smart_ptr<std::shared_ptr<Vector2b>>( "Vector2bSharedPtr" )

        .constructor<>()
        .constructor<bool, bool>()
        .constructor<const Vector2b&>()

        // Properties
        .property( "x", &Vector2b::x )
        .property( "y", &Vector2b::y )

        // Vector operations
        .function( "length", &Vector2b::length )
        .function( "lengthSq", &Vector2b::lengthSq )
        .function( "get", select_overload<const bool& ( int ) const>( &Vector2b::operator[] ) )
        .function( "set", select_overload<bool& ( int )>( &Vector2b::operator[] ) )

        .class_function( "diagonal", &Vector2b::diagonal )
        .class_function( "plusX", &Vector2b::plusX )
        .class_function( "plusY", &Vector2b::plusY )
        .class_function( "minusX", &Vector2b::minusX )
        .class_function( "minusY", &Vector2b::minusY );

    
    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector2i`
    // ------------------------------------------------------------------------
    class_<Vector2i>( "Vector2i" )
        .smart_ptr<std::shared_ptr<Vector2i>>( "Vector2iSharedPtr" )
    
        .constructor<>()
        .constructor<int, int>()
        .constructor<const Vector2i&>()

        // Properties
        .property( "x", &Vector2i::x )
        .property( "y", &Vector2i::y )

        // Vector operations
        .function( "length", &Vector2i::length )
        .function( "lengthSq", &Vector2i::lengthSq )
        .function( "perpendicular", &Vector2i::perpendicular )
        .function( "furthestBasisVector", &Vector2i::furthestBasisVector )
        .function( "get", select_overload<const int& ( int ) const>( &Vector2i::operator[] ) )
        .function( "set", select_overload<int& ( int )>( &Vector2i::operator[] ) )

        .class_function( "diagonal", &Vector2i::diagonal )
        .class_function( "plusX", &Vector2i::plusX )
        .class_function( "plusY", &Vector2i::plusY )
        .class_function( "minusX", &Vector2i::minusX )
        .class_function( "minusY", &Vector2i::minusY );

    
    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector2ll`
    // ------------------------------------------------------------------------
    class_<Vector2ll>( "Vector2ll" )
        .smart_ptr<std::shared_ptr<Vector2ll>>( "Vector2llSharedPtr" )
    
        .constructor<>();


    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector2f`
    // ------------------------------------------------------------------------
    class_<Vector2f>( "Vector2f" )
        .smart_ptr<std::shared_ptr<Vector2f>>( "Vector2fSharedPtr" )

        .constructor<>()                      // Default constructor (0,0)
        .constructor<float, float>()          // From two floats
        .constructor<const Vector2f&>() // Copy constructor

        // Properties - direct access to x,y components
        .property( "x", &Vector2f::x )
        .property( "y", &Vector2f::y )

        // Vector operations
        .function( "length", &Vector2f::length )
        .function( "lengthSq", &Vector2f::lengthSq )
        .function( "normalized", &Vector2f::normalized )
        .function( "perpendicular", &Vector2f::perpendicular )
        .function( "isFinite", &Vector2f::isFinite )
        .function( "furthestBasisVector", &Vector2f::furthestBasisVector )
        .function( "get", select_overload<const float& ( int ) const>( &Vector2f::operator[] ) )
        .function( "set", select_overload<float& ( int )>( &Vector2f::operator[] ) )

        .class_function( "diagonal", &Vector2f::diagonal )
        .class_function( "plusX", &Vector2f::plusX )
        .class_function( "plusY", &Vector2f::plusY )
        .class_function( "minusX", &Vector2f::minusX )
        .class_function( "minusY", &Vector2f::minusY );


    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Vector2d`
    // ------------------------------------------------------------------------
    class_<Vector2d>( "Vector2d" )
        .smart_ptr<std::shared_ptr<Vector2d>>( "Vector2dSharedPtr" )

        .constructor<>();
}
