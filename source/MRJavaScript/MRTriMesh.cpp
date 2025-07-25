#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRTriMesh.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( TriMeshModule )
{
    class_<TriMesh>( "TriMesh" )
        .smart_ptr<std::shared_ptr<TriMesh>>( "TriMeshSharedPtr" )
        .constructor<>()

        .class_function( "copy", optional_override( [] ( const TriMesh& other )
        {
            return TriMesh( other );
        } ) )

        .property( "tris", &TriMesh::tris )
        .property( "points", &TriMesh::points );
}
