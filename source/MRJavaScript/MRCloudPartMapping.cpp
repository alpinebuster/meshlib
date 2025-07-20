#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRCloudPartMapping.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( CloudPartMappingModule )
{
    class_<CloudPartMapping>( "CloudPartMapping" )
        .constructor<>()
        .property( "src2tgtVerts", &CloudPartMapping::src2tgtVerts, return_value_policy::reference() )
        .property( "tgt2srcVerts", &CloudPartMapping::tgt2srcVerts, return_value_policy::reference() );
}
