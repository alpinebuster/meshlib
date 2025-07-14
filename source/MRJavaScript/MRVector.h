#pragma once

#include <string>

#include <emscripten/bind.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRVector4.h>

using namespace emscripten;
using namespace MR;


template<typename VecType>
auto bindTypedVector( const std::string& className )
{
    auto cls = class_<VecType>( className.c_str() )
        .template constructor<>()
        .template constructor<size_t>()
        .template constructor<size_t, const typename VecType::value_type &>()

        .function( "size", &VecType::size )
        .function( "empty", &VecType::empty )
        .function( "clear", &VecType::clear )

        .function( "get", select_overload<const typename VecType::value_type & ( size_t ) const>( &VecType::operator[] ) )
        .function( "set", select_overload<typename VecType::value_type & ( size_t )>( &VecType::operator[] ))

        .function( "resize", select_overload<void( size_t )>( &VecType::resize ) )
        .function( "resizeWithValue", select_overload<void( size_t, const typename VecType::value_type & )>( &VecType::resize ) )
        .function( "resizeWithReserve", select_overload<void( size_t )>( &VecType::resizeWithReserve ) )
        .function( "resizeWithReserveAndValue", select_overload<void( size_t, const typename VecType::value_type & )>( &VecType::resizeWithReserve ) )

        .function( "autoResizeAt", &VecType::autoResizeAt, allow_raw_pointers() )
        .function( "autoResizeSet", select_overload<void( size_t, typename VecType::value_type )>( &VecType::autoResizeSet ) )

        .function( "pushBack", select_overload<void( const typename VecType::value_type & )>( &VecType::push_back ) )
        .function( "popBack", &VecType::pop_back )

        .function( "front", select_overload<const typename VecType::value_type & ( ) const>( &VecType::front ) )
        .function( "back", select_overload<const typename VecType::value_type & ( ) const>( &VecType::back ) )

        .function( "beginId", &VecType::beginId )
        .function( "backId", &VecType::backId )
        .function( "endId", &VecType::endId )

        .function( "capacity", &VecType::capacity )
        .function( "reserve", &VecType::reserve )
        .function( "heapBytes", &VecType::heapBytes )

        .function("equals", optional_override( [](const VecType& self, const VecType& other ) {return self == other;} ))
        .function("notEquals", optional_override( [](const VecType& self, const VecType& other ) {return self != other;} ))

        .function( "getData", optional_override( [] ( VecType& self )
        {
            return val( typed_memory_view( self.size(), self.data() ) );
        }))
        .function( "getDataConst", optional_override( [] ( const VecType& self )
        {
            return val( typed_memory_view( self.size(), self.data() ) );
        }));

	return cls;
}


template<typename Vec2Type>
auto bindTypedVector2( const std::string& className )
{
    auto cls = class_<Vec2Type>( className.c_str() )
        .template smart_ptr<std::shared_ptr<Vec2Type>>( ( className + "SharedPtr" ).c_str() )

        .template constructor<>()
        .template constructor<typename Vec2Type::ValueType, typename Vec2Type::ValueType>()
        .template constructor<const Vec2Type&>()

        .property( "x", &Vec2Type::x )
        .property( "y", &Vec2Type::y )

        .function( "length", &Vec2Type::length )
        .function( "lengthSq", &Vec2Type::lengthSq )
        .function( "get", select_overload<const typename Vec2Type::ValueType& ( int ) const>( &Vec2Type::operator[] ) )
        .function( "set", select_overload<typename Vec2Type::ValueType& ( int )>( &Vec2Type::operator[] ) )

        .class_function( "diagonal", &Vec2Type::diagonal )
        .class_function( "plusX", &Vec2Type::plusX )
        .class_function( "plusY", &Vec2Type::plusY )
        .class_function( "minusX", &Vec2Type::minusX )
        .class_function( "minusY", &Vec2Type::minusY );

	// `perpendicular()` and `furthestBasisVector()` are not defined for `bool`
	if constexpr ( !std::is_same_v<typename Vec2Type::ValueType, bool> )
	{
		cls.function( "perpendicular", &Vec2Type::perpendicular )
		   .function( "furthestBasisVector", &Vec2Type::furthestBasisVector );
	}
    if constexpr ( !std::is_integral_v<typename Vec2Type::ValueType> )
    {
        cls.function( "normalized", &Vec2Type::normalized );
	}
    if constexpr ( std::is_floating_point_v<typename Vec2Type::ValueType> )
    {
        cls.function( "isFinite", &Vec2Type::isFinite );
	}

	return cls;
}


