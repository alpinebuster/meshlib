#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>

#include "MRMeshFwd.h"

using namespace emscripten;
using namespace MR;

// TODO: V2

EMSCRIPTEN_BINDINGS( IdModule )
{
    // 1) Expose `NoInit` as an empty value type
    value_object<MR::NoInit>( "NoInit" );
    // 2) Expose the global constant `noInit` to JS
    constant( "noInit", MR::noInit );

    // Bind `UndirectedEdgeId` first (needed for `EdgeId` constructor)
    class_<UndirectedEdgeId>( "UndirectedEdgeId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<UndirectedEdgeId>>( "shared_ptr<UndirectedEdgeId>" ) 

        .function( "valid", &UndirectedEdgeId::valid )
        .function( "toInt", select_overload<int() const>( static_cast<int( UndirectedEdgeId::* )() const >( &UndirectedEdgeId::operator int ) ) )
        .function( "toBool", optional_override( []( const UndirectedEdgeId& self ) { return bool( self ); }))
        .function( "get", &UndirectedEdgeId::get )
        .function( "equals", optional_override([](const UndirectedEdgeId& self, const UndirectedEdgeId& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const UndirectedEdgeId& self, const UndirectedEdgeId& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const UndirectedEdgeId& self, const UndirectedEdgeId& other){ return self < other; }) )
        .function( "increment", select_overload<UndirectedEdgeId&()>( &UndirectedEdgeId::operator-- ) )
        .function( "decrement", select_overload<UndirectedEdgeId&()>( &UndirectedEdgeId::operator++ ) )
        .function( "incrementByInt", select_overload<UndirectedEdgeId( int )>( &UndirectedEdgeId::operator-- ) )
        .function( "decrementByInt", select_overload<UndirectedEdgeId( int )>( &UndirectedEdgeId::operator++ ) );

    class_<EdgeId>( "EdgeId" )
        // Constructors
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<EdgeId>>( "shared_ptr<EdgeId>" ) 
        .class_function( "fromUndirected", optional_override( []( const UndirectedEdgeId& u ) {return EdgeId( u );}))

        // Validity check
        .function( "valid", &EdgeId::valid )
        // Conversion
        .function( "toInt", optional_override([](const EdgeId& self){ return int(self); }))
        .function( "toBool", optional_override([](const EdgeId& self){ return bool(self); }))
        // Access underlying value
        .function( "get", optional_override([](EdgeId& self){ return self.get(); }))
        // Symmetry operations
        .function( "sym", &EdgeId::sym )
        .function( "even", &EdgeId::even )
        .function( "odd", &EdgeId::odd )
        // Undirected conversion
        .function( "undirected", &EdgeId::undirected )
        .function( "toUndirected", optional_override([](const EdgeId& self) { return self.undirected(); }) )
        // Comparison
        .function( "equals", optional_override( [](const EdgeId& self, const EdgeId& other) { return self == other; } ) )
        .function( "notEquals", optional_override([](const EdgeId& self, const EdgeId& other){ return self != other; }) )
        .function( "lessThan", optional_override( [](const EdgeId& self, const EdgeId& other){ return self < other; } ) )
        // Increment / Decrement
        .function( "increment", select_overload<EdgeId&()>( &EdgeId::operator-- ) )
        .function( "decrement", select_overload<EdgeId&()>( &EdgeId::operator++ ) )
        .function( "incrementByInt", select_overload<EdgeId( int )>( &EdgeId::operator-- ) )
        .function( "decrementByInt", select_overload<EdgeId( int )>( &EdgeId::operator++ ) );
    
    class_<FaceId>( "FaceId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<FaceId>>( "shared_ptr<FaceId>" ) 

        .function( "valid", &FaceId::valid )
        .function( "toInt", select_overload<int () const>( static_cast<int( FaceId::* ) () const>( &FaceId::operator int )))
        .function( "toBool", optional_override( []( const FaceId& self ) { return bool( self ); }))
        .function( "get", &FaceId::get )
        .function( "equals", optional_override([](const FaceId& self, const FaceId& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const FaceId& self, const FaceId& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const FaceId& self, const FaceId& other){ return self < other; }) )
        .function( "increment", select_overload<FaceId&()>( &FaceId::operator-- ) )
        .function( "decrement", select_overload<FaceId&()>( &FaceId::operator++ ) )
        .function( "incrementByInt", select_overload<FaceId( int )>( &FaceId::operator-- ) )
        .function( "decrementByInt", select_overload<FaceId( int )>( &FaceId::operator++ ) );

    class_<VertId>( "VertId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<VertId>>( "shared_ptr<VertId>" ) 

        .function( "valid", &VertId::valid )
        .function( "toInt", select_overload<int() const>( static_cast<int ( VertId::* ) () const>( &VertId::operator int ) ) )
        .function( "toBool", optional_override( [] ( const VertId& self ) { return bool( self ); }))
        .function( "get", &VertId::get )
        .function( "equals", optional_override([](const VertId& self, const VertId& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const VertId& self, const VertId& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const VertId& self, const VertId& other){ return self < other; }) )
        .function( "increment", select_overload<VertId&()>( &VertId::operator-- ) )
        .function( "decrement", select_overload<VertId&()>( &VertId::operator++ ) )
        .function( "incrementByInt", select_overload<VertId( int )>( &VertId::operator-- ) )
        .function( "decrementByInt", select_overload<VertId( int )>( &VertId::operator++ ) );

    class_<PixelId>( "PixelId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<PixelId>>( "shared_ptr<PixelId>" ) 

        .function( "valid", &PixelId::valid )
        .function( "toInt", select_overload<int() const>( static_cast< int ( PixelId::* ) ( ) const >( &PixelId::operator int ) ) )
        .function( "toBool", optional_override( [] ( const PixelId& self ) { return bool( self ); }))
        .function( "get", &PixelId::get )
        .function( "equals", optional_override([](const PixelId& self, const PixelId& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const PixelId& self, const PixelId& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const PixelId& self, const PixelId& other){ return self < other; }) )
        .function( "increment", select_overload<PixelId&()>( &PixelId::operator-- ) )
        .function( "decrement", select_overload<PixelId&()>( &PixelId::operator++ ) )
        .function( "incrementByInt", select_overload<PixelId( int )>( &PixelId::operator-- ) )
        .function( "decrementByInt", select_overload<PixelId( int )>( &PixelId::operator++ ) );

    class_<VoxelId>( "VoxelId" )
        .constructor<>()
        .constructor<size_t>()
        .smart_ptr<std::shared_ptr<VoxelId>>( "shared_ptr<VoxelId>" ) 

        .function( "valid", &VoxelId::valid )
        .function( "toInt", select_overload<size_t() const>( static_cast< size_t ( VoxelId::* ) ( ) const >( &VoxelId::operator size_t ) ) )
        .function( "toBool", optional_override( [] ( const VoxelId& self ) { return bool( self ); }))
        .function( "get", &VoxelId::get )
        .function( "equals", optional_override([](const VoxelId& self, const VoxelId& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const VoxelId& self, const VoxelId& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const VoxelId& self, const VoxelId& other){ return self < other; }) )
        .function( "increment", select_overload<VoxelId&()>( &VoxelId::operator-- ) )
        .function( "decrement", select_overload<VoxelId&()>( &VoxelId::operator++ ) )
        .function( "incrementByInt", select_overload<VoxelId( int )>( &VoxelId::operator-- ) )
        .function( "decrementByInt", select_overload<VoxelId( int )>( &VoxelId::operator++ ) );

    class_<RegionId>( "RegionId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<RegionId>>( "shared_ptr<RegionId>" ) 

        .function( "valid", &RegionId::valid )
        .function( "toInt", select_overload<int() const>( static_cast< int ( RegionId::* ) ( ) const >( &RegionId::operator int ) ) )
        .function( "toBool", optional_override( [] ( const RegionId& self ) { return bool( self ); }))
        .function( "get", &RegionId::get )
        .function( "equals", optional_override([](const RegionId& self, const RegionId& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const RegionId& self, const RegionId& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const RegionId& self, const RegionId& other){ return self < other; }) )
        .function( "increment", select_overload<RegionId&()>( &RegionId::operator-- ) )
        .function( "decrement", select_overload<RegionId&()>( &RegionId::operator++ ) )
        .function( "incrementByInt", select_overload<RegionId( int )>( &RegionId::operator-- ) )
        .function( "decrementByInt", select_overload<RegionId( int )>( &RegionId::operator++ ) );

    class_<NodeId>( "NodeId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<NodeId>>( "shared_ptr<NodeId>" ) 

        .function( "valid", &NodeId::valid )
        .function( "toInt", select_overload<int() const>( static_cast< int ( NodeId::* ) ( ) const >( &NodeId::operator int ) ) )
        .function( "toBool", optional_override( [] ( const NodeId& self ) { return bool( self ); }))
        .function( "get", &NodeId::get )
        .function( "equals", optional_override([](const NodeId& self, const NodeId& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const NodeId& self, const NodeId& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const NodeId& self, const NodeId& other){ return self < other; }) )
        .function( "increment", select_overload<NodeId&()>( &NodeId::operator-- ) )
        .function( "decrement", select_overload<NodeId&()>( &NodeId::operator++ ) )
        .function( "incrementByInt", select_overload<NodeId( int )>( &NodeId::operator-- ) )
        .function( "decrementByInt", select_overload<NodeId( int )>( &NodeId::operator++ ) );

    class_<ObjId>( "ObjId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<ObjId>>( "shared_ptr<ObjId>" ) 

        .function( "valid", &ObjId::valid )
        .function( "toInt", select_overload<int() const>( static_cast< int ( ObjId::* ) ( ) const >( &ObjId::operator int ) ) )
        .function( "toBool", optional_override( [] ( const ObjId& self ) { return bool( self ); }))
        .function( "get", &ObjId::get )
        .function( "equals", optional_override([](const ObjId& self, const ObjId& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const ObjId& self, const ObjId& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const ObjId& self, const ObjId& other){ return self < other; }) )
        .function( "increment", select_overload<ObjId&()>( &ObjId::operator-- ) )
        .function( "decrement", select_overload<ObjId&()>( &ObjId::operator++ ) )
        .function( "incrementByInt", select_overload<ObjId( int )>( &ObjId::operator-- ) )
        .function( "decrementByInt", select_overload<ObjId( int )>( &ObjId::operator++ ) );

    class_<TextureId>( "TextureId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<TextureId>>( "shared_ptr<TextureId>" ) 

        .function( "valid", &TextureId::valid )
        .function( "toInt", select_overload<int() const>( static_cast< int ( TextureId::* ) ( ) const >( &TextureId::operator int ) ) )
        .function( "toBool", optional_override( [] ( const TextureId& self ) { return bool( self ); }))
        .function( "get", &TextureId::get )
        .function( "equals", optional_override([](const TextureId& self, const TextureId& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const TextureId& self, const TextureId& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const TextureId& self, const TextureId& other){ return self < other; }) )
        .function( "increment", select_overload<TextureId&()>( &TextureId::operator-- ) )
        .function( "decrement", select_overload<TextureId&()>( &TextureId::operator++ ) )
        .function( "incrementByInt", select_overload<TextureId( int )>( &TextureId::operator-- ) )
        .function( "decrementByInt", select_overload<TextureId( int )>( &TextureId::operator++ ) );

    class_<GraphVertId>( "GraphVertId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<GraphVertId>>( "shared_ptr<GraphVertId>" ) 

        .function( "valid", &GraphVertId::valid )
        .function( "toInt", select_overload<int() const>( static_cast< int ( GraphVertId::* ) ( ) const >( &GraphVertId::operator int ) ) )
        .function( "toBool", optional_override( [] ( const GraphVertId& self ) { return bool( self ); }))
        .function( "get", &GraphVertId::get )
        .function( "equals", optional_override([](const GraphVertId& self, const GraphVertId& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const GraphVertId& self, const GraphVertId& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const GraphVertId& self, const GraphVertId& other){ return self < other; }) )
        .function( "increment", select_overload<GraphVertId&()>( &GraphVertId::operator-- ) )
        .function( "decrement", select_overload<GraphVertId&()>( &GraphVertId::operator++ ) )
        .function( "incrementByInt", select_overload<GraphVertId( int )>( &GraphVertId::operator-- ) )
        .function( "decrementByInt", select_overload<GraphVertId( int )>( &GraphVertId::operator++ ) );

    class_<GraphEdgeId>( "GraphEdgeId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<GraphEdgeId>>( "shared_ptr<GraphEdgeId>" ) 

        .function( "valid", &GraphEdgeId::valid )
        .function( "toInt", select_overload<int() const>( static_cast< int ( GraphEdgeId::* ) ( ) const >( &GraphEdgeId::operator int ) ) )
        .function( "toBool", optional_override( [] ( const GraphEdgeId& self ) { return bool( self ); }))
        .function( "get", &GraphEdgeId::get )
        .function( "equals", optional_override([](const GraphEdgeId& self, const GraphEdgeId& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const GraphEdgeId& self, const GraphEdgeId& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const GraphEdgeId& self, const GraphEdgeId& other){ return self < other; }) )
        .function( "increment", select_overload<GraphEdgeId&()>( &GraphEdgeId::operator-- ) )
        .function( "decrement", select_overload<GraphEdgeId&()>( &GraphEdgeId::operator++ ) )
        .function( "incrementByInt", select_overload<GraphEdgeId( int )>( &GraphEdgeId::operator-- ) )
        .function( "decrementByInt", select_overload<GraphEdgeId( int )>( &GraphEdgeId::operator++ ) );
}

EMSCRIPTEN_BINDINGS( ScalarsModule )
{
    BIND_TYPED_VECTOR(VertScalars, float, VertId);
    BIND_TYPED_VECTOR(FaceScalars, float, FaceId);
    BIND_TYPED_VECTOR(EdgeScalars, float, EdgeId);
    BIND_TYPED_VECTOR(UndirectedEdgeScalars, float, UndirectedEdgeId);
}

EMSCRIPTEN_BINDINGS( CoordsModule )
{
    // NOTE: `VertNormals` is the same as `VertCoords`
    // 
    // It will throw `BindingError: Cannot register type 'VertUVCoords' twice`
    // BIND_TYPED_VECTOR( VertNormals, Vector3f, VertId );
    // 
    BIND_TYPED_VECTOR( VertCoords, Vector3f, VertId );
    // NOTE: `VertUVCoords` is the same as `VertCoords2`
    // BIND_TYPED_VECTOR( VertUVCoords, UVCoord, VertId );
    BIND_TYPED_VECTOR( VertCoords2, Vector2f, VertId );
    BIND_TYPED_VECTOR( FaceNormals, Vector3f, FaceId );
}
