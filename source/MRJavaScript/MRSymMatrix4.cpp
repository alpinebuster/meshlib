#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRSymMatrix4.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( SymMatrix4Module )
{
    class_<SymMatrix4b>( "SymMatrix4b" )
        .constructor<>();

    class_<SymMatrix4i>( "SymMatrix4i" )
        .constructor<>();

    class_<SymMatrix4ll>( "SymMatrix4ll" )
        .constructor<>();
    
    class_<SymMatrix4f>( "SymMatrix4f" )
        .constructor<>();
    
    class_<SymMatrix4d>( "SymMatrix4d" )
        .constructor<>();
}
