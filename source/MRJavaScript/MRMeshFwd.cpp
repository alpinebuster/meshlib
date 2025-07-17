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
#include "MRBuffer.h"

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( MeshFwdModule )
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
    MRJS::bindTypedBMap<FaceBMap, FaceId, FaceId>( "FaceBMap" );
    MRJS::bindTypedBMap<VertBMap, VertId, VertId>( "VertBMap" );
    MRJS::bindTypedBMap<EdgeBMap, EdgeId, EdgeId>( "EdgeBMap" );
    MRJS::bindTypedBMap<UndirectedEdgeBMap, UndirectedEdgeId, UndirectedEdgeId>( "UndirectedEdgeBMap" );
    MRJS::bindTypedBMap<WholeEdgeBMap, EdgeId, UndirectedEdgeId>( "WholeEdgeBMap" );
    ///


    MRJS::bindTypedBMap<BMap<VertId, size_t>, VertId, size_t>( "VertIdSizeTBMap" );
    MRJS::bindTypedBMap<BMap<UndirectedEdgeId, size_t>, UndirectedEdgeId, size_t>( "UndirectedEdgeIdSizeTBMap" );
    MRJS::bindTypedBMap<BMap<FaceId, size_t>, FaceId, size_t>( "FaceIdSizeTBMap" );
}

EMSCRIPTEN_BINDINGS( MapTypedModule )
{
    ///
    MRJS::bindTypedVector<Triangulation, FaceId>( "Triangulation" );
    MRJS::bindTypedVector<Dipoles, NodeId>( "Dipoles" );
    ///


    ///
    MRJS::bindTypedVector<FaceMap, FaceId>( "FaceMap" );
    MRJS::bindTypedVector<VertMap, VertId>( "VertMap" );
    // NOTE: `EdgeMap` -> `Vector<EdgeId, EdgeId>`
    MRJS::bindTypedVector<EdgeMap, EdgeId>( "EdgeMap" );

    MRJS::bindTypedVector<Vector<VertId, EdgeId>, EdgeId>( "VertIdEdgeIdMap" );
    MRJS::bindTypedVector<Vector<EdgeId, VertId>, VertId>( "EdgeIdVertIdMap" );
    MRJS::bindTypedVector<Vector<EdgeId, FaceId>, FaceId>( "EdgeIdFaceIdMap" );
    MRJS::bindTypedVector<Vector<FaceId, EdgeId>, EdgeId>( "FaceIdEdgeIdMap" );

    MRJS::bindTypedVector<Vector<ModelPointsData, ObjId>, ObjId>( "ModelPointsDataObjIdMap" );
    MRJS::bindTypedVector<Vector<MeshBuilder::VertSpan, FaceId>, FaceId>( "VertSpanFaceIdMap" );
    ///

    
    ///
    MRJS::bindTypedVector<UndirectedEdgeMap, UndirectedEdgeId>( "UndirectedEdgeMap" );
    MRJS::bindTypedVector<ObjMap, ObjId>( "ObjMap" );
    MRJS::bindTypedVector<WholeEdgeMap, UndirectedEdgeId>( "WholeEdgeMap" );
    MRJS::bindTypedVector<UndirectedEdge2RegionMap, UndirectedEdgeId>( "UndirectedEdge2RegionMap" );
    MRJS::bindTypedVector<Face2RegionMap, FaceId>( "Face2RegionMap" );
    MRJS::bindTypedVector<Vert2RegionMap, VertId>( "Vert2RegionMap" );
    ///
}

EMSCRIPTEN_BINDINGS( CoordsTypedModule )
{
    // NOTE: `VertNormals` is the same as `VertCoords`
    // 
    // It will throw `BindingError: Cannot register type 'VertUVCoords' twice`
    // BIND_TYPED_VECTOR( VertNormals, Vector3f, VertId );
    // 
    MRJS::bindTypedVector<VertCoords, VertId>( "VertCoords" );
    // NOTE: `VertUVCoords` is the same as `VertCoords2`
    // BIND_TYPED_VECTOR( VertUVCoords, UVCoord, VertId );
    MRJS::bindTypedVector<VertCoords2, VertId>( "VertCoords2" );
    MRJS::bindTypedVector<FaceNormals, FaceId>( "FaceNormals" );
}

EMSCRIPTEN_BINDINGS( ColorsTypedModule )
{
    MRJS::bindTypedVector<TexturePerFace, FaceId>( "TexturePerFace" );
    MRJS::bindTypedVector<VertColors, VertId>( "VertColors" );
    MRJS::bindTypedVector<FaceColors, FaceId>( "FaceColors" );
    MRJS::bindTypedVector<EdgeColors, EdgeId>( "EdgeColors" );
    MRJS::bindTypedVector<UndirectedEdgeColors, UndirectedEdgeId>( "UndirectedEdgeColors" );
}

EMSCRIPTEN_BINDINGS( ScalarsTypedModule )
{
    MRJS::bindTypedVector<VertScalars, VertId>( "VertScalars" );
    MRJS::bindTypedVector<FaceScalars, FaceId>( "FaceScalars" );
    MRJS::bindTypedVector<EdgeScalars, EdgeId>( "EdgeScalars" );
    MRJS::bindTypedVector<UndirectedEdgeScalars, UndirectedEdgeId>( "UndirectedEdgeScalars" );
}

EMSCRIPTEN_BINDINGS( NodeVecTypedModule )
{
    MRJS::bindTypedVector<AABBTreePoints::NodeVec, NodeId>( "NodeVec" );
}
