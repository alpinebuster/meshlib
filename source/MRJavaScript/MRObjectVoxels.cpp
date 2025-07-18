#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRSurfaceDistanceBuilder.h>

#include <MRVoxels/MRFloatGrid.h>
#include <MRVoxels/MRVDBFloatGrid.h>
#include <MRVoxels/MRVDBConversions.h>
#include <MRVoxels/MROpenVDBHelper.h>
#include <MRVoxels/MRObjectVoxels.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( ObjectVoxelsModule )
{
}
