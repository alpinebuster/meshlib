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
    bindTypedUnionFind<VertId>( "UnionFindVertId" );
    bindTypedUnionFind<EdgeId>( "UnionFindEdgeId" );
    bindTypedUnionFind<UndirectedEdgeId>( "UnionFindUndirectedEdgeId" );
    bindTypedUnionFind<FaceId>( "UnionFindFaceId" );
    bindTypedUnionFind<PixelId>( "UnionFindPixelId" );
    bindTypedUnionFind<VoxelId>( "UnionFindVoxelId" );
    bindTypedUnionFind<RegionId>( "UnionFindRegionId" );
    bindTypedUnionFind<NodeId>( "UnionFindNodeId" );
    bindTypedUnionFind<ObjId>( "UnionFindObjId" );
    bindTypedUnionFind<TextureId>( "UnionFindTextureId" );
    bindTypedUnionFind<GraphVertId>( "UnionFindGraphVertId" );
    bindTypedUnionFind<GraphEdgeId>( "UnionFindGraphEdgeId" );
}
