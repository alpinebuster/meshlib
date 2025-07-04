#include <array>
#include <memory>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRAABBTree.h>
#include <MRMesh/MRFaceFace.h>
#include <MRMesh/MRMeshCollidePrecise.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshCollidePreciseModule )
{
    class_<EdgeTri>( "EdgeTri" )
        .constructor<>()
        .constructor<EdgeId, FaceId>()
        .property( "edge", &EdgeTri::edge )
        .property( "tri", &EdgeTri::tri );


    class_<VarEdgeTri>( "VarEdgeTri" )
        .constructor<>()  // Default constructor
        .constructor<bool, EdgeId, FaceId>()  // Main constructor
        .constructor<bool, const EdgeTri&>()  // EdgeTri constructor

        .property( "edge", &VarEdgeTri::edge )
        .property( "tri", &VarEdgeTri::tri )
        .property( "isEdgeATriB", &VarEdgeTri::isEdgeATriB )
        .property( "valid", &VarEdgeTri::valid )
        .function( "edgeTri", &VarEdgeTri::edgeTri );
}
