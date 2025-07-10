#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRAABBTreePoints.h>
#include <MRMesh/MRPointCloud.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( AABBTreePointsModule )
{
    register_vector<AABBTreePoints::Point>( "VectorAABBTreePointsPoint" );
    register_vector<AABBTreePoints::Node>( "VectorAABBTreePointsNode" );

    value_object<AABBTreePoints::Point>( "AABBTreePointsPoint" )
        .field( "coord", &AABBTreePoints::Point::coord )
        .field( "id", &AABBTreePoints::Point::id );

    class_<AABBTreePoints::Node>( "AABBTreePointsNode" )
        .constructor<>()
        .property( "box", &AABBTreePoints::Node::box )
        .property( "l", &AABBTreePoints::Node::l )
        .property( "r", &AABBTreePoints::Node::r );

    class_<AABBTreePoints>( "AABBTreePoints" )
        // FIXME: BindingError: Cannot register multiple constructors with identical number of parameters (1)
        // .constructor<const PointCloud&>()
        .constructor<const Mesh&>()
        .constructor<const VertCoords&, const VertBitSet*>( allow_raw_pointers() )

        .class_property( "MaxNumPointsInLeaf", &AABBTreePoints::MaxNumPointsInLeaf )
    
        .function( "getBoundingBox", &AABBTreePoints::getBoundingBox )
        // .function( "nodes", select_overload<const AABBTreePoints::NodeVec& () const>( &AABBTreePoints::nodes ) )
        .function( "orderedPoints", &AABBTreePoints::orderedPoints )
        // .function( "getLeafOrder", &AABBTreePoints::getLeafOrder )
        .function( "refit", &AABBTreePoints::refit );
}
