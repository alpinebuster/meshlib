#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRFillContour.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRId.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( FillContourModule )
{
    function( "fillContourLeft",
        select_overload<FaceBitSet( const MeshTopology&, const EdgePath& )>( &fillContourLeft ) );

    function( "fillContourLeftMultiple",
        select_overload<FaceBitSet( const MeshTopology&, const std::vector<EdgePath>& )>( &fillContourLeft ) );
}
