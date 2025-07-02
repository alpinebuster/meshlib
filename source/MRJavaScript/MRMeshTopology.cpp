#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshTopology.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshTopologyModule )
{
    class_<MeshTopology>( "MeshTopology" )
        .constructor<>();
}
