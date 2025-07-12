#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRAABBTreePoints.h>
#include <MRMesh/MRPlane3.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRBuffer.h>
#include <MRMesh/MRPointCloud.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( PointCloudModule )
{
    class_<PointCloud>( "PointCloud" )
        .constructor<>()

        .property( "points", &PointCloud::points )
        .property( "normals", &PointCloud::normals )
        .property( "validPoints", &PointCloud::validPoints )

        .function( "calcNumValidPoints", &PointCloud::calcNumValidPoints )
        .function( "hasNormals", &PointCloud::hasNormals )
        .function( "getVertIds", &PointCloud::getVertIds, allow_raw_pointers() )
        // .function( "getAABBTree", &PointCloud::getAABBTree )
        .function( "getAABBTreeNotCreate", &PointCloud::getAABBTreeNotCreate, allow_raw_pointers() )
        .function( "getBoundingBox", &PointCloud::getBoundingBox )
        .function( "computeBoundingBox", select_overload<Box3f( const AffineXf3f* ) const>( &PointCloud::computeBoundingBox ), allow_raw_pointers() )
        .function( "findCenterFromPoints", &PointCloud::findCenterFromPoints )
        .function( "findCenterFromBBox", &PointCloud::findCenterFromBBox )
        .function( "getLexicographicalOrder", &PointCloud::getLexicographicalOrder )
        .function( "addPartByMask", select_overload<void(const PointCloud&, const VertBitSet&, const CloudPartMapping&, const VertNormals*)>(&PointCloud::addPartByMask), allow_raw_pointers())
        .function( "addPoint", select_overload<VertId( const Vector3f& )>( &PointCloud::addPoint ) )
        .function( "addPointNormal", select_overload<VertId( const Vector3f&, const Vector3f& )>( &PointCloud::addPoint ) )
        .function( "mirror", &PointCloud::mirror )
        .function( "flipOrientation", &PointCloud::flipOrientation, allow_raw_pointers() )
        .function( "pack", select_overload<bool( VertMap* )>( &PointCloud::pack ), allow_raw_pointers() )
        // NOTE: Add `return_value_policy` to fix `call to implicitly-deleted copy constructor` error
        .function( "packReorder", select_overload<VertBMap( Reorder )>( &PointCloud::pack ), return_value_policy::reference() )
        .function( "invalidateCaches", &PointCloud::invalidateCaches )
        .function( "heapBytes", &PointCloud::heapBytes );
}
