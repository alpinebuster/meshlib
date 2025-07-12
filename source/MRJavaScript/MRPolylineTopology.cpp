#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRAABBTreePolyline.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRAffineXf2.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRMapEdge.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRPolyline.h>
#include <MRMesh/MRPolylineTopology.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( PolylineTopologyModule )
{
    class_<PolylineTopology>( "PolylineTopology" )
        .constructor<>()

        // FIXME
        // .function( "buildFromContours", &PolylineTopology::buildFromContours )

        .function( "buildOpenLines", &PolylineTopology::buildOpenLines )

        .function( "makeEdge", select_overload<EdgeId()>( &PolylineTopology::makeEdge ) )
        .function( "makeEdgeWithVertId", select_overload<EdgeId( VertId, VertId )>( &PolylineTopology::makeEdge ) )

        .function( "isLoneEdge", &PolylineTopology::isLoneEdge )
        .function( "lastNotLoneEdge", &PolylineTopology::lastNotLoneEdge )
        .function( "edgeSize", &PolylineTopology::edgeSize )
        .function( "undirectedEdgeSize", &PolylineTopology::undirectedEdgeSize )
        .function( "computeNotLoneUndirectedEdges", &PolylineTopology::computeNotLoneUndirectedEdges )
        .function( "edgeReserve", &PolylineTopology::edgeReserve )
        .function( "hasEdge", &PolylineTopology::hasEdge )

        .function( "deleteEdge", &PolylineTopology::deleteEdge )
        .function( "deleteEdges", &PolylineTopology::deleteEdges )

        .function( "heapBytes", &PolylineTopology::heapBytes )
        .function( "splice", &PolylineTopology::splice )
        .function( "next", &PolylineTopology::next )
        .function( "org", &PolylineTopology::org )
        .function( "dest", &PolylineTopology::dest )

        .function( "setOrg", &PolylineTopology::setOrg )
        .function( "edgePerVertex", &PolylineTopology::edgePerVertex )
        .function( "getOrgs", &PolylineTopology::getOrgs )
        .function( "edgeWithOrg", &PolylineTopology::edgeWithOrg )
        .function( "hasVert", &PolylineTopology::hasVert )
        .function( "getVertDegree", &PolylineTopology::getVertDegree )
        .function( "numValidVerts", &PolylineTopology::numValidVerts )
        .function( "lastValidVert", &PolylineTopology::lastValidVert )
        .function( "addVertId", &PolylineTopology::addVertId )

        .function( "vertResize", &PolylineTopology::vertResize )
        .function( "vertResizeWithReserve", &PolylineTopology::vertResizeWithReserve )
        .function( "vertReserve", &PolylineTopology::vertReserve )
        .function( "vertSize", &PolylineTopology::vertSize )
        .function( "vertCapacity", &PolylineTopology::vertCapacity )
        .function( "getValidVerts", &PolylineTopology::getValidVerts )
        .function( "getVertIds", &PolylineTopology::getVertIds, allow_raw_pointers() )

        .function( "findEdge", &PolylineTopology::findEdge )
        .function( "getPathVertices", &PolylineTopology::getPathVertices )
        .function( "splitEdge", &PolylineTopology::splitEdge )
        .function( "makePolyline", &PolylineTopology::makePolyline, allow_raw_pointers() )

        .function( "addPart", &PolylineTopology::addPart, allow_raw_pointers() )
        .function( "addPartByMask", &PolylineTopology::addPartByMask, allow_raw_pointers() )

        .function( "pack", &PolylineTopology::pack, allow_raw_pointers() )
    
		.function( "equals", optional_override( [] ( const PolylineTopology& self, const PolylineTopology& other )
		{
			return self == other;
        } ) )
		.function( "notEquals", optional_override( [] ( const PolylineTopology& self, const PolylineTopology& other )
		{
			return self != other;
        } ) )
        
        .function( "isConsistentlyOriented", &PolylineTopology::isConsistentlyOriented )
        .function( "flip", &PolylineTopology::flip )
        .function( "checkValidity", &PolylineTopology::checkValidity )
        .function( "computeValidsFromEdges", &PolylineTopology::computeValidsFromEdges )
        .function( "isClosed", &PolylineTopology::isClosed );

    
    class_<PolylineMaker>( "PolylineMaker" )
        .constructor<PolylineTopology&>()
        .function( "start", &PolylineMaker::start )
        .function( "proceed", &PolylineMaker::proceed )
        .function( "close", &PolylineMaker::close )
        .function( "finishOpen", &PolylineMaker::finishOpen );
}
