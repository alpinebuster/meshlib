#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRId.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRColor.h>
#include <MRMesh/MRDipole.h>
#include <MRMesh/MRAABBTreePoints.h>
#include <MRMesh/MRBuffer.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRGridSampling.h>
#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshPart.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRPointCloud.h>
#include <MRMesh/MRProgressCallback.h>
#include <MRMesh/MRMeshBuilderTypes.h>
#include <MRMesh/MRMeshFwd.h>

#include "MRMeshFwd.h"

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( MeshFwdModule )
{
    // 1) Expose `NoInit` as an empty value type
    value_object<MR::NoInit>( "NoInit" );
    // 2) Expose the global constant `noInit` to JS
    constant( "noInit", MR::noInit );
    
    // TODO: V2

    // Bind `UndirectedEdgeId` first (needed for `EdgeId` constructor)
    class_<UndirectedEdgeId>( "UndirectedEdgeId" )
        .constructor<>()
        .constructor<int>()
        .smart_ptr<std::shared_ptr<UndirectedEdgeId>>( "UndirectedEdgeIdSharedPtr" ) 

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
        .smart_ptr<std::shared_ptr<EdgeId>>( "EdgeIdSharedPtr" ) 
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
        .smart_ptr<std::shared_ptr<FaceId>>( "FaceIdSharedPtr" ) 

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
        .smart_ptr<std::shared_ptr<VertId>>( "VertIdSharedPtr" ) 

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
        .smart_ptr<std::shared_ptr<PixelId>>( "PixelIdSharedPtr" ) 

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
        .smart_ptr<std::shared_ptr<VoxelId>>( "VoxelIdSharedPtr" ) 

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
        .smart_ptr<std::shared_ptr<RegionId>>( "RegionIdSharedPtr" ) 

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
        .smart_ptr<std::shared_ptr<NodeId>>( "NodeIdSharedPtr" ) 

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
        .smart_ptr<std::shared_ptr<ObjId>>( "ObjIdSharedPtr" ) 

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
        .smart_ptr<std::shared_ptr<TextureId>>( "TextureIdSharedPtr" ) 

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
        .smart_ptr<std::shared_ptr<GraphVertId>>( "GraphVertIdSharedPtr" ) 

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
        .smart_ptr<std::shared_ptr<GraphEdgeId>>( "GraphEdgeIdSharedPtr" ) 

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

EMSCRIPTEN_BINDINGS( BMapTypedModule )
{
    ///
    bindTypedBMap<FaceBMap, FaceId, FaceId>( "FaceBMap" );
    bindTypedBMap<VertBMap, VertId, VertId>( "VertBMap" );
    bindTypedBMap<EdgeBMap, EdgeId, EdgeId>( "EdgeBMap" );
    bindTypedBMap<UndirectedEdgeBMap, UndirectedEdgeId, UndirectedEdgeId>( "UndirectedEdgeBMap" );
    bindTypedBMap<WholeEdgeBMap, EdgeId, UndirectedEdgeId>( "WholeEdgeBMap" );
    ///


    bindTypedBMap<BMap<VertId, size_t>, VertId, size_t>( "VertIdSizeTBMap" );
    bindTypedBMap<BMap<UndirectedEdgeId, size_t>, UndirectedEdgeId, size_t>( "UndirectedEdgeIdSizeTBMap" );
    bindTypedBMap<BMap<FaceId, size_t>, FaceId, size_t>( "FaceIdSizeTBMap" );
}

EMSCRIPTEN_BINDINGS( MapTypedModule )
{
    BIND_TYPED_VECTOR( Triangulation, ThreeVertIds, FaceId );

    bindTypedVector<Dipoles, Dipole, NodeId>( "Dipoles" );

    BIND_TYPED_VECTOR( FaceMap, FaceId, FaceId );
    BIND_TYPED_VECTOR( VertMap, VertId, VertId );

    ///
    // NOTE: `EdgeMap` -> `Vector<EdgeId, EdgeId>`
    BIND_TYPED_VECTOR( EdgeMap, EdgeId, EdgeId );
    bindTypedVector<Vector<VertId, EdgeId>, VertId, EdgeId>( "VertIdEdgeIdMap" );
    bindTypedVector<Vector<EdgeId, VertId>, EdgeId, VertId>( "EdgeIdVertIdMap" );
    bindTypedVector<Vector<EdgeId, FaceId>, EdgeId, FaceId>( "EdgeIdFaceIdMap" );
    bindTypedVector<Vector<FaceId, EdgeId>, FaceId, EdgeId>( "FaceIdEdgeIdMap" );

    bindTypedVector<Vector<ModelPointsData, ObjId>, ModelPointsData, ObjId>( "ModelPointsDataObjIdMap" );
    bindTypedVector<Vector<MeshBuilder::VertSpan, FaceId>, MeshBuilder::VertSpan, FaceId>( "VertSpanFaceIdMap" );
    ///

    BIND_TYPED_VECTOR( UndirectedEdgeMap, UndirectedEdgeId, UndirectedEdgeId );
    BIND_TYPED_VECTOR( ObjMap, ObjId, ObjId );

    BIND_TYPED_VECTOR( WholeEdgeMap, EdgeId, UndirectedEdgeId );
    BIND_TYPED_VECTOR( UndirectedEdge2RegionMap, RegionId, UndirectedEdgeId );
    BIND_TYPED_VECTOR( Face2RegionMap, RegionId, FaceId );
    BIND_TYPED_VECTOR( Vert2RegionMap, RegionId, VertId );
}

EMSCRIPTEN_BINDINGS( CoordsTypedModule )
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

EMSCRIPTEN_BINDINGS( ColorsTypedModule )
{
    BIND_TYPED_VECTOR( TexturePerFace, TextureId, FaceId );
    BIND_TYPED_VECTOR( VertColors, Color, VertId );
    BIND_TYPED_VECTOR( FaceColors, Color, FaceId );
    BIND_TYPED_VECTOR( EdgeColors, Color, EdgeId );
    BIND_TYPED_VECTOR( UndirectedEdgeColors, Color, UndirectedEdgeId );
}

EMSCRIPTEN_BINDINGS( ScalarsTypedModule )
{
    BIND_TYPED_VECTOR( VertScalars, float, VertId );
    BIND_TYPED_VECTOR( FaceScalars, float, FaceId );
    BIND_TYPED_VECTOR( EdgeScalars, float, EdgeId );
    BIND_TYPED_VECTOR( UndirectedEdgeScalars, float, UndirectedEdgeId );
}

EMSCRIPTEN_BINDINGS( NodeVecTypedModule )
{
    bindTypedVector<AABBTreePoints::NodeVec, AABBTreePoints::Node, NodeId>( "NodeVec" );
}


EMSCRIPTEN_BINDINGS( MeshFwdTypeModule )
{
    enum_<FilterType>( "FilterType" )
        .value( "Linear", FilterType::Linear )
        .value( "Discrete", FilterType::Discrete );

    enum_<WrapType>( "WrapType" )
        .value( "Repeat", WrapType::Repeat )
        .value( "Mirror", WrapType::Mirror )
        .value( "Clamp", WrapType::Clamp );

    enum_<Reorder>( "Reorder" )
        .value( "None", Reorder::None )
        .value( "Lexicographically", Reorder::Lexicographically )
        .value( "AABBTree", Reorder::AABBTree );
}
