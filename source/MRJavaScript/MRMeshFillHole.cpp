#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFillHole.h>
#include <MRMesh/MRMeshFwd.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshFillHoleModule )
{
	function( "extendHolePlane", select_overload<EdgeId( Mesh&, EdgeId, const Plane3f& )>( [] ( Mesh& mesh, EdgeId edgeId, const Plane3f& plane ) -> EdgeId
	{
		return extendHole( mesh, edgeId, plane, nullptr );
	}
		),
		allow_raw_pointers()
	);

	// Version with optional FaceBitSet parameter
	function( "extendHolePlaneWithFaces",
		select_overload<EdgeId( Mesh&, EdgeId, const Plane3f&, FaceBitSet* )>( extendHole ),
		allow_raw_pointers()
	);
}
