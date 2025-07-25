#include <optional>

#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVisualObject.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( VisualObjectModule )
{
    class_<VisualObject>( "VisualObject" )
        .constructor<>();
}
