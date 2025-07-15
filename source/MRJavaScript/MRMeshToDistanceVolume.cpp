#include <tuple>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRAABBTree.h>
#include <MRMesh/MRPointsToMeshProjector.h>
#include <MRMesh/MRVolumeIndexer.h>
#include <MRMesh/MRIsNaN.h>

#include <MRVoxels/MRVDBConversions.h>
#include <MRVoxels/MRMeshToDistanceVolume.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( MeshToDistanceVolumeModule )
{
}
