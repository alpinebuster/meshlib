#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMatrix4.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( Matrix4Module )
{
    class_<Matrix4b>( "Matrix4b" )
        .constructor<>();

    class_<Matrix4i>( "Matrix4i" )
        .constructor<>();

    class_<Matrix4ll>( "Matrix4ll" )
        .constructor<>();
    
    class_<Matrix4f>( "Matrix4f" )
        .constructor<>();
    
    class_<Matrix4d>( "Matrix4d" )
        .constructor<>();
}
