#include <emscripten/bind.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRVector4.h>
#include <MRMesh/MRBuffer.h>
#include <MRMesh/MRVector.h>

#include "MRVector.h"

using namespace emscripten;
using namespace MR;


// ------------------------------------------------------------------------
// Bind the Embind interface for `Vector*`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( VectorModule )
{
    ///
    bindTypedVector<Vector<double, EdgeId>, EdgeId>( "VectorDoubleEdgeId" );
    bindTypedVector<Vector<double, UndirectedEdgeId>, UndirectedEdgeId>( "VectorDoubleUndirectedEdgeId" );
    bindTypedVector<Vector<double, FaceId>, FaceId>( "VectorDoubleVertId" );
    bindTypedVector<Vector<double, PixelId>, PixelId>( "VectorDoublePixelId" );
    bindTypedVector<Vector<double, VoxelId>, VoxelId>( "VectorDoubleVoxelId" );
    bindTypedVector<Vector<double, RegionId>, RegionId>( "VectorDoubleRegionId" );
    bindTypedVector<Vector<double, NodeId>, NodeId>( "VectorDoubleNodeId" );
    bindTypedVector<Vector<double, ObjId>, ObjId>( "VectorDoubleObjId" );
    bindTypedVector<Vector<double, TextureId>, TextureId>( "VectorDoubleTextureId" );
    bindTypedVector<Vector<double, GraphVertId>, GraphVertId>( "VectorDoubleGraphVertId" );
    bindTypedVector<Vector<double, GraphEdgeId>, GraphEdgeId>( "VectorDoubleGraphEdgeId" );
    ///


    ///
    bindTypedVector<Vector<size_t, EdgeId>, EdgeId>( "VectorSizeTEdgeId" );
    bindTypedVector<Vector<size_t, UndirectedEdgeId>, UndirectedEdgeId>( "VectorSizeTUndirectedEdgeId" );
    bindTypedVector<Vector<size_t, FaceId>, FaceId>( "VectorSizeTVertId" );
    bindTypedVector<Vector<size_t, PixelId>, PixelId>( "VectorSizeTPixelId" );
    bindTypedVector<Vector<size_t, VoxelId>, VoxelId>( "VectorSizeTVoxelId" );
    bindTypedVector<Vector<size_t, RegionId>, RegionId>( "VectorSizeTRegionId" );
    bindTypedVector<Vector<size_t, NodeId>, NodeId>( "VectorSizeTNodeId" );
    bindTypedVector<Vector<size_t, ObjId>, ObjId>( "VectorSizeTObjId" );
    bindTypedVector<Vector<size_t, TextureId>, TextureId>( "VectorSizeTTextureId" );
    bindTypedVector<Vector<size_t, GraphVertId>, GraphVertId>( "VectorSizeTGraphVertId" );
    bindTypedVector<Vector<size_t, GraphEdgeId>, GraphEdgeId>( "VectorSizeTGraphEdgeId" );
    ///


    ///
    bindTypedVector<Vector<int, EdgeId>, EdgeId>( "VectorIntEdgeId" );
    bindTypedVector<Vector<int, UndirectedEdgeId>, UndirectedEdgeId>( "VectorIntUndirectedEdgeId" );
    bindTypedVector<Vector<int, FaceId>, FaceId>( "VectorIntVertId" );
    bindTypedVector<Vector<int, PixelId>, PixelId>( "VectorIntPixelId" );
    bindTypedVector<Vector<int, VoxelId>, VoxelId>( "VectorIntVoxelId" );
    bindTypedVector<Vector<int, RegionId>, RegionId>( "VectorIntRegionId" );
    bindTypedVector<Vector<int, NodeId>, NodeId>( "VectorIntNodeId" );
    bindTypedVector<Vector<int, ObjId>, ObjId>( "VectorIntObjId" );
    bindTypedVector<Vector<int, TextureId>, TextureId>( "VectorIntTextureId" );
    bindTypedVector<Vector<int, GraphVertId>, GraphVertId>( "VectorIntGraphVertId" );
    bindTypedVector<Vector<int, GraphEdgeId>, GraphEdgeId>( "VectorIntGraphEdgeId" );
    ///


    ///
    bindTypedVector<Vector<int, size_t>, size_t>( "VectorIntSizeT" );
    bindTypedVector<Vector<float, size_t>, size_t>( "VectorFloatSizeT" );
    bindTypedVector<Vector<double, size_t>, size_t>( "VectorDoubleSizeT" );
    ///


    function( "getAti", select_overload<int   ( const Vector<int, size_t>&,    size_t, int    )>( &getAt ));
    function( "getAtf", select_overload<float ( const Vector<float, size_t>&,  size_t, float  )>( &getAt ) );
    function( "getAtd", select_overload<double( const Vector<double, size_t>&, size_t, double )>( &getAt ) );
}