template<typename Vec3Type>
auto bindTypedVector3( const std::string& name, const std::string& suffix )
{
    using T = Vec3Type::ValueType;

    auto cls = class_<Vec3Type>( name.c_str() )
        .template smart_ptr<std::shared_ptr<Vec3Type>>( ( name + "SharedPtr" ).c_str() )

        .template constructor<>()
        .template constructor<T, T, T>()
        .class_function( "createFromVector2", optional_override( [] ( Vector2<T> v2 )
        {
            return Vec3Type( v2 );
        } ) )

        .property( "x", &Vec3Type::x )
        .property( "y", &Vec3Type::y )
        .property( "z", &Vec3Type::z )

        .function( "lengthSq", &Vec3Type::lengthSq )
        .function( "length", &Vec3Type::length )
        .function( "get", select_overload<const T & ( int ) const>( &Vec3Type::operator[] ) )
        .function( "set", select_overload<T & ( int )>( &Vec3Type::operator[] ) )

        .class_function( "diagonal", &Vec3Type::diagonal )
        .class_function( "plusX", &Vec3Type::plusX )
        .class_function( "plusY", &Vec3Type::plusY )
        .class_function( "plusZ", &Vec3Type::plusZ )
        .class_function( "minusX", &Vec3Type::minusX )
        .class_function( "minusY", &Vec3Type::minusY )
        .class_function( "minusZ", &Vec3Type::minusZ );

    // `float`, `double`, and `long double` are all considered floating-point types.
    // Therefore, for these three types, `std::is_floating_point_v<T>` will be `true`, while `int` and `bool` will be `false`.
    if constexpr ( std::is_floating_point_v<T> )
    {
        cls.function( "normalized", &Vec3Type::normalized )
           .function( "perpendicular", &Vec3Type::perpendicular )
           // .function( "transformed", &Vec3Type::transformed, allow_raw_pointers() )
           .function( "unsignZeroValues", &Vec3Type::unsignZeroValues )
           .function( "isFinite", &Vec3Type::isFinite );

        function( ( "unitVector3" + suffix ).c_str(), select_overload<Vec3Type( T, T )>( &unitVector3<T> ) );
    }

    // `std::is_integral_v<T>` returns `true` for integral types (such as `int`, `long`, `short`, `char`, `bool`, etc.)
    if constexpr ( std::is_integral_v<T> )
    {
        // NOTE: For integer vectors:
        // 
        // `normalized()`, `furthestBasisVector()`, 
        // `perpendicular()`, `unsignZeroValues()` and `isFinite()` is not working
        // 
        cls
        .function( "normalized",
            optional_override( [] ( const Vec3Type& self ) -> Vector3f
            {
                return Vector3f( static_cast< float >( self.x ), static_cast< float >( self.y ), static_cast< float >( self.z ) ).normalized();
            } )
        )
        .function( "perpendicular",
            optional_override( [] ( const Vec3Type& self ) -> std::pair<Vector3f, Vector3f>
            {
                Vector3f floatVec(
                    static_cast< float >( self.x ),
                    static_cast< float >( self.y ),
                    static_cast< float >( self.z )
                );
                return floatVec.perpendicular();
            } )
        )
        // .function( "transformed",
        //     optional_override( [] ( Vec3Type& self, const AffineXf3f* xf ) -> Vector3f
        //     {
        //         Vector3f floatVec(
        //             static_cast< float >( self.x ),
        //             static_cast< float >( self.y ),
        //             static_cast< float >( self.z )
        //         );
        //         return floatVec.transformed( xf );
        //     } ),
        //     allow_raw_pointers()
        // )
        .function( "unsignZeroValues",
            optional_override( [] ( Vec3Type& self ) -> Vector3f
            {
                Vector3f floatVec(
                    static_cast< float >( self.x ),
                    static_cast< float >( self.y ),
                    static_cast< float >( self.z )
                );
                // 
                // NOTE: Convert back to integers will truncate any fractional parts
                // 
                // self.x = static_cast<int>( floatVec.x );
                // self.y = static_cast<int>( floatVec.y );
                // self.z = static_cast<int>( floatVec.z );
                // 
                floatVec.unsignZeroValues();
                return floatVec;
            } )
        )
        .function( "isFinite", optional_override( [] ( Vec3Type& self ) -> bool
            {
                Vector3f floatVec( static_cast< float >( self.x ), static_cast< float >( self.y ), static_cast< float >( self.z ) );
                return floatVec.isFinite();
            } )
        );

        function( ( "unitVector3" + suffix ).c_str(),
            optional_override( [] ( T x, T y ) -> Vector3f
            {
                float dx = static_cast<float>( x );
                float dy = static_cast<float>( y );
                return unitVector3( dx, dy );
            } )
        );
    }

    if constexpr ( !std::is_same_v<T, bool> )
    {
        cls.function( "furthestBasisVector", &Vec3Type::furthestBasisVector );
    
        function( ( "distanceSq" + suffix ).c_str(), select_overload<T( const Vec3Type&, const Vec3Type& )>( &distanceSq<T> ) );
        function( ( "distance" + suffix ).c_str(), select_overload<T( const Vec3Type&, const Vec3Type& )>( &distance<T> ) );
        function( ( "cross" + suffix ).c_str(), select_overload<Vec3Type( const Vec3Type&, const Vec3Type& )>( &cross<T> ) );
        function( ( "dot" + suffix ).c_str(), select_overload<T( const Vec3Type&, const Vec3Type& )>( &dot<T> ) );
        function( ( "sqr" + suffix ).c_str(), select_overload<T( const Vec3Type& )>( &sqr<T> ) );
        function( ( "mixed" + suffix ).c_str(), select_overload<T( const Vec3Type&, const Vec3Type&, const Vec3Type& )>( &mixed<T> ) );
        function( ( "mult" + suffix ).c_str(), select_overload<Vec3Type( const Vec3Type&, const Vec3Type& )>( &mult<T> ) );
        function( ( "div" + suffix ).c_str(), select_overload<Vec3Type( const Vec3Type&, const Vec3Type& )>( &div<T> ) );
        function( ( "angle" + suffix ).c_str(), select_overload<T( const Vec3Type&, const Vec3Type& )>( &angle<T> ) );
    }

    return cls;
}


