#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MREdgePoint.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( EdgePointModule )
{
    class_<EdgePoint>( "EdgePoint" )
        .constructor<>();
}
