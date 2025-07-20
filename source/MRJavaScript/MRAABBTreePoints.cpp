#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRPointCloud.h>
#include <MRMesh/MRBuffer.h>
#include <MRMesh/MRAABBTreePoints.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( AABBTreePointsModule )
{
    value_object<AABBTreePoints::Point>( "AABBTreePointsPoint" )
        .field( "coord", &AABBTreePoints::Point::coord )
        .field( "id", &AABBTreePoints::Point::id );

    class_<AABBTreePoints::Node>( "AABBTreePointsNode" )
        .constructor<>()
        .property( "box", &AABBTreePoints::Node::box )
        .property( "l", &AABBTreePoints::Node::l )
        .property( "r", &AABBTreePoints::Node::r );

    class_<AABBTreePoints>( "AABBTreePoints" )
        .smart_ptr<std::shared_ptr<AABBTreePoints>>( "AABBTreePointsSharedPtr" )

        .constructor<const Mesh&>()
        .constructor<const VertCoords&, const VertBitSet*>( allow_raw_pointers() )

        .class_function( "createFromPointCloudUniquePtr", 
            optional_override( [] ( const PointCloud& pointCloud )
            {
                return std::make_unique<AABBTreePoints>( pointCloud );
            } ), 
            allow_raw_pointers()
        )
        .class_function( "createFromPointCloudSharedPtr", 
            optional_override( [] ( const PointCloud& pointCloud )
            {
                return std::make_shared<AABBTreePoints>( pointCloud );
            } ), 
            allow_raw_pointers()
        )

        .class_function("createFromPointsUniquePtr", 
            optional_override([](const VertCoords & points, const VertBitSet & validPoints) {
                return std::make_unique<AABBTreePoints>(points, validPoints);
            }), 
            allow_raw_pointers()
        )
        .class_function( "createFromPointsSharedPtr", 
            optional_override( [] ( const VertCoords& points, const VertBitSet& validPoints )
            {
                return std::make_shared<AABBTreePoints>(points, validPoints);
            }), 
            allow_raw_pointers()
        )

        .class_property( "MaxNumPointsInLeaf", &AABBTreePoints::MaxNumPointsInLeaf )
    
        .function( "nodes", select_overload<const AABBTreePoints::NodeVec& () const>( &AABBTreePoints::nodes ) )
        .function( "getBoundingBox", &AABBTreePoints::getBoundingBox )
        .function( "orderedPoints", &AABBTreePoints::orderedPoints )
        .function( "getLeafOrder", &AABBTreePoints::getLeafOrder )
        .function( "getLeafOrderAndReset", &AABBTreePoints::getLeafOrderAndReset )
        .function( "heapBytes", &AABBTreePoints::heapBytes )
        .function( "refit", &AABBTreePoints::refit );
}