template<typename Vec4Type>
auto bindTypedVector4( const std::string& name, const std::string& suffix )
{
    using T = Vec4Type::ValueType;

    auto cls = class_<Vec4Type>( name.c_str() )
        .template smart_ptr<std::shared_ptr<Vec4Type>>( ( name + "SharedPtr" ).c_str() )
        .constructor<>()
        .constructor<T, T, T, T>()

        .property( "x", &Vec4Type::x )
        .property( "y", &Vec4Type::y )
        .property( "z", &Vec4Type::z )
        .property( "w", &Vec4Type::w )

        .class_function( "diagonal", &Vec4Type::diagonal )

        .function( "get", select_overload<const T & ( int ) const>( &Vec4Type::operator[] ) )
        .function( "set", select_overload<T & ( int )>( &Vec4Type::operator[] ) )

        .function( "lengthSq", &Vec4Type::lengthSq )
        .function( "length", &Vec4Type::length );


    if constexpr ( std::is_floating_point_v<T> )
    {
        cls.function( "isFinite", &Vec4Type::isFinite );
    }

    if constexpr ( !std::is_integral_v<T> )
    {
        cls.function( "proj3d", &Vec4Type::proj3d )
           .function( "normalized", &Vec4Type::normalized );
    }

    if constexpr ( !std::is_same_v<T, bool> )
    {
        function( ( "dot" + suffix ).c_str(), select_overload<T ( const Vec4Type&, const Vec4Type& )>( &dot<T> ) );
        function( ( "mult" + suffix ).c_str(), select_overload<Vec4Type( const Vec4Type&, const Vec4Type& )>( &mult<T> ) );
        function( ( "div" + suffix ).c_str(), select_overload<Vec4Type( const Vec4Type&, const Vec4Type& )>( &div<T> ) );
    }

    function( ( "distanceSq" + suffix ).c_str(), select_overload<T( const Vec4Type&, const Vec4Type& )>( &distanceSq<T> ) );
    function( ( "distance" + suffix ).c_str(), select_overload<T( const Vec4Type&, const Vec4Type& )>( &distance<T> ) );
    function( ( "sqr" + suffix ).c_str(), select_overload<T( const Vec4Type& )>( &sqr<T> ) );

    return cls;
}
