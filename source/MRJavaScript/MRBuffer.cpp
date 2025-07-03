#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRBuffer.h>

using namespace emscripten;
using namespace MR;

using FaceBMapBuffer = Buffer<FaceId, FaceId>;
using VertBMapBuffer = Buffer<VertId, VertId>;
using EdgeBMapBuffer = Buffer<EdgeId, EdgeId>;
using UndirectedEdgeBMapBuffer = Buffer<UndirectedEdgeId, UndirectedEdgeId>;
using WholeEdgeBMapBuffer = Buffer<EdgeId, UndirectedEdgeId>;

EMSCRIPTEN_BINDINGS( BufferModule )
{
    class_<FaceBMapBuffer>( "FaceBMapBuffer" )
        .constructor<>()
        .constructor<size_t>()

        .function( "capacity", &FaceBMapBuffer::capacity )
        .function( "size", &FaceBMapBuffer::size )
        .function( "empty", &FaceBMapBuffer::empty )
        .function( "clear", &FaceBMapBuffer::clear )
        .function( "resize", &FaceBMapBuffer::resize )

        // FIXME
        // .function( "get", select_overload<const FaceId& ( FaceId ) const>( &FaceBMapBuffer::operator[] ) )
        // .function( "set", select_overload<FaceId& ( FaceId )>( &FaceBMapBuffer::operator[] ) )
        .function("get", optional_override([](const FaceBMapBuffer& buf, FaceId id) -> FaceId {
            return buf[id];  // Return copy (avoid references)
        }))
        .function("set", optional_override([](FaceBMapBuffer& buf, FaceId id, const FaceId& value) {
            buf[id] = value;
        } ) )

        // FIXME
        // .function( "data", select_overload<FaceId* ()>( &FaceBMapBuffer::data ), allow_raw_pointers() )
        // .function( "dataConst", select_overload<FaceId* () const>( &FaceBMapBuffer::data ), allow_raw_pointers() )
        .function( "dataPtr", optional_override( [] ( FaceBMapBuffer& self )
        {
            return self.data(); // T*
        }), allow_raw_pointers())

        .function( "beginId", &FaceBMapBuffer::beginId )
        .function( "backId", &FaceBMapBuffer::backId )
        .function( "endId", &FaceBMapBuffer::endId )
        .function( "heapBytes", &FaceBMapBuffer::heapBytes );

    
    class_<VertBMapBuffer>( "VertBMapBuffer" )
        .constructor<>()
        .constructor<size_t>();

    
    class_<EdgeBMapBuffer>( "EdgeBMapBuffer" )
        .constructor<>()
        .constructor<size_t>();

    
    class_<UndirectedEdgeBMapBuffer>( "UndirectedEdgeBMapBuffer" )
        .constructor<>()
        .constructor<size_t>();

    
    class_<WholeEdgeBMapBuffer>( "WholeEdgeBMapBuffer" )
        .constructor<>()
        .constructor<size_t>();
}
