#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRBuffer.h>

#include "MRBuffer.h"

using namespace emscripten;
using namespace MR;


using FaceBMapBuffer = Buffer<FaceId, FaceId>;
using VertBMapBuffer = Buffer<VertId, VertId>;
using EdgeBMapBuffer = Buffer<EdgeId, EdgeId>;
using UndirectedEdgeBMapBuffer = Buffer<UndirectedEdgeId, UndirectedEdgeId>;
using WholeEdgeBMapBuffer = Buffer<EdgeId, UndirectedEdgeId>;


namespace MRJS
{

EMSCRIPTEN_BINDINGS( BufferModule )
{
    ///
    BufferBinding<FaceId, FaceId>( "FaceBMapBuffer" ).init();
    BufferBinding<VertId, VertId>( "VertBMapBuffer" ).init();
    BufferBinding<EdgeId, EdgeId>( "EdgeBMapBuffer" ).init();
    BufferBinding<UndirectedEdgeId, UndirectedEdgeId>( "UndirectedEdgeBMapBuffer" ).init();
    BufferBinding<EdgeId, UndirectedEdgeId>( "WholeEdgeBMapBuffer" ).init();
    ///


    ///
    class_<PackMapping>( "PackMapping" )
        .constructor<>()
        // .property( "e", &PackMapping::e, allow_raw_pointers() )
        // .property( "f", &PackMapping::f, allow_raw_pointers() )
        // .property( "v", &PackMapping::v, allow_raw_pointers() )
        ;
    ///
}

}
