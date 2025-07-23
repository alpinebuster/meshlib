#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRPartMapping.h>
#include <MRMesh/MRMeshTopology.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( PartMappingModule )
{
    class_<PartMapping>( "PartMapping" )
        .constructor<>()

        .function( "clear", &PartMapping::clear );
}
