#include <optional>
#include <memory>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshExtrude.h>
#include <MRMesh/MRRegionBoundary.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRMeshCollidePrecise.h>
#include <MRMesh/MRIntersectionContour.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( IntersectionContourModule )
{
	function( "orderIntersectionContours", &orderIntersectionContours );
	function( "orderSelfIntersectionContours", &orderSelfIntersectionContours );

	function( "isClosed", &isClosed );
	function( "detectLoneContours", &detectLoneContours );
	function( "removeLoneDegeneratedContours", &removeLoneDegeneratedContours, allow_raw_pointers() );
	function( "removeLoneContours", &removeLoneContours );
}
