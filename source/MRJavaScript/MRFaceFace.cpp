#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRFaceFace.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( FaceFaceModule )
{
    class_<FaceFace>( "FaceFace" )
        .constructor<>()
        .constructor<FaceId, FaceId>()

        .property( "aFace", &FaceFace::aFace )
        .property( "bFace", &FaceFace::bFace )
        .function( "equals", optional_override( [] ( const FaceFace& self, const FaceFace& other ) -> bool
        {
            return self.aFace == other.aFace && self.bFace == other.bFace;
        } ) );



    class_<UndirectedEdgeUndirectedEdge>( "UndirectedEdgeUndirectedEdge" )
        .constructor<>()
        .constructor<UndirectedEdgeId, UndirectedEdgeId>()

        .property( "aUndirEdge", &UndirectedEdgeUndirectedEdge::aUndirEdge )
        .property( "bUndirEdge", &UndirectedEdgeUndirectedEdge::bUndirEdge )
        .function( "equals", optional_override( [] ( const UndirectedEdgeUndirectedEdge& self, const UndirectedEdgeUndirectedEdge& other ) -> bool
        {
            return self.aUndirEdge == other.aUndirEdge && self.bUndirEdge == other.bUndirEdge;
        } ) );
}
