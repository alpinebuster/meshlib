#include <optional>
#include <string>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRMesh.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRPointCloud.h>
#include <MRMesh/MRMeshOrPoints.h>
#include <MRMesh/MREdgeLengthMesh.h>
#include <MRMesh/MRAABBTree.h>
#include <MRMesh/MRAABBTreePoints.h>
#include <MRMesh/MRAABBTreeObjects.h>
#include <MRMesh/MRCloudPartMapping.h>
#include <MRMesh/MRPartMapping.h>
#include <MRMesh/MRBuffer.h>
#include <MRMesh/MRGridSampling.h>
#include <MRMesh/MRGridSettings.h>
#include <MRMesh/MRMeshTexture.h>
#include <MRMesh/MROneMeshContours.h>
#include <MRMesh/MRIntersectionContour.h>
#include <MRMesh/MRTriMesh.h>
#include <MRPch/MRExpected.h>
#include <MRMesh/MRExpected.h>

#include "MRExpected.h"

using namespace emscripten;
using namespace MR;


// ------------------------------------------------------------------------
// Bind the Embind interface for `Expected*`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( ExpectedModule )
{
    ///
    class_<Expected<void>>( "ExpectedVoid" )
        .function( "hasValue", &Expected<void>::has_value )
        .function( "opbool", optional_override( [] ( const Expected<void>& self ) -> bool
        {
            return static_cast<bool>( self );
        } ) )
        .function( "hasError", optional_override( [] ( const Expected<void>& self )
        {
            return !self.has_value();
        } ) )
        .function( "error", optional_override( [] ( const Expected<void>& self ) -> const std::string&
        {
            return self.error();
        } ) );
    ///


    ///
    MRJS::bindExpected<MeshTopology>( "ExpectedMeshTopology" );
    MRJS::bindExpected<Mesh>( "ExpectedMesh" );
    MRJS::bindExpected<EdgeLengthMesh>( "ExpectedEdgeLengthMesh" );
    MRJS::bindExpected<MeshOrPoints>( "ExpectedMeshOrPoints" );
    MRJS::bindExpected<PointCloud>( "ExpectedPointCloud" );
    MRJS::bindExpected<AABBTree>( "ExpectedAABBTree" );
    MRJS::bindExpected<AABBTreePoints>( "ExpectedAABBTreePoints" );
    MRJS::bindExpected<AABBTreeObjects>( "ExpectedAABBTreeObjects" );
    MRJS::bindExpected<CloudPartMapping>( "ExpectedCloudPartMapping" );
    MRJS::bindExpected<PartMapping>( "ExpectedPartMapping" );
    MRJS::bindExpected<MeshOrPointsXf>( "ExpectedMeshOrPointsXf" );
    MRJS::bindExpected<MeshTexture>( "ExpectedMeshTexture" );
    MRJS::bindExpected<GridSettings>( "ExpectedGridSettings" );
    MRJS::bindExpected<TriMesh>( "ExpectedTriMesh" );
    ///


    ///
    MRJS::bindExpected<FaceBitSet>( "ExpectedFaceBitSet" );
    MRJS::bindExpected<VertBitSet>( "ExpectedVertBitSet" );
    MRJS::bindExpected<EdgeBitSet>( "ExpectedEdgeBitSet" );
    MRJS::bindExpected<UndirectedEdgeBitSet>( "ExpectedUndirectedEdgeBitSet" );
    MRJS::bindExpected<PixelBitSet>( "ExpectedPixelBitSet" );
    MRJS::bindExpected<VoxelBitSet>( "ExpectedVoxelBitSet" );
    MRJS::bindExpected<RegionBitSet>( "ExpectedRegionBitSet" );
    MRJS::bindExpected<NodeBitSet>( "ExpectedNodeBitSet" );
    MRJS::bindExpected<ObjBitSet>( "ExpectedObjBitSet" );
    MRJS::bindExpected<TextureBitSet>( "ExpectedTextureBitSet" );
    MRJS::bindExpected<GraphVertBitSet>( "ExpectedGraphVertBitSet" );
    MRJS::bindExpected<GraphEdgeBitSet>( "ExpectedGraphEdgeBitSet" );
    ///


    ///
    MRJS::bindExpected<PackMapping>( "ExpectedPackMapping" );
    ///


    ///
    // NOTE: `EdgeLoop` is the same as `EdgePath`
    // MRJS::bindExpected<EdgeLoop>( "ExpectedEdgeLoop" );
    // 
    MRJS::bindExpected<EdgePath>( "ExpectedEdgePath" );
    MRJS::bindExpected<EdgeLoops>( "ExpectedEdgeLoops" );
    MRJS::bindExpected<OneMeshContour>( "ExpectedOneMeshContour" );
    MRJS::bindExpected<OneMeshContours>( "ExpectedOneMeshContours" );
    MRJS::bindExpected<SurfacePath>( "ExpectedSurfacePath" );
    ///
}
