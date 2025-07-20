#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRPointsToMeshProjector.h>
#include <MRMesh/MRMeshProject.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( MeshProjectModule )
{
    class_<MeshProjectionResult>( "MeshProjectionResult" )
        .constructor<>()

        .property( "proj", &MeshProjectionResult::proj )   // PointOnFace
        .property( "mtp", &MeshProjectionResult::mtp )     // MeshTriPoint
        .property( "distSq", &MeshProjectionResult::distSq )
        .function( "valid", &MeshProjectionResult::valid )
        .function( "opbool", select_overload<bool() const>( &MeshProjectionResult::operator bool ) );
}
