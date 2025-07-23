#include <MRPch/MRWasm.h>

#include <MRMesh/MRAABBTreeObjects.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( AABBTreeObjectsModule )
{
    class_<AABBTreeObjects>( "AABBTreeObjects" )
        .constructor<>();
}
