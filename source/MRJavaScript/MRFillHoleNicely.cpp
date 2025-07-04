#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshSubdivide.h>
#include <MRMesh/MRPositionVertsSmoothly.h>
#include <MRMesh/MRMeshComponents.h>
#include <MRMesh/MRFillHoleNicely.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( FillHoleNicelyModule )
{
}
