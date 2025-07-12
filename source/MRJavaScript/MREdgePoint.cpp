#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MREdgePoint.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( EdgePointModule )
{
    class_<EdgePoint>( "EdgePoint" )
        .constructor<>();
    
    class_<EdgePointPair>( "EdgePointPair" )
        .constructor<>();
    
    class_<EdgeSegment>( "EdgeSegment" )
        .constructor<>();


	function( "fromSameTriangle", select_overload<bool ( const MeshTopology&, EdgePoint&, EdgePoint& )>( &fromSameTriangle ));
}
