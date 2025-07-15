#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVolumeIndexer.h>
#include <MRMesh/MRPointsToMeshProjector.h>

#include <MRVoxels/MRVDBConversions.h>
#include <MRVoxels/MRMeshToDistanceVolume.h>
#include <MRVoxels/MRTeethMaskToDirectionVolume.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( TeethMaskToDirectionVolumeModule )
{
}
