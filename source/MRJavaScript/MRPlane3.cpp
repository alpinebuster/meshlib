#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRPlane3.h>
#include <MRMesh/MRMeshFwd.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( PlaneModule )
{
    class_<Plane3f>( "Plane3f" )
        .constructor<>();

    class_<Plane3f>( "Plane3i" )
        .constructor<>();
    
    class_<Plane3f>( "Plane3d" )
        .constructor<>();
    
    class_<Plane3f>( "Plane3ll" )
        .constructor<>();
}
