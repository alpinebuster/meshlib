#include <optional>

#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMesh.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MREdgeLengthMesh.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( EdgeLengthMeshModule )
{
    class_<EdgeLengthMesh>( "EdgeLengthMesh" )
        .constructor<>()
        .class_function( "fromMesh", &EdgeLengthMesh::fromMesh )

        .property( "topology", &EdgeLengthMesh::topology )
        .property( "edgeLengths", &EdgeLengthMesh::edgeLengths )

        .function( "leftCotan", &EdgeLengthMesh::leftCotan )
        .function( "cotan", &EdgeLengthMesh::cotan )
        .function( "isDelone", &EdgeLengthMesh::isDelone )
        .function( "edgeLengthAfterFlip", &EdgeLengthMesh::edgeLengthAfterFlip )
        .function( "flipEdge", &EdgeLengthMesh::flipEdge );
}
