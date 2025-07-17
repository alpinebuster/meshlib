#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRId.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRVector4.h>
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
#include "MRVector.h"

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
    ///
    bindTypedVector<Triangulation, FaceId>( "Triangulation" );
    bindTypedVector<Dipoles, NodeId>( "Dipoles" );
    ///


    ///
    bindTypedVector<FaceMap, FaceId>( "FaceMap" );
    bindTypedVector<VertMap, VertId>( "VertMap" );
    // NOTE: `EdgeMap` -> `Vector<EdgeId, EdgeId>`
    bindTypedVector<EdgeMap, EdgeId>( "EdgeMap" );

    bindTypedVector<Vector<VertId, EdgeId>, EdgeId>( "VertIdEdgeIdMap" );
    bindTypedVector<Vector<EdgeId, VertId>, VertId>( "EdgeIdVertIdMap" );
    bindTypedVector<Vector<EdgeId, FaceId>, FaceId>( "EdgeIdFaceIdMap" );
    bindTypedVector<Vector<FaceId, EdgeId>, EdgeId>( "FaceIdEdgeIdMap" );

    bindTypedVector<Vector<ModelPointsData, ObjId>, ObjId>( "ModelPointsDataObjIdMap" );
    bindTypedVector<Vector<MeshBuilder::VertSpan, FaceId>, FaceId>( "VertSpanFaceIdMap" );
    ///

    
    ///
    bindTypedVector<UndirectedEdgeMap, UndirectedEdgeId>( "UndirectedEdgeMap" );
    bindTypedVector<ObjMap, ObjId>( "ObjMap" );
    bindTypedVector<WholeEdgeMap, UndirectedEdgeId>( "WholeEdgeMap" );
    bindTypedVector<UndirectedEdge2RegionMap, UndirectedEdgeId>( "UndirectedEdge2RegionMap" );
    bindTypedVector<Face2RegionMap, FaceId>( "Face2RegionMap" );
    bindTypedVector<Vert2RegionMap, VertId>( "Vert2RegionMap" );
    ///
}

EMSCRIPTEN_BINDINGS( CoordsTypedModule )
{
    // NOTE: `VertNormals` is the same as `VertCoords`
    // 
    // It will throw `BindingError: Cannot register type 'VertUVCoords' twice`
    // BIND_TYPED_VECTOR( VertNormals, Vector3f, VertId );
    // 
    bindTypedVector<VertCoords, VertId>( "VertCoords" );
    // NOTE: `VertUVCoords` is the same as `VertCoords2`
    // BIND_TYPED_VECTOR( VertUVCoords, UVCoord, VertId );
    bindTypedVector<VertCoords2, VertId>( "VertCoords2" );
    bindTypedVector<FaceNormals, FaceId>( "FaceNormals" );
}

EMSCRIPTEN_BINDINGS( ColorsTypedModule )
{
    bindTypedVector<TexturePerFace, FaceId>( "TexturePerFace" );
    bindTypedVector<VertColors, VertId>( "VertColors" );
    bindTypedVector<FaceColors, FaceId>( "FaceColors" );
    bindTypedVector<EdgeColors, EdgeId>( "EdgeColors" );
    bindTypedVector<UndirectedEdgeColors, UndirectedEdgeId>( "UndirectedEdgeColors" );
}

EMSCRIPTEN_BINDINGS( ScalarsTypedModule )
{
    bindTypedVector<VertScalars, VertId>( "VertScalars" );
    bindTypedVector<FaceScalars, FaceId>( "FaceScalars" );
    bindTypedVector<EdgeScalars, EdgeId>( "EdgeScalars" );
    bindTypedVector<UndirectedEdgeScalars, UndirectedEdgeId>( "UndirectedEdgeScalars" );
}

EMSCRIPTEN_BINDINGS( NodeVecTypedModule )
{
    bindTypedVector<AABBTreePoints::NodeVec, NodeId>( "NodeVec" );
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
