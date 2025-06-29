#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshExtrude.h>
#include <MRMesh/MRRegionBoundary.h>
#include <MRMesh/MRBitSet.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshFillHoleModule )
{
	class_<MakeDegenerateBandAroundRegionParams>( "MakeDegenerateBandAroundRegionParams" )
		.constructor<>();
	
	function( "makeDegenerateBandAroundRegion", &makeDegenerateBandAroundRegion );
}
