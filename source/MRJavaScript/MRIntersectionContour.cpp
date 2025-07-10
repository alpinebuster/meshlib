#include <optional>
#include <memory>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshExtrude.h>
#include <MRMesh/MRRegionBoundary.h>
#include <MRMesh/MRIntersectionContour.h>
#include <MRMesh/MRMeshCollidePrecise.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( IntersectionContourModule )
{
    // ContinuousContour is `std::vector<VarEdgeTri>`
    register_vector<VarEdgeTri>( "ContinuousContour" );
    // `ContinuousContours` is `std::vector<ContinuousContour>`
    register_vector<ContinuousContour>( "ContinuousContours" );
}
