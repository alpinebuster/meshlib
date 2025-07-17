#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRUnionFind.h>

#include "MRUnionFind.h"

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( UnionFindModule )
{
    MRJS::bindTypedUnionFind<VertId>( "UnionFindVertId" );
    MRJS::bindTypedUnionFind<EdgeId>( "UnionFindEdgeId" );
    MRJS::bindTypedUnionFind<UndirectedEdgeId>( "UnionFindUndirectedEdgeId" );
    MRJS::bindTypedUnionFind<FaceId>( "UnionFindFaceId" );
    MRJS::bindTypedUnionFind<PixelId>( "UnionFindPixelId" );
    MRJS::bindTypedUnionFind<VoxelId>( "UnionFindVoxelId" );
    MRJS::bindTypedUnionFind<RegionId>( "UnionFindRegionId" );
    MRJS::bindTypedUnionFind<NodeId>( "UnionFindNodeId" );
    MRJS::bindTypedUnionFind<ObjId>( "UnionFindObjId" );
    MRJS::bindTypedUnionFind<TextureId>( "UnionFindTextureId" );
    MRJS::bindTypedUnionFind<GraphVertId>( "UnionFindGraphVertId" );
    MRJS::bindTypedUnionFind<GraphEdgeId>( "UnionFindGraphEdgeId" );
}
