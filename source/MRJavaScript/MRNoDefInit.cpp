#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRNoDefInit.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( NoDefInitModule )
{
    class_<NoDefInit<FaceId>>( "NoDefInitFaceId" )
        .constructor<>();
    class_<NoDefInit<VertId>>( "NoDefInitVertId" )
        .constructor<>();
    class_<NoDefInit<EdgeId>>( "NoDefInitEdgeId" )
        .constructor<>();
    class_<NoDefInit<UndirectedEdgeId>>( "NoDefInitUndirectedEdgeId" )
        .constructor<>();
}
