#include <optional>
#include <string>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRMesh.h>
#include <MRMesh/MRId.h>
#include <MRPch/MRExpected.h>
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
    // MRJS::bindExpected<MeshTexture>( "ExpectedMeshTexture" );
    // MRJS::bindExpected<GridSettings>( "ExpectedGridSettings" );
    // MRJS::bindExpected<TriMesh>( "ExpectedTriMesh" );
    ///


    ///
    // NOTE: `EdgeLoop` is the same as `EdgePath`
    // MRJS::bindExpected<EdgeLoop>( "ExpectedEdgeLoop" );
    // 
    MRJS::bindExpected<EdgePath>( "ExpectedEdgePath" );
    MRJS::bindExpected<EdgeLoops>( "ExpectedEdgeLoops" );
    ///
}
