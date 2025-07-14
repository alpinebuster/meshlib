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
    
    ///
    bindTypedId<EdgeId>( "EdgeId" );  // Using specialized versions
    bindTypedId<VoxelId, size_t>( "VoxelId" );  // Using specialized versions

    bindTypedId<UndirectedEdgeId>( "UndirectedEdgeId" );
    bindTypedId<FaceId>( "FaceId" );
    bindTypedId<VertId>( "VertId" );
    bindTypedId<PixelId>( "PixelId" );
    bindTypedId<RegionId>( "RegionId" );
    bindTypedId<NodeId>( "NodeId" );
    bindTypedId<ObjId>( "ObjId" );
    bindTypedId<TextureId>( "TextureId" );
    bindTypedId<GraphVertId>( "GraphVertId" );
    bindTypedId<GraphEdgeId>( "GraphEdgeId" );
    ///
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
