#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRBuffer.h>
#include <MRMesh/MRGridSettings.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( GridSettingsModule )
{
    enum_<GridSettings::EdgeType>( "EdgeType" )
        .value( "Horizontal", GridSettings::EdgeType::Horizontal )
        .value( "Vertical", GridSettings::EdgeType::Vertical )
        .value( "DiagonalA", GridSettings::EdgeType::DiagonalA )
        .value( "DiagonalB", GridSettings::EdgeType::DiagonalB );

    enum_<GridSettings::TriType>( "TriType" )
        .value( "Lower", GridSettings::TriType::Lower )
        .value( "Upper", GridSettings::TriType::Upper );


    class_<GridSettings>( "GridSettings" )
        .constructor<>()
        .property( "dim", &GridSettings::dim )

        ///
        .function( "getVertIds", optional_override( [] ( GridSettings& self ) -> BMap<VertId, size_t>*
            {
                return &self.vertIds;
            } ), allow_raw_pointers() )
        .function( "setVertIds", optional_override( []( GridSettings& self, BMap<VertId, size_t>& newVertIds ) {
            self.vertIds = std::move( newVertIds );
        } ), allow_raw_pointers() )
        .function( "setVertIdsWithPtr", optional_override( []( GridSettings& self, BMap<VertId, size_t>* newVertIds ) {
            if ( newVertIds ) self.vertIds = std::move( *newVertIds );
        } ), allow_raw_pointers() )
        ///

        ///
        .function( "getUEdgeIds", optional_override( [] ( GridSettings& self ) -> BMap<UndirectedEdgeId, size_t>*
            {
                return &self.uedgeIds;
            } ), allow_raw_pointers() )
        .function( "setUEdgeIds", optional_override( []( GridSettings& self, BMap<UndirectedEdgeId, size_t>& newUEdgeIds ) {
            self.uedgeIds = std::move( newUEdgeIds );
        } ), allow_raw_pointers() )
        .function( "setUEdgeIdsWithPtr", optional_override( []( GridSettings& self, BMap<UndirectedEdgeId, size_t>* newUEdgeIds ) {
            if ( newUEdgeIds ) self.uedgeIds = std::move( *newUEdgeIds );
        } ), allow_raw_pointers() )
        ///

        ///
        .function( "getFaceIds", optional_override( [] ( GridSettings& self ) -> BMap<FaceId, size_t>*
            {
                return &self.faceIds;
            } ), allow_raw_pointers() )
        .function( "setFaceIds", optional_override( []( GridSettings& self, BMap<FaceId, size_t>& newFaceIds ) {
            self.faceIds = std::move( newFaceIds );
        } ), allow_raw_pointers() )
        .function( "setFaceIdsWithPtr", optional_override( []( GridSettings& self, BMap<FaceId, size_t>* newFaceIds ) {
            if ( newFaceIds ) self.faceIds = std::move( *newFaceIds );
        } ), allow_raw_pointers() );
        ///
}
