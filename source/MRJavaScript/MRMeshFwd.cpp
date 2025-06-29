#include <emscripten/bind.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>

using namespace emscripten;
using namespace MR;

// TODO: V2

EMSCRIPTEN_BINDINGS( MRIdModule )
{
    // 1) Expose `NoInit` as an empty value type
    value_object<MR::NoInit>( "NoInit" );
    // 2) Expose the global constant `noInit` to JS
    constant( "noInit", MR::noInit );

    // Bind `UndirectedEdgeId` first (needed for `EdgeId` constructor)
    class_<Id<UndirectedEdgeTag>>( "UndirectedEdgeId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<Id<UndirectedEdgeTag>>>( "shared_ptr<Id<UndirectedEdgeTag>>" ) 

        .function( "valid", &Id<UndirectedEdgeTag>::valid )
        .function( "toInt", select_overload<int() const>( static_cast<int( Id<UndirectedEdgeTag>::* )() const >( &Id<UndirectedEdgeTag>::operator int ) ) )
        .function( "toBool", optional_override( []( const Id<UndirectedEdgeTag>& self ) { return bool( self ); }))
        .function( "get", &Id<UndirectedEdgeTag>::get )
        .function( "equals", optional_override([](const Id<UndirectedEdgeTag>& self, const Id<UndirectedEdgeTag>& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const Id<UndirectedEdgeTag>& self, const Id<UndirectedEdgeTag>& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const Id<UndirectedEdgeTag>& self, const Id<UndirectedEdgeTag>& other){ return self < other; }) )
        .function( "increment", select_overload<Id<UndirectedEdgeTag>&()>( &Id<UndirectedEdgeTag>::operator-- ) )
        .function( "decrement", select_overload<Id<UndirectedEdgeTag>&()>( &Id<UndirectedEdgeTag>::operator++ ) )
        .function( "incrementByInt", select_overload<Id<UndirectedEdgeTag>( int )>( &Id<UndirectedEdgeTag>::operator-- ) )
        .function( "decrementByInt", select_overload<Id<UndirectedEdgeTag>( int )>( &Id<UndirectedEdgeTag>::operator++ ) );

    class_<Id<EdgeTag>>( "EdgeId" )
        // Constructors
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<Id<EdgeTag>>>( "shared_ptr<Id<EdgeTag>>" ) 
        .class_function( "fromUndirected", optional_override( []( const UndirectedEdgeId& u ) {return Id<EdgeTag>( u );}))

        // Validity check
        .function( "valid", &Id<EdgeTag>::valid )
        // Conversion
        .function( "toInt", optional_override([](const Id<EdgeTag>& self){ return int(self); }))
        .function( "toBool", optional_override([](const Id<EdgeTag>& self){ return bool(self); }))
        // Access underlying value
        .function( "get", optional_override([](Id<EdgeTag>& self){ return self.get(); }))
        // Symmetry operations
        .function( "sym", &Id<EdgeTag>::sym )
        .function( "even", &Id<EdgeTag>::even )
        .function( "odd", &Id<EdgeTag>::odd )
        // Undirected conversion
        .function( "undirected", &Id<EdgeTag>::undirected )
        .function( "toUndirected", optional_override([](const Id<EdgeTag>& self) { return self.undirected(); }) )
        // Comparison
        .function( "equals", optional_override( [](const Id<EdgeTag>& self, const Id<EdgeTag>& other) { return self == other; } ) )
        .function( "notEquals", optional_override([](const Id<EdgeTag>& self, const Id<EdgeTag>& other){ return self != other; }) )
        .function( "lessThan", optional_override( [](const Id<EdgeTag>& self, const Id<EdgeTag>& other){ return self < other; } ) )
        // Increment / Decrement
        .function( "increment", select_overload<Id<EdgeTag>&()>( &Id<EdgeTag>::operator-- ) )
        .function( "decrement", select_overload<Id<EdgeTag>&()>( &Id<EdgeTag>::operator++ ) )
        .function( "incrementByInt", select_overload<Id<EdgeTag>( int )>( &Id<EdgeTag>::operator-- ) )
        .function( "decrementByInt", select_overload<Id<EdgeTag>( int )>( &Id<EdgeTag>::operator++ ) );
    
    class_<Id<FaceTag>>( "FaceId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<Id<FaceTag>>>( "shared_ptr<Id<FaceTag>>" ) 

        .function( "valid", &Id<FaceTag>::valid )
        .function( "toInt", select_overload<int () const>( static_cast<int( Id<FaceTag>::* ) () const>( &Id<FaceTag>::operator int )))
        .function( "toBool", optional_override( []( const Id<FaceTag>& self ) { return bool( self ); }))
        .function( "get", &Id<FaceTag>::get )
        .function( "equals", optional_override([](const Id<FaceTag>& self, const Id<FaceTag>& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const Id<FaceTag>& self, const Id<FaceTag>& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const Id<FaceTag>& self, const Id<FaceTag>& other){ return self < other; }) )
        .function( "increment", select_overload<Id<FaceTag>&()>( &Id<FaceTag>::operator-- ) )
        .function( "decrement", select_overload<Id<FaceTag>&()>( &Id<FaceTag>::operator++ ) )
        .function( "incrementByInt", select_overload<Id<FaceTag>( int )>( &Id<FaceTag>::operator-- ) )
        .function( "decrementByInt", select_overload<Id<FaceTag>( int )>( &Id<FaceTag>::operator++ ) );

    class_<Id<VertTag>>( "VertId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<Id<VertTag>>>( "shared_ptr<Id<VertTag>>" ) 

        .function( "valid", &Id<VertTag>::valid )
        .function( "toInt", select_overload<int() const>( static_cast<int ( Id<VertTag>::* ) () const>( &Id<VertTag>::operator int ) ) )
        .function( "toBool", optional_override( [] ( const Id<VertTag>& self ) { return bool( self ); }))
        .function( "get", &Id<VertTag>::get )
        .function( "equals", optional_override([](const Id<VertTag>& self, const Id<VertTag>& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const Id<VertTag>& self, const Id<VertTag>& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const Id<VertTag>& self, const Id<VertTag>& other){ return self < other; }) )
        .function( "increment", select_overload<Id<VertTag>&()>( &Id<VertTag>::operator-- ) )
        .function( "decrement", select_overload<Id<VertTag>&()>( &Id<VertTag>::operator++ ) )
        .function( "incrementByInt", select_overload<Id<VertTag>( int )>( &Id<VertTag>::operator-- ) )
        .function( "decrementByInt", select_overload<Id<VertTag>( int )>( &Id<VertTag>::operator++ ) );

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
