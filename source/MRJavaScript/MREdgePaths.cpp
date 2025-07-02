#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshRelax.h>
#include <MRMesh/MREdgePaths.h>
#include <MRMesh/MREdgeMetric.h>
#include <MRMesh/MRMeshRelax.h>
#include <MRMesh/MRMesh.h>

#include "MRUtils.h"

using namespace emscripten;
using namespace MR;

val smoothExtractedRegionBoundary( Mesh& mesh, int numIters = 6 )
{
    // 1) Construct a `FaceBitSet` that marks all faces in the mesh as "selected"
    //    This way, the outer boundary of `regionFaces` is exactly irregular closed circle
    FaceBitSet regionFaces( mesh.topology.faceSize() );
    regionFaces.set(); // Set all bits to 1

    // 2) Call the smoothing function
    smoothRegionBoundary( mesh, regionFaces, numIters );

    // 3) Update internal cache (normals, acceleration structures, etc.)
    mesh.invalidateCaches();

    val meshData = MRJS::exportMeshData( mesh );
    val obj = val::object();
    obj.set( "success", true );
    obj.set( "mesh", meshData );

    return obj;
}

EMSCRIPTEN_BINDINGS( MeshEdgePathsModule )
{
    function( "smoothExtractedRegionBoundary", &smoothExtractedRegionBoundary );
}
