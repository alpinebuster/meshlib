#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRSegmPoint.h>
#include <MRMesh/MRPolylineTopology.h>
#include <MRMesh/MREdgePoint.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( EdgePointModule )
{
    class_<EdgePoint>( "EdgePoint" )
        .constructor<>()
        .constructor<EdgeId, float>()
        .class_function( "createFromMeshTopology", optional_override( [] ( const MeshTopology & topology, VertId v )
        {
            return EdgePoint( topology, v );
        } ) )
        .class_function( "createFromPolylineTopology", optional_override( [] ( const PolylineTopology & topology, VertId v )
        {
            return EdgePoint( topology, v );
        } ) )

        .property( "e", &EdgePoint::e )
        .property( "a", &EdgePoint::a )
        
        .function( "inVertex", select_overload<bool() const>( &EdgePoint::inVertex ) )
        .function( "inVertexFromMeshTopology", select_overload<VertId (const MeshTopology &) const>( &EdgePoint::inVertex ) )
        .function( "inVertexFromPolylineTopology", select_overload<VertId( const PolylineTopology& ) const>( &EdgePoint::inVertex ) )
        
        .function( "getClosestVertex", select_overload<VertId (const MeshTopology &) const>( &EdgePoint::getClosestVertex ) )
        .function( "getClosestVertexFromPolylineTopology", select_overload<VertId( const PolylineTopology& ) const>( &EdgePoint::getClosestVertex ) )
        
        .function( "moveToClosestVertex", &EdgePoint::moveToClosestVertex )
        .function( "isBd", &EdgePoint::isBd, allow_raw_pointers())
        .function( "valid", &EdgePoint::valid )
        .function( "opbool", select_overload<bool() const>( &EdgePoint::operator bool ) )
        .function( "sym", &EdgePoint::sym )
        .function( "equals", optional_override( [] ( const EdgePoint& self, const EdgePoint& other )
        {
            return self == other;
        } ) );


    class_<EdgePointPair>( "EdgePointPair" )
        .constructor<>()
        .constructor<EdgePoint, EdgePoint>()

        .property( "a", &EdgePointPair::a )
        .property( "b", &EdgePointPair::b )

        .function( "equals", optional_override( [] ( const EdgePointPair& self, const EdgePointPair& other )
        {
            return self == other;
        } ) );


    class_<EdgeSegment>( "EdgeSegment" )
        .constructor<>()
        .constructor<EdgeId, float, float>()

        .property( "e", &EdgeSegment::e )
        .property( "a", &EdgeSegment::a )
        .property( "b", &EdgeSegment::b )

        .function( "edgePointA", &EdgeSegment::edgePointA )
        .function( "edgePointB", &EdgeSegment::edgePointB )
        .function( "valid", &EdgeSegment::valid )
    
        .function( "equals", optional_override( [] ( const EdgeSegment& self, const EdgeSegment& other )
        {
            return self == other;
        } ) )
        .function( "sym", &EdgeSegment::sym );


	function( "fromSameTriangle", select_overload<bool ( const MeshTopology&, EdgePoint&, EdgePoint& )>( &fromSameTriangle ));
}
