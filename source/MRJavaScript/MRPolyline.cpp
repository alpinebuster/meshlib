#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRAABBTreePolyline.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRAffineXf2.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRComputeBoundingBox.h>
#include <MRMesh/MREdgePaths.h>
#include <MRMesh/MRLineSegm.h>
#include <MRMesh/MRPlane3.h>
#include <MRMesh/MREdgePoint.h>
#include <MRMesh/MRTriPoint.h>
#include <MRMesh/MRPolylineTopology.h>
#include <MRMesh/MRPolyline.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( PolylineModule )
{
    class_<Polyline3>( "Polyline3" )
        .constructor<>()
        .constructor<const Contour<Vector3f>&>()
        .class_function( "fromContours", optional_override( [] ( const Contours<Vector3f>& u )
        {
            return Polyline3( u );
        } ) )

        .property( "topology", &Polyline3::topology )
        .property( "points", &Polyline3::points )

        .function( "addFromPointsAsClosed", select_overload<EdgeId ( const Vector3f*, size_t, bool )>( &Polyline3::addFromPoints ), allow_raw_pointers() )
        .function( "addFromPoints", select_overload<EdgeId ( const Vector3f*, size_t )>( &Polyline3::addFromPoints ), allow_raw_pointers() )

        .function( "addPart", &Polyline3::addPart, allow_raw_pointers() )
        .function( "addPartByMask", &Polyline3::addPartByMask, allow_raw_pointers() )
        .function( "pack", &Polyline3::pack, allow_raw_pointers() )

        .function( "orgPnt", &Polyline3::orgPnt)
        .function( "destPnt", &Polyline3::destPnt )

        .function( "edgePointFromEdgeId", select_overload<Vector3f ( EdgeId, float ) const>( &Polyline3::edgePoint ) )
        .function( "edgePoint", select_overload<Vector3f ( const EdgePoint& ) const>( &Polyline3::edgePoint ) )
        .function( "edgeCenter", &Polyline3::edgeCenter )
        .function( "edgeVector", &Polyline3::edgeVector )
        .function( "edgeSegment", &Polyline3::edgeSegment )

        .function( "toEdgePoint", select_overload<EdgePoint ( VertId ) const>( &Polyline3::toEdgePoint ) )
        .function( "toEdgePointWithEdgeId", select_overload<EdgePoint ( EdgeId, const Vector3f& ) const>( &Polyline3::toEdgePoint ) )

        .function( "edgeLength", &Polyline3::edgeLength )
        .function( "edgeLengthSq", &Polyline3::edgeLengthSq )
        .function( "loopDirArea", &Polyline3::loopDirArea )
        .function( "totalLength", &Polyline3::totalLength )

        // .function( "getAABBTree", &Polyline3::getAABBTree )
        // .function( "getAABBTreeNotCreate", &Polyline3::getAABBTreeNotCreate, allow_raw_pointers() )
        .function( "getBoundingBox", &Polyline3::getBoundingBox )
        .function( "computeBoundingBox", &Polyline3::computeBoundingBox, allow_raw_pointers() )
        .function( "findCenterFromPoints", &Polyline3::findCenterFromPoints )
        .function( "transform", &Polyline3::transform )
        .function( "invalidateCaches", &Polyline3::invalidateCaches )
    
        .function( "splitEdgeWithEdgeId", select_overload<EdgeId ( EdgeId, const Vector3f& )>( &Polyline3::splitEdge ) )
        .function( "splitEdge", select_overload<EdgeId ( EdgeId )>( &Polyline3::splitEdge ) )
    
        .function( "contours", &Polyline3::contours, allow_raw_pointers() )
        // FIXME
        // .function( "toPolyline", &Polyline3::toPolyline )
        
        .function( "addFromEdgePath", &Polyline3::addFromEdgePath )
        // .function( "addFromSurfacePath", &Polyline3::addFromSurfacePath )
        // .function( "addFromGeneralSurfacePath", &Polyline3::addFromGeneralSurfacePath )

        // FIXME
        // .function( "mirror", &Polyline3::mirror )
        .function( "heapBytes", &Polyline3::heapBytes );

    
    class_<Polyline2>( "Polyline2" )
        .constructor<>()
        .constructor<const Contour<Vector2f>&>()
        .class_function( "fromContours", optional_override( [] ( const Contours<Vector2f>& u )
        {
            return Polyline2( u );
        } ) )

        .property( "topology", &Polyline2::topology )
        .property( "points", &Polyline2::points )

        .function( "addFromPointsAsClosed", select_overload<EdgeId ( const Vector2f*, size_t, bool )>( &Polyline2::addFromPoints ), allow_raw_pointers() )
        .function( "addFromPoints", select_overload<EdgeId ( const Vector2f*, size_t )>( &Polyline2::addFromPoints ), allow_raw_pointers() )

        .function( "addPart", &Polyline2::addPart, allow_raw_pointers() )
        .function( "addPartByMask", &Polyline2::addPartByMask, allow_raw_pointers() )
        .function( "pack", &Polyline2::pack, allow_raw_pointers() )

        .function( "orgPnt", &Polyline2::orgPnt)
        .function( "destPnt", &Polyline2::destPnt )

        .function( "edgePointFromEdgeId", select_overload<Vector2f ( EdgeId, float ) const>( &Polyline2::edgePoint ) )
        .function( "edgePoint", select_overload<Vector2f ( const EdgePoint& ) const>( &Polyline2::edgePoint ) )
        .function( "edgeCenter", &Polyline2::edgeCenter )
        .function( "edgeVector", &Polyline2::edgeVector )
        .function( "edgeSegment", &Polyline2::edgeSegment )

        .function( "toEdgePoint", select_overload<EdgePoint ( VertId ) const>( &Polyline2::toEdgePoint ) )
        .function( "toEdgePointWithEdgeId", select_overload<EdgePoint ( EdgeId, const Vector2f& ) const>( &Polyline2::toEdgePoint ) )

        .function( "edgeLength", &Polyline2::edgeLength )
        .function( "edgeLengthSq", &Polyline2::edgeLengthSq )
        .function( "loopDirArea", &Polyline2::loopDirArea )
        .function( "totalLength", &Polyline2::totalLength )

        // .function( "getAABBTree", &Polyline2::getAABBTree )
        // .function( "getAABBTreeNotCreate", &Polyline2::getAABBTreeNotCreate, allow_raw_pointers() )
        .function( "getBoundingBox", &Polyline2::getBoundingBox )
        .function( "computeBoundingBox", &Polyline2::computeBoundingBox, allow_raw_pointers() )
        .function( "findCenterFromPoints", &Polyline2::findCenterFromPoints )
        .function( "transform", &Polyline2::transform )
        .function( "invalidateCaches", &Polyline2::invalidateCaches )
    
        .function( "splitEdgeWithEdgeId", select_overload<EdgeId ( EdgeId, const Vector2f& )>( &Polyline2::splitEdge ) )
        .function( "splitEdge", select_overload<EdgeId ( EdgeId )>( &Polyline2::splitEdge ) )
    
        .function( "contours", &Polyline2::contours, allow_raw_pointers() )
        // FIXME
        // .function( "toPolyline", &Polyline2::toPolyline )
        
        .function( "addFromEdgePath", &Polyline2::addFromEdgePath )
        // .function( "addFromSurfacePath", &Polyline2::addFromSurfacePath )
        // .function( "addFromGeneralSurfacePath", &Polyline2::addFromGeneralSurfacePath )

        // FIXME
        // .function( "mirror", &Polyline2::mirror )
        .function( "heapBytes", &Polyline2::heapBytes );
}
