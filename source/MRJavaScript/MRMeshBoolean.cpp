#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRBooleanOperation.h>
#include <MRMesh/MREdgePaths.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRMeshBoolean.h>

using namespace emscripten;
using namespace MR;

BooleanResult performBoolean(
    const Mesh& meshA,
    const Mesh& meshB,
    BooleanOperation op )
{
    return MR::boolean( meshA, meshB, op );
}

EMSCRIPTEN_BINDINGS( MeshBooleanModule )
{
    class_<BooleanResult>( "BooleanResult" )
        .constructor<>()
        .property( "mesh", &BooleanResult::mesh )
        .property( "meshABadContourFaces", &BooleanResult::meshABadContourFaces )
        .property( "meshBBadContourFaces", &BooleanResult::meshBBadContourFaces )
        .property( "errorString", &BooleanResult::errorString )
        .function( "valid", &BooleanResult::valid )
        .function( "getMesh", optional_override( [] ( BooleanResult& br )
        {
            return br.mesh;
        } ) );

    function( "performBoolean", &performBoolean );
}
