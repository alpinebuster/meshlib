#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRMeshPart.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshPartModule )
{
    class_<MeshPart>( "MeshPart" )
        .constructor<const Mesh&>()
        .constructor<const Mesh&, const TypedBitSet<Id<FaceTag>>*>( allow_raw_pointers() )
        .function("getMesh", optional_override([](const MeshPart& mp) -> const Mesh& { 
            return mp.mesh; 
        }), allow_raw_pointers())
        .property( "region", &MeshPart::region, allow_raw_pointers() );

    class_<MeshVertPart>( "MeshVertPart" )
        .constructor<const Mesh&>()
        .constructor<const Mesh&, const TypedBitSet<Id<VertTag>>*>( allow_raw_pointers() )
        .function("getMesh", optional_override([](const MeshVertPart& mvp) -> const Mesh& { 
            return mvp.mesh; 
        }), allow_raw_pointers())
        .property( "region", &MeshVertPart::region, allow_raw_pointers() );
}
