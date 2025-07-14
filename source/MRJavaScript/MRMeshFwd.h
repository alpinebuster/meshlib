#pragma once

#include <type_traits>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRColor.h>
#include <MRMesh/MRDipole.h>
#include <MRMesh/MRBuffer.h>

using namespace emscripten;
using namespace MR;


// This helper macro is used to declare typedefs. For example:
// 
// NOTE: VertCoords -> Vector<Vector3f, VertId>
// 
// The code below,
//     BIND_TYPED_VECTOR( VertCoords, Vector3f, VertId );
// 
// will generate the following code:
//     class_<VertCoords>( "VertCoords" )
//         .constructor<>()
//         .constructor<size_t>()
//         .constructor<size_t, const Vector3f&>()
//         .function( "size", &VertCoords::size )
//         .function( "get", select_overload<const Vector3f&(VertId) const>(&VertCoords::operator[]) )
//
#define BIND_TYPED_VECTOR(NAME, ELEM_TYPE, ID_TYPE) \
    class_<NAME>(#NAME) \
        .constructor<>() \
        .constructor<size_t>() \
        .constructor<size_t, const ELEM_TYPE&>() \
        .function("size", &NAME::size) \
        .function("empty", &NAME::empty) \
        .function("clear", &NAME::clear) \
        .function("capacity", &NAME::capacity) \
        .function("reserve", &NAME::reserve) \
        .function("resize", select_overload<void(size_t)>(&NAME::resize)) \
        .function("resizeWithValue", select_overload<void(size_t, const ELEM_TYPE&)>(&NAME::resize)) \
        .function("resizeWithReserve", select_overload<void(size_t)>(&NAME::resizeWithReserve)) \
        .function("resizeWithReserveAndValue", select_overload<void(size_t, const ELEM_TYPE&)>(&NAME::resizeWithReserve)) \
        .function("get", select_overload<const ELEM_TYPE&(ID_TYPE) const>(&NAME::operator[])) \
        .function("set", optional_override([](NAME& self, ID_TYPE i, ELEM_TYPE value) { self[i] = value; })) \
        .function("getByIndex", select_overload<const ELEM_TYPE&(ID_TYPE) const>(&NAME::operator[])) \
        .function("getByIndexMutable", select_overload<ELEM_TYPE&(ID_TYPE)>(&NAME::operator[]), allow_raw_pointers()) \
        .function("getAt", optional_override([](const NAME& self, ID_TYPE i) -> ELEM_TYPE { \
            if (i >= self.size()) throw std::out_of_range(std::string(#NAME) + " index out of range: " + std::to_string(int(i)) + " >= " + std::to_string(self.size())); \
            return self[i]; \
        })) \
        .function("setAt", optional_override([](NAME& self, ID_TYPE i, ELEM_TYPE value) -> bool { \
            if (i >= self.size()) throw std::out_of_range(std::string(#NAME) + " index out of range: " + std::to_string(int(i)) + " >= " + std::to_string(self.size())); \
            self[i] = value; return true; \
        })) \
        .function("front", select_overload<const ELEM_TYPE&() const>(&NAME::front)) \
        .function("frontMutable", select_overload<ELEM_TYPE&()>(&NAME::front), allow_raw_pointers()) \
        .function("back", select_overload<const ELEM_TYPE&() const>(&NAME::back)) \
        .function("backMutable", select_overload<ELEM_TYPE&()>(&NAME::back), allow_raw_pointers()) \
        .function("pushBack", select_overload<void(const ELEM_TYPE&)>(&NAME::push_back)) \
        .function("popBack", &NAME::pop_back) \
        .function("emplaceBack", &NAME::emplace_back<ELEM_TYPE>) \
        .function("beginId", &NAME::beginId) \
        .function("backId", &NAME::backId) \
        .function("endId", &NAME::endId) \
        .function("autoResizeAt", select_overload<ELEM_TYPE&(ID_TYPE)>(&NAME::autoResizeAt)) \
        .function("autoResizeSet", select_overload<void(ID_TYPE, ELEM_TYPE)>(&NAME::autoResizeSet)) \
        .function("autoResizeSetRange", select_overload<void(ID_TYPE, size_t, ELEM_TYPE)>(&NAME::autoResizeSet)) \
        .function("swap", &NAME::swap) \
        .function("heapBytes", &NAME::heapBytes) \
        .function("equals", optional_override([](const NAME& a, const NAME& b) { return a == b; })) \
        .function("notEquals", optional_override([](const NAME& a, const NAME& b) { return a != b; }));


// NOTE:
// 
// 1) `.constructor` is `template<class... Args> class_& constructor();`
// It is a template member function itself, so it must be used as `.template constructor<>()`
// 
// 2) `.function` is `class_& function(const char*, F)`
// It is a regular member function (not a template!)
// 
template<typename EM_NAME, typename ELEM, typename ID>
auto bindTypedVector( const char* jsName )
{
    auto cls = class_<EM_NAME>( jsName )
        .template constructor<>()
        .template constructor<size_t>()
        .template constructor<size_t, const ELEM&>()
        .function( "size", &EM_NAME::size )
        .function( "empty", &EM_NAME::empty )
        .function( "clear", &EM_NAME::clear )
        .function( "capacity", &EM_NAME::capacity )
        .function( "reserve", &EM_NAME::reserve )
        .function( "resize", select_overload<void( size_t )>( &EM_NAME::resize ) )
        .function( "resizeWithValue", select_overload<void( size_t, const ELEM& )>( &EM_NAME::resize ) )
        .function( "resizeWithReserve", select_overload<void( size_t )>( &EM_NAME::resizeWithReserve ) )
        .function( "resizeWithReserveAndValue", select_overload<void( size_t, const ELEM& )>( &EM_NAME::resizeWithReserve ) )
        .function( "get", select_overload<const ELEM & ( ID ) const>( &EM_NAME::operator[] ) )
        .function( "set", optional_override( [] ( EM_NAME& self, ID i, ELEM value )
        {
            self[i] = value;
        } ) )
        .function( "getByIndex", select_overload<const ELEM & ( ID ) const>( &EM_NAME::operator[] ) )
        .function( "getByIndexMutable", select_overload<ELEM & ( ID )>( &EM_NAME::operator[] ), allow_raw_pointers() )
        .function( "getAt", optional_override( [] ( const EM_NAME& self, ID i ) -> ELEM
        {
            if ( i >= self.size() ) throw std::out_of_range(
                "Index out of range: " +
                std::to_string( int( i ) ) + " >= " + std::to_string( self.size() )
            );
            return self[i];
        } ) )
        .function( "setAt", optional_override( [] ( EM_NAME& self, ID i, ELEM value ) -> bool
        {
            if ( i >= self.size() ) throw std::out_of_range(
                "Index out of range: " +
                std::to_string( int( i ) ) + " >= " + std::to_string( self.size() )
            );
            self[i] = value;
            return true;
        } ) )
        .function( "front", select_overload<const ELEM & ( ) const>( &EM_NAME::front ) )
        .function( "frontMutable", select_overload<ELEM & ( )>( &EM_NAME::front ), allow_raw_pointers() )
        .function( "back", select_overload<const ELEM & ( ) const>( &EM_NAME::back ) )
        .function( "backMutable", select_overload<ELEM & ( )>( &EM_NAME::back ), allow_raw_pointers() )
        .function( "pushBack", select_overload<void( const ELEM& )>( &EM_NAME::push_back ) )
        .function( "popBack", &EM_NAME::pop_back )
        .function( "emplaceBack", &EM_NAME::template emplace_back<ELEM> )
        .function( "beginId", &EM_NAME::beginId )
        .function( "backId", &EM_NAME::backId )
        .function( "endId", &EM_NAME::endId )
        .function( "autoResizeAt", select_overload<ELEM & ( ID )>( &EM_NAME::autoResizeAt ) )
        .function( "autoResizeSet", select_overload<void( ID, ELEM )>( &EM_NAME::autoResizeSet ) )
        .function( "autoResizeSetRange", select_overload<void( ID, size_t, ELEM )>( &EM_NAME::autoResizeSet ) )
        .function( "swap", &EM_NAME::swap )
        .function( "heapBytes", &EM_NAME::heapBytes );

    // If the element type supports `==/!=`, then register `equals`/`notEquals`
    if constexpr ( std::equality_comparable<ELEM> )
    {
        cls.function( "equals", optional_override( [] ( const EM_NAME& a, const EM_NAME& b )
        {
            return a == b;
        } ) );
        cls.function( "notEquals", optional_override( [] ( const EM_NAME& a, const EM_NAME& b )
        {
            return a != b;
        } ) );
    }

    return cls;
}

template<typename MapType, typename ElementType, typename IdType>
auto bindTypedBMap(const char* jsName)
{
    auto cls = class_<MapType>( jsName )
        .constructor<>()
        // Using pointer cause `Buffer` does NOT support the **copy** assignment operator
        .function( "getB", optional_override( [] ( MapType& self ) -> Buffer<ElementType, IdType>*
            {
                return &self.b;
            } ), allow_raw_pointers() )
        // NOTE:
        // 
        // 1) If `setB` accepts optional arguments or allows "clearing", use **pointer**
        // 2) If `setB` always requires a valid `Buffer` object, change it with a **reference**
        // 
        .function( "setB", optional_override( []( MapType& self, Buffer<ElementType, IdType>& newB ) {
            self.b = std::move( newB );
        } ), allow_raw_pointers() )
        .function( "setBWithPtr", optional_override( []( MapType& self, Buffer<ElementType, IdType>* newB ) {
            // Move assignment, because `Buffer` does not support the copy assignment operator
            if ( newB ) self.b = std::move( *newB );
        } ), allow_raw_pointers() )
        .property( "tsize", &MapType::tsize );

    return cls;
}


///
template<typename IdType, typename ValueType = int>
auto bindTypedId( const std::string& className )
{
    auto cls = class_<IdType>( className.c_str() )
        // Ctor
        .template constructor<>()
        .template constructor<ValueType>()
        .template smart_ptr<std::shared_ptr<IdType>>( ( className + "SharedPtr" ).c_str() )

        .function( "opint", select_overload<ValueType() const>( &IdType::operator ValueType ) )
        .function( "valid", &IdType::valid )
        .function( "opbool", select_overload<bool() const>( &IdType::operator bool ) )
        .function( "get", select_overload<ValueType & ( )>( &IdType::get ) )

        .function( "equals", optional_override( [] ( const IdType& self, const IdType& other )
        {
            return self == other;
        } ) )
        .function( "notEquals", optional_override( [] ( const IdType& self, const IdType& other )
        {
            return self != other;
        } ) )
        .function( "lessThan", optional_override( [] ( const IdType& self, const IdType& other )
        {
            return self < other;
        } ) )
    
        .function( "increment", select_overload<IdType & ( )>( &IdType::operator++ ) )
        .function( "decrement", select_overload<IdType & ( )>( &IdType::operator-- ) )
        .function( "incrementByInt", select_overload<IdType( int )>( &IdType::operator++ ) )
        .function( "decrementByInt", select_overload<IdType( int )>( &IdType::operator-- ) )

        .function( "addAssign", select_overload<IdType & ( ValueType )>( &IdType::operator+= ) )
        .function( "subAssign", select_overload<IdType & ( ValueType )>( &IdType::operator-= ) );
    
    return cls;
}

// `EdgeId` specialized version - includes special `sym()`, `even()`, `odd()`, `undirected()` methods.
template<>
auto bindTypedId<EdgeId, int>( const std::string& className )
{
    auto cls = class_<EdgeId>( className.c_str() )
        .template constructor<>()
        .template constructor<int>()
        .template smart_ptr<std::shared_ptr<EdgeId>>( ( className + "SharedPtr" ).c_str() )
        .class_function( "fromUndirected", optional_override( [] ( const UndirectedEdgeId& u )
        {
            return EdgeId( u );
        } ) )

        .function( "opint", select_overload<int() const>( &EdgeId::operator int ) )
        .function( "valid", &EdgeId::valid )
        .function( "opbool", select_overload<bool() const>( &EdgeId::operator bool ) )
        .function( "get", select_overload<int& ( )>( &EdgeId::get ) )

        .function( "sym", &EdgeId::sym )
        .function( "even", &EdgeId::even )
        .function( "odd", &EdgeId::odd )
        .function( "undirected", &EdgeId::undirected )
        .function( "toUndirected", optional_override( [] ( const EdgeId& self )
        {
            return self.undirected();
        } ) )

        .function( "equals", optional_override( [] ( const EdgeId& self, const EdgeId& other )
        {
            return self == other;
        } ) )
        .function( "notEquals", optional_override( [] ( const EdgeId& self, const EdgeId& other )
        {
            return self != other;
        } ) )
        .function( "lessThan", optional_override( [] ( const EdgeId& self, const EdgeId& other )
        {
            return self < other;
        } ) )
        
        .function( "increment", select_overload<EdgeId & ( )>( &EdgeId::operator++ ) )
        .function( "decrement", select_overload<EdgeId & ( )>( &EdgeId::operator-- ) )
        .function( "incrementByInt", select_overload<EdgeId( int )>( &EdgeId::operator++ ) )
        .function( "decrementByInt", select_overload<EdgeId( int )>( &EdgeId::operator-- ) )

        .function( "addAssign", select_overload<EdgeId & ( int )>( &EdgeId::operator+= ) )
        .function( "subAssign", select_overload<EdgeId & ( int )>( &EdgeId::operator-= ) );

    return cls;
}

// `VoxelId` specialized version - use `size_t` as `ValueType`
template<>
auto bindTypedId<VoxelId, size_t>( const std::string& className ) {
    auto cls = class_<VoxelId>(className.c_str())
        .template constructor<>()
        .template constructor<size_t>()
        .template smart_ptr<std::shared_ptr<VoxelId>>( ( className + "SharedPtr" ).c_str() )

        .function( "opint", select_overload<size_t() const>( &VoxelId::operator size_t ) )
        .function( "valid", &VoxelId::valid )
        .function( "opbool", select_overload<bool() const>( &VoxelId::operator bool ) )
        .function( "get", select_overload<size_t& ( )>( &VoxelId::get ) )

        .function( "equals", optional_override( [] ( const VoxelId& self, const VoxelId& other )
        {
            return self == other;
        } ) )
        .function( "notEquals", optional_override( [] ( const VoxelId& self, const VoxelId& other )
        {
            return self != other;
        } ) )
        .function( "lessThan", optional_override( [] ( const VoxelId& self, const VoxelId& other )
        {
            return self < other;
        } ) )
        
        .function( "increment", select_overload<VoxelId & ( )>( &VoxelId::operator++ ) )
        .function( "decrement", select_overload<VoxelId & ( )>( &VoxelId::operator-- ) )
        .function( "incrementByInt", select_overload<VoxelId( int )>( &VoxelId::operator++ ) )
        .function( "decrementByInt", select_overload<VoxelId( int )>( &VoxelId::operator-- ) )

        .function( "addAssign", select_overload<VoxelId & ( size_t )>( &VoxelId::operator+= ) )
        .function( "subAssign", select_overload<VoxelId & ( size_t )>( &VoxelId::operator-= ) );

    return cls;
}
///
