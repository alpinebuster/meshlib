#include <fstream>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRMeshTriPoint.h>
#include <MRMesh/MRProgressCallback.h>
#include <MRMesh/MRExpected.h>
#include <MRMesh/MRMeshTopology.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshTopologyModule )
{
    class_<MeshTopology>( "MeshTopology" )
        .constructor<>()
        
        .function( "isClosed", &MeshTopology::isClosed, allow_raw_pointers() )
        .function( "getTriangulation", &MeshTopology::getTriangulation, return_value_policy::reference() )
        .function( "findHoleRepresentiveEdges", &MeshTopology::findHoleRepresentiveEdges, allow_raw_pointers() );
}
