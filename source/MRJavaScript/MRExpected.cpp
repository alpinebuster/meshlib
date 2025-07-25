#include <optional>
#include <string>

#include <MRPch/MRWasm.h>

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
#include <MRMesh/MRFaceFace.h>
#include <MRMesh/MRMeshBoolean.h>
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

    MRJS::bindExpected<std::string>( "ExpectedStdString" );
    MRJS::bindExpected<bool>( "ExpectedBool" );
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
    MRJS::bindExpected<FaceFace>( "ExpectedFaceFace" );
    MRJS::bindExpected<BooleanResultPoints>( "ExpectedBooleanResultPoints" );
    ///


    ///
    MRJS::bindExpected<std::vector<FaceFace>>( "ExpectedVectorFaceFace" );
    ///

	
	///
    MRJS::bindExpected<std::pair<VertId, VertId>>( "ExpectedVertIdPair" );
    MRJS::bindExpected<std::pair<FaceId, FaceId>>( "ExpectedFaceIdPair" );
    MRJS::bindExpected<std::pair<EdgeId, EdgeId>>( "ExpectedEdgeIdPair" );
    MRJS::bindExpected<std::pair<UndirectedEdgeId, UndirectedEdgeId>>( "ExpectedUndirectedIdPair" );
    MRJS::bindExpected<std::pair<UndirectedEdgeId, EdgeId>>( "ExpectedUndirectedE2EIdPair" );

    MRJS::bindExpected<std::vector<std::pair<VertId, VertId>>>( "ExpectedVertHashMapEntries" );
    MRJS::bindExpected<std::vector<std::pair<FaceId, FaceId>>>( "ExpectedFaceHashMapEntries" );
    MRJS::bindExpected<std::vector<std::pair<EdgeId, EdgeId>>>( "ExpectedEdgeHashMapEntries" );
    MRJS::bindExpected<std::vector<std::pair<UndirectedEdgeId, UndirectedEdgeId>>>( "ExpectedUndirectedEdgeHashMapEntries" );
    MRJS::bindExpected<std::vector<std::pair<UndirectedEdgeId, EdgeId>>>( "ExpectedWholeEdgeHashMapEntries" );
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
