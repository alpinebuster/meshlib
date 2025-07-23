#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRIdentifyVertices.h>

using namespace emscripten;
using namespace MR;
using namespace MeshBuilder;


EMSCRIPTEN_BINDINGS( IdentifyVerticesModule )
{   
    class_<VertexIdentifier>( "VertexIdentifier" )
        .constructor<>()

        .function( "reserve", &VertexIdentifier::reserve )
        .function( "numTris", &VertexIdentifier::numTris )
        .function( "takeTriangulation", &VertexIdentifier::takeTriangulation )
        .function( "takePoints", &VertexIdentifier::takePoints );


    class_<equalVector3f>( "EqualVector3f" )
        .constructor<>()

        .function( "opcall", select_overload<bool (const Vector3f &, const Vector3f &) const>( &equalVector3f::operator() ) );
}
