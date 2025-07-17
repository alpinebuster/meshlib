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
    auto cls = class_<VoxelId>( className.c_str() )
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
