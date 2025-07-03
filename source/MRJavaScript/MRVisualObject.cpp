#include <optional>

#include <emscripten/bind.h>
#include <emscripten/val.h>

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
