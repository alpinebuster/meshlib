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


EMSCRIPTEN_BINDINGS( BufferModule )
{
    ///
    MRJS::BufferBinding<FaceId, FaceId>( "FaceBMapBuffer" ).init();
    MRJS::BufferBinding<VertId, VertId>( "VertBMapBuffer" ).init();
    MRJS::BufferBinding<EdgeId, EdgeId>( "EdgeBMapBuffer" ).init();
    MRJS::BufferBinding<UndirectedEdgeId, UndirectedEdgeId>( "UndirectedEdgeBMapBuffer" ).init();
    MRJS::BufferBinding<EdgeId, UndirectedEdgeId>( "WholeEdgeBMapBuffer" ).init();

    MRJS::BufferBinding<FaceId, size_t>( "FaceIdEdgeIdSizeTBMapBuffer" ).init();
    MRJS::BufferBinding<VertId, size_t>( "VertIdSizeTBMapBuffer" ).init();
    MRJS::BufferBinding<EdgeId, size_t>( "EdgeIdSizeTBMapBuffer" ).init();
    MRJS::BufferBinding<UndirectedEdgeId, size_t>( "UndirectedEdgeIdSizeTBMapBuffer" ).init();
    ///


    ///
    class_<PackMapping>( "PackMapping" )
        // NOTE:
        // See `source/MRJavaScript/MRMesh.cpp#L161` & reference `https://github.com/emscripten-core/emscripten/issues/9343`
        // 
        // When using `std::unique_ptr<PackMapping>` as the return type, 
        // Emscripten automatically handles the binding of the `std::unique_ptr` smart pointer,
        // and there is no need( nor should there be ) to explicitly call:
        //
        // .smart_ptr<std::unique_ptr<PackMapping>>( "PackMappingUniquePtr" )
        // 
        .constructor<>()

        .function( "getE", optional_override( [] ( PackMapping& self ) -> UndirectedEdgeBMap*
        {
            return &self.e;
        } ), allow_raw_pointers() )
        .function( "setE", optional_override( []( PackMapping& self, UndirectedEdgeBMap& newE ) {
            self.e = std::move( newE );
        } ), allow_raw_pointers() )
        .function( "setEWithPtr", optional_override( []( PackMapping& self, UndirectedEdgeBMap* newE ) {
            if ( newE ) self.e = std::move( *newE );
        } ), allow_raw_pointers() )
        
        .function( "getF", optional_override( [] ( PackMapping& self ) -> FaceBMap*
        {
            return &self.f;
        } ), allow_raw_pointers() )
        .function( "setF", optional_override( []( PackMapping& self, FaceBMap& newB ) {
            self.f = std::move( newB );
        } ), allow_raw_pointers() )
        .function( "setFWithPtr", optional_override( []( PackMapping& self, FaceBMap* newB ) {
            if ( newB ) self.f = std::move( *newB );
        } ), allow_raw_pointers() )
        
        .function( "getV", optional_override( [] ( PackMapping& self ) -> VertBMap*
        {
            return &self.v;
        } ), allow_raw_pointers() )
        .function( "setV", optional_override( []( PackMapping& self, VertBMap& newV ) {
            self.v = std::move( newV );
        } ), allow_raw_pointers() )
        .function( "setVWithPtr", optional_override( []( PackMapping& self, VertBMap* newV ) {
            if ( newV ) self.v = std::move( *newV );
        } ), allow_raw_pointers() );
    ///
}
