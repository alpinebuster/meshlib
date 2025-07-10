#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRSurroundingContour.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( SurroundingContourModule )
{
	function( "surroundingContourEdges",
		select_overload<Expected<EdgeLoop>( const Mesh&, std::vector<EdgeId>, const EdgeMetric&, const Vector3f& )>
		( &surroundingContour ),
		allow_raw_pointers()
	);

	function( "surroundingContourVertices",
		select_overload<Expected<EdgeLoop>( const Mesh&, std::vector<VertId>, const EdgeMetric&, const Vector3f& )>
		( &surroundingContour ),
		allow_raw_pointers()
	);
}
