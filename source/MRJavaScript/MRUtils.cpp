#include <optional>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRVector4.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRBuffer.h>
#include <MRMesh/MRMeshOrPoints.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MREdgePaths.h>
#include <MRMesh/MRFillContour.h>
#include <MRMesh/MREdgeMetric.h>
#include <MRMesh/MRPointCloud.h>
#include <MRMesh/MRAABBTreePoints.h>
#include <MRMesh/MREdgePoint.h>
#include <MRMesh/MRDipole.h>
#include <MRMesh/MRGridSampling.h>
#include <MRMesh/MRMeshProject.h>
#include <MRMesh/MRMeshBuilder.h>
#include <MRMesh/MRProgressCallback.h>
#include <MRMesh/MRMeshBuilderTypes.h>
#include <MRMesh/MRMeshBuilder.h>
#include <MRMesh/MRMeshExtrude.h>
#include <MRMesh/MRRegionBoundary.h>
#include <MRMesh/MROneMeshContours.h>
#include <MRMesh/MRIntersectionContour.h>
#include <MRMesh/MRMeshTriPoint.h>
#include <MRMesh/MRMeshFillHole.h>
#include <MRMesh/MRMeshCollidePrecise.h>

#include <MRVoxels/MRTeethMaskToDirectionVolume.h>

#include "MRUtils.h"

using namespace emscripten;
using namespace MR;


namespace MRJS
{

Vector3f arrayToVector3f( const val& arr )
{
	return Vector3f( arr[0].as<float>(), arr[1].as<float>(), arr[2].as<float>() );
}

val vector3fToArray( const Vector3f& v )
{
	val arr = val::array();
	arr.set( 0, v.x );
	arr.set( 1, v.y );
	arr.set( 2, v.z );
	return arr;
}

val box3fToObject( const Box<Vector3<float>>& box )
{
	val obj = val::object();
	obj.set( "min", vector3fToArray( box.min ) );
	obj.set( "max", vector3fToArray( box.max ) );
	return obj;
}

template<typename T>
val expectedToJs( const Expected<T>& expected )
{
	if ( expected.has_value() )
	{
		val obj = val::object();
		obj.set( "success", true );
		obj.set( "value", expected.value() );
		return obj;
	}
	else
	{
		val obj = val::object();
		obj.set( "success", false );
		obj.set( "error", expected.error() );
		return obj;
	}
}

val vector3fToFloat32Array( const std::vector<Vector3f>& vec )
{
	return val( typed_memory_view( vec.size() * 3, reinterpret_cast< const float* >( vec.data() ) ) );
}

std::vector<Vector3f> parseJSCoordinates( const std::vector<float>& coordinates )
{
    std::vector<Vector3f> points;

    // Validate that we have complete sets of 3D coordinates
    if ( coordinates.size() % 3 != 0 )
    {
        throw std::invalid_argument( "Coordinate array length must be divisible by 3" );
    }

    // Convert flat array to Vector3f objects
    points.reserve( coordinates.size() / 3 );
    for ( size_t i = 0; i < coordinates.size(); i += 3 )
    {
        points.emplace_back( coordinates[i], coordinates[i + 1], coordinates[i + 2] );
    }

    return points;
}

/**
 *@brief CutMesh with contour and extracting cutted parts
 * 
 *  using EdgePath = std::vector<EdgeId>;
 *  using EdgeLoop = std::vector<EdgeId>;
 *  using EdgeLoops = std::vector<EdgeLoop>;
 *
 * @param mesh 
 * @param cut 
 * @return std::pair<Mesh, Mesh> 
 */
std::pair<Mesh, Mesh> returnParts( const Mesh& mesh, const std::vector<EdgePath>& cut )
{
	// NOTE: This works!
	// auto innerBitSet = fillContourLeft( mesh.topology, cut );
	// Mesh innerMesh = mesh.cloneRegion( innerBitSet );

	Mesh innerMesh;
    auto innerBitSet = fillContourLeft( mesh.topology, cut );
    innerMesh.addMeshPart( {mesh, &innerBitSet} );

    Mesh outerMesh;
    auto cutReverse = cut;
    MR::reverse( cutReverse );
    auto outerBitSet = fillContourLeft( mesh.topology, cutReverse  );
	outerMesh.addMeshPart( {mesh, &outerBitSet} );
	
	return { innerMesh, outerMesh };
}

}

// ------------------------------------------------------------------------
// Bindings for utilities
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( UtilsModule )
{
}


// ------------------------------------------------------------------------
// Bind the Embind interface for `std::vector<*>`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( VectorTypedModule )
{
	///
	register_vector<int>( "StdVectori" );
	register_vector<float>( "StdVectorf" );
	register_vector<double>( "StdVectord" );
	register_vector<long long>( "StdVectorll" );
	register_vector<uint64_t>( "StdVectorUi64" );
	///


	///
	register_vector<MeshBuilder::MeshPiece>( "VectorMeshPiece" );
	register_vector<EdgePoint>( "SurfacePath" );

	register_vector<AABBTreePoints::Point>( "VectorAABBTreePointsPoint" );
    register_vector<AABBTreePoints::Node>( "VectorAABBTreePointsNode" );

    register_vector<ModelPointsData>( "VectorModelPointsData" );
    register_vector<ObjVertId>( "VectorObjVertId" );

    register_vector<MeshProjectionResult>( "VectorMeshProjectionResult" );
	register_vector<MeshBuilder::VertDuplication>( "VectorVertDuplication" );

    register_vector<EdgeTri>( "VectorEdgeTri" );
	// ContinuousContour is `std::vector<VarEdgeTri>`
    register_vector<VarEdgeTri>( "ContinuousContour" );
    // `ContinuousContours` is `std::vector<ContinuousContour>`
	register_vector<ContinuousContour>( "ContinuousContours" );
    register_vector<OneMeshContour>( "OneMeshContours" );
    register_vector<OneMeshIntersection>( "VectorOneMeshIntersection" );
	register_vector<MeshTriPoint>( "VectorMeshTriPoint" );
	
	register_vector<FillHoleItem>( "VectorFillHoleItem" );
	register_vector<HoleFillPlan>( "VectorHoleFillPlan" );
	///


	///
	register_vector<std::vector<MeshBuilder::MeshPiece>>( "VectorVectorMeshPiece" );
	register_vector<std::vector<EdgePoint>>( "SurfacePaths" );

	register_vector<std::vector<AABBTreePoints::Point>>( "VectorVectorAABBTreePointsPoint" );
    register_vector<std::vector<AABBTreePoints::Node>>( "VectorVectorAABBTreePointsNode" );

    register_vector<std::vector<ModelPointsData>>( "VectorVectorModelPointsData" );
    register_vector<std::vector<ObjVertId>>( "VectorVectorObjVertId" );

    register_vector<std::vector<MeshProjectionResult>>( "VectorVectorMeshProjectionResult" );
	register_vector<std::vector<MeshBuilder::VertDuplication>>( "VectorVectorVertDuplication" );

    register_vector<std::vector<EdgeTri>>( "VectorVectorEdgeTri" );
    // NOTE: `std::vector<std::vector<VarEdgeTri>>` is `std::vector<ContinuousContour>`;
	register_vector<std::vector<ContinuousContour>>( "VectorContinuousContours" );
    register_vector<std::vector<OneMeshContour>>( "VectorOneMeshContours" );
    register_vector<std::vector<OneMeshIntersection>>( "VectorVectorOneMeshIntersection" );
    register_vector<std::vector<MeshTriPoint>>( "VectorVectorMeshTriPoint" );
	///


	///
	register_vector<std::vector<std::vector<EdgePoint>>>( "VectorSurfacePaths" );
	///


	///
    register_vector<std::array<Vector2i, 2>>( "VectorArray2Vector2i" );
    register_vector<std::array<Vector2f, 2>>( "VectorArray2Vector2f" );
	register_vector<std::array<Vector2d, 2>>( "VectorArray2Vector2d" );

	register_vector<std::array<Vector2i, 3>>( "VectorArray3Vector2i" );
    register_vector<std::array<Vector2f, 3>>( "VectorArray3Vector2f" );
	register_vector<std::array<Vector2d, 3>>( "VectorArray3Vector2d" );

	
	register_vector<std::array<Vector3i, 2>>( "VectorArray2Triangle3i" );
    register_vector<std::array<Vector3f, 2>>( "VectorArray2Triangle3f" );
	register_vector<std::array<Vector3d, 2>>( "VectorArray2Triangle3d" );

	register_vector<std::array<Vector3i, 3>>( "VectorArray3Triangle3i" );
    register_vector<std::array<Vector3f, 3>>( "VectorArray3Triangle3f" );
    register_vector<std::array<Vector3d, 3>>( "VectorArray3Triangle3d" );
	///

	///
	// Register vector structures of `std::vector<*Id()>`
	// 
	// NOTE:
	//   `EdgePath` -> `std::vector<EdgeId>`
	//   `EdgeLoop` -> `std::vector<EdgeId>`
	// 
	// register_vector<std::vector<EdgeId>>( "VectorVectorEdgeId" );
	// 
    register_vector<std::vector<UndirectedEdgeId>>( "VectorVectorUndirectedEdgeId" );
    register_vector<std::vector<FaceId>>( "VectorVectorFaceId" );
    register_vector<std::vector<VertId>>( "VectorVectorVertId" );
    register_vector<std::vector<PixelId>>( "VectorVectorPixelId" );
    register_vector<std::vector<VoxelId>>( "VectorVectorVoxelId" );
    register_vector<std::vector<RegionId>>( "VectorVectorRegionId" );
    register_vector<std::vector<NodeId>>( "VectorVectorNodeId" );
    register_vector<std::vector<ObjId>>( "VectorVectorObjId" );
    register_vector<std::vector<TextureId>>( "VectorVectorTextureId" );
    register_vector<std::vector<GraphVertId>>( "VectorVectorGraphVertId" );
    register_vector<std::vector<GraphEdgeId>>( "VectorVectorGraphEdgeId" );
	///


    ///
    register_vector<ThreeVertIds>( "VectorThreeVertIds" );

    // Register vector structures of `*Id()`
    register_vector<EdgeId>( "VectorEdgeId" );
    register_vector<UndirectedEdgeId>( "VectorUndirectedEdgeId" );
    register_vector<FaceId>( "VectorFaceId" );
    register_vector<VertId>( "VectorVertId" );
    register_vector<PixelId>( "VectorPixelId" );
    register_vector<VoxelId>( "VectorVoxelId" );
    register_vector<RegionId>( "VectorRegionId" );
    register_vector<NodeId>( "VectorNodeId" );
    register_vector<ObjId>( "VectorObjId" );
    register_vector<TextureId>( "VectorTextureId" );
    register_vector<GraphVertId>( "VectorGraphVertId" );
    register_vector<GraphEdgeId>( "VectorGraphEdgeId" );

    // NOTE: `EdgeLoop` equals `EdgePath` 
    // register_vector<EdgeLoop>( "VectorEdgeLoop" );
    register_vector<EdgePath>( "VectorEdgePath" );
    // NOTE: `EdgeLoops` equals `std::vector<EdgePath>`
    // register_vector<EdgeLoops>( "VectorEdgeLoops" );
    register_vector<std::vector<EdgePath>>( "VectorVectorEdgePath" );
	///

	
	///
    register_vector<std::pair<EdgeId, EdgeId>>( "EdgeHashMapEntries" );
    register_vector<std::pair<UndirectedEdgeId, UndirectedEdgeId>>( "UndirectedEdgeHashMapEntries" );
    register_vector<std::pair<UndirectedEdgeId, EdgeId>>( "WholeEdgeHashMapEntries" );
    register_vector<std::pair<FaceId, FaceId>>( "FaceHashMapEntries" );
    register_vector<std::pair<VertId, VertId>>( "VertHashMapEntries" );
	///


	///
	register_vector<Vector<MeshBuilder::VertSpan, FaceId>>( "VectorVertSpanFaceId" );
	///


	///
    register_vector<Vector<int, size_t>>( "VectorVectori" );
    register_vector<Vector<float, size_t>>( "VectorVectord" );
	register_vector<Vector<double, size_t>>( "VectorVectorf" );
	///


	///
	register_vector<Vector2f>( "VectorVector2f" );
	register_vector<std::vector<Vector2f>>( "VectorVectorVector2f" );
	
	register_vector<Vector2ll>( "VectorVector2ll" );
	register_vector<std::vector<Vector2ll>>( "VectorVectorVector2ll" );
	
	register_vector<Vector2b>( "VectorVector2b" );
	register_vector<std::vector<Vector2b>>( "VectorVectorVector2b" );
	
	register_vector<Vector2i>( "VectorVector2i" );
	register_vector<std::vector<Vector2i>>( "VectorVectorVector2i" );

	register_vector<Vector2d>( "VectorVector2d" );
	register_vector<std::vector<Vector2d>>( "VectorVectorVector2d" );
	///


	///
	register_vector<Vector3f>( "VectorVector3f" );
	register_vector<std::vector<Vector3f>>( "VectorVectorVector3f" );

	register_vector<Vector3b>( "VectorVector3b" );
	register_vector<std::vector<Vector3b>>( "VectorVectorVector3b" );

	register_vector<Vector3i>( "VectorVector3i" );
	register_vector<std::vector<Vector3i>>( "VectorVectorVector3i" );

	register_vector<Vector3ll>( "VectorVector3ll" );
	register_vector<std::vector<Vector3ll>>( "VectorVectorVector3ll" );

	register_vector<Vector3d>( "VectorVector3d" );
	register_vector<std::vector<Vector3d>>( "VectorVectorVector3d" );
	///


	///
    register_vector<Vector4f>( "VectorVector4f" );
	register_vector<std::vector<Vector4f>>( "VectorVectorVector4f" );

	register_vector<Vector4b>( "VectorVector4b" );
	register_vector<std::vector<Vector4b>>( "VectorVectorVector4b" );
	
	register_vector<Vector4i>( "VectorVector4i" );
	register_vector<std::vector<Vector4i>>( "VectorVectorVector4i" );
	
	register_vector<Vector4ll>( "VectorVector4ll" );
	register_vector<std::vector<Vector4ll>>( "VectorVectorVector4ll" );
	
	register_vector<Vector4d>( "VectorVector4d" );
	register_vector<std::vector<Vector4d>>( "VectorVectorVector4d" );
	///
}


// ------------------------------------------------------------------------
// Bind the Embind interface for `Array*`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( ArrayTypedModule )
{
	///
	MRJS::bindStdArray<Vector2b, 2>( "Array2Vector2b" );
	MRJS::bindStdArray<Vector2i, 2>( "Array2Vector2i" );
	MRJS::bindStdArray<Vector2ll, 2>( "Array2Vector2ll" );
	MRJS::bindStdArray<Vector2f, 2>( "Array2Vector2f" );
	MRJS::bindStdArray<Vector2d, 2>( "Array2Vector2d" );

	MRJS::bindStdArray<Vector2b, 3>( "Array3Vector2b" );
	MRJS::bindStdArray<Vector2i, 3>( "Array3Vector2i" );
	MRJS::bindStdArray<Vector2ll, 3>( "Array3Vector2ll" );
	MRJS::bindStdArray<Vector2f, 3>( "Array3Vector2f" );
	MRJS::bindStdArray<Vector2d, 3>( "Array3Vector2d" );


	MRJS::bindStdArray<Vector3b, 2>( "Array2Triangle3b" );
	MRJS::bindStdArray<Vector3i, 2>( "Array2Triangle3i" );
	MRJS::bindStdArray<Vector3ll, 2>( "Array2Triangle3ll" );
	MRJS::bindStdArray<Vector3f, 2>( "Array2Triangle3f" );
	MRJS::bindStdArray<Vector3d, 2>( "Array2Triangle3d" );

	MRJS::bindStdArray<Vector3b, 3>( "Array3Triangle3b" );
	MRJS::bindStdArray<Vector3i, 3>( "Array3Triangle3i" );
	MRJS::bindStdArray<Vector3ll, 3>( "Array3Triangle3ll" );
	MRJS::bindStdArray<Vector3f, 3>( "Array3Triangle3f" );
	MRJS::bindStdArray<Vector3d, 3>( "Array3Triangle3d" );
	///

	
	/// Bind the Embind interface for `Array2*`
	MRJS::bindStdArray<float, 2>( "Array2f" );
	MRJS::bindStdArray<double, 2>( "Array2d" );
	///


	/// Bind the Embind interface for `Array3*`
	MRJS::bindStdArray<float, 3>( "Array3f" );
	MRJS::bindStdArray<double, 3>( "Array3d" );
	///


	/// Bind the Embind interface for `Array4*`
	MRJS::bindStdArray<float, 4>( "Array4f" );
	MRJS::bindStdArray<double, 4>( "Array4d" );
	///


	/// Bind the Embind interface for `Array*Id`
	MRJS::bindStdArray<EdgeId, 2>( "Array2EdgeId" );
	MRJS::bindStdArray<EdgeId, 3>( "Array3EdgeId" );
	MRJS::bindStdArray<EdgeId, 4>( "Array4EdgeId" );

	MRJS::bindStdArray<UndirectedEdgeId, 2>( "Array2UndirectedEdgeId" );
	MRJS::bindStdArray<UndirectedEdgeId, 3>( "Array3UndirectedEdgeId" );
	MRJS::bindStdArray<UndirectedEdgeId, 4>( "Array4UndirectedEdgeId" );

	MRJS::bindStdArray<FaceId, 2>( "Array2FaceId" );
	MRJS::bindStdArray<FaceId, 3>( "Array3FaceId" );
	MRJS::bindStdArray<FaceId, 4>( "Array4FaceId" );

	MRJS::bindStdArray<VertId, 2>( "Array2VertId" );
	MRJS::bindStdArray<VertId, 3>( "Array3VertId" );
	MRJS::bindStdArray<VertId, 4>( "Array4VertId" );
	
	MRJS::bindStdArray<ThreeVertIds, 2>( "Array2ThreeVertIds" );
	MRJS::bindStdArray<ThreeVertIds, 3>( "Array3ThreeVertIds" );
	MRJS::bindStdArray<ThreeVertIds, 4>( "Array4ThreeVertIds" );

	MRJS::bindStdArray<PixelId, 2>( "Array2PixelId" );
	MRJS::bindStdArray<PixelId, 3>( "Array3PixelId" );
	MRJS::bindStdArray<PixelId, 4>( "Array4PixelId" );

	MRJS::bindStdArray<VoxelId, 2>( "Array2VoxelId" );
	MRJS::bindStdArray<VoxelId, 3>( "Array3VoxelId" );
	MRJS::bindStdArray<VoxelId, 4>( "Array4VoxelId" );

	MRJS::bindStdArray<RegionId, 2>( "Array2RegionId" );
	MRJS::bindStdArray<RegionId, 3>( "Array3RegionId" );
	MRJS::bindStdArray<RegionId, 4>( "Array4RegionId" );

	MRJS::bindStdArray<NodeId, 2>( "Array2NodeId" );
	MRJS::bindStdArray<NodeId, 3>( "Array3NodeId" );
	MRJS::bindStdArray<NodeId, 4>( "Array4NodeId" );

	MRJS::bindStdArray<ObjId, 2>( "Array2ObjId" );
	MRJS::bindStdArray<ObjId, 3>( "Array3ObjId" );
	MRJS::bindStdArray<ObjId, 4>( "Array4ObjId" );

	MRJS::bindStdArray<TextureId, 2>( "Array2TextureId" );
	MRJS::bindStdArray<TextureId, 3>( "Array3TextureId" );
	MRJS::bindStdArray<TextureId, 4>( "Array4TextureId" );

	MRJS::bindStdArray<GraphVertId, 2>( "Array2GraphVertId" );
	MRJS::bindStdArray<GraphVertId, 3>( "Array3GraphVertId" );
	MRJS::bindStdArray<GraphVertId, 4>( "Array4GraphVertId" );

	MRJS::bindStdArray<GraphEdgeId, 2>( "Array2GraphEdgeId" );
	MRJS::bindStdArray<GraphEdgeId, 3>( "Array3GraphEdgeId" );
	MRJS::bindStdArray<GraphEdgeId, 4>( "Array4GraphEdgeId" );
	///
}


// ------------------------------------------------------------------------
// Bind the Embind interface for `Optional*`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( OptionalTypedModule )
{
	///
	register_optional<float>();
	register_optional<int>();
	register_optional<bool>();
	register_optional<double>();
	register_optional<long long>();
	///


	///
	register_optional<MeshOrPoints>();
    register_optional<ModelPointsData>();
    register_optional<MultiObjsSamples>();
    register_optional<DentalId>();
	///


	///
	register_optional<Triangulation>();
	register_optional<Dipoles>();
	register_optional<FaceMap>();
	register_optional<VertMap>();
	register_optional<EdgeMap>();
	register_optional<UndirectedEdgeMap>();
	register_optional<ObjMap>();

	register_optional<PackMapping>();
	///


	///
	register_optional<Vector3b>();
	register_optional<Vector3i>();
	register_optional<Vector3ll>();
	register_optional<Vector3f>();
	register_optional<Vector3d>();
	///


	///
	register_optional<std::array<Vector3b, 2>>();
	register_optional<std::array<Vector3i, 2>>();
	register_optional<std::array<Vector3ll, 2>>();
	register_optional<std::array<Vector3f, 2>>();
	register_optional<std::array<Vector3d, 2>>();

	register_optional<std::array<Vector3b, 3>>();
	register_optional<std::array<Vector3i, 3>>();
	register_optional<std::array<Vector3ll, 3>>();
	register_optional<std::array<Vector3f, 3>>();
	register_optional<std::array<Vector3d, 3>>();


	register_optional<std::array<Vector2b, 2>>();
	register_optional<std::array<Vector2i, 2>>();
	register_optional<std::array<Vector2ll, 2>>();
	register_optional<std::array<Vector2f, 2>>();
	register_optional<std::array<Vector2d, 2>>();

	register_optional<std::array<Vector2b, 3>>();
	register_optional<std::array<Vector2i, 3>>();
	register_optional<std::array<Vector2ll, 3>>();
	register_optional<std::array<Vector2f, 3>>();
	register_optional<std::array<Vector2d, 3>>();
	///


	///
	register_optional<FaceBitSet>();
	register_optional<VertBitSet>();
	register_optional<EdgeBitSet>();
	register_optional<UndirectedEdgeBitSet>();
	register_optional<PixelBitSet>();
	register_optional<VoxelBitSet>();
	register_optional<RegionBitSet>();
	register_optional<NodeBitSet>();
	register_optional<ObjBitSet>();
	register_optional<TextureBitSet>();
	register_optional<GraphVertBitSet>();
	register_optional<GraphEdgeBitSet>();
	///


	///
	register_optional<VertPair>();
	register_optional<FacePair>();
	register_optional<EdgePair>();
	register_optional<UndirectedEdgePair>();
	///


	///
	register_optional<std::vector<VertPair>>();
	register_optional<std::vector<FacePair>>();
	register_optional<std::vector<EdgePair>>();
	register_optional<std::vector<UndirectedEdgePair>>();
	///


	///
	register_optional<EdgeId>();
	register_optional<UndirectedEdgeId>();
	register_optional<FaceId>();
	register_optional<VertId>();
	register_optional<PixelId>();
	register_optional<VoxelId>();
	register_optional<RegionId>();
	register_optional<NodeId>();
	register_optional<ObjId>();
	register_optional<TextureId>();
	register_optional<GraphVertId>();
	register_optional<GraphEdgeId>();
	///


	///
	register_optional<std::vector<EdgeId>>();
	register_optional<std::vector<UndirectedEdgeId>>();
	register_optional<std::vector<FaceId>>();
	register_optional<std::vector<VertId>>();
	register_optional<std::vector<PixelId>>();
	register_optional<std::vector<VoxelId>>();
	register_optional<std::vector<RegionId>>();
	register_optional<std::vector<NodeId>>();
	register_optional<std::vector<ObjId>>();
	register_optional<std::vector<TextureId>>();
	register_optional<std::vector<GraphVertId>>();
	register_optional<std::vector<GraphEdgeId>>();
	///
}


// ------------------------------------------------------------------------
// Bind the Embind interface for `*Functor*`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( FunctorTypedModule )
{
	///
	class_<std::function<std::string( std::string )>>( "StringFunctorString" )
		.constructor<>()
		.function( "opcall", &std::function<std::string( std::string )>::operator() );

	class_<std::function<float( int )>>( "FloatFunctorInt" )
		.constructor<>()
		.function( "opcall", &std::function<float( int )>::operator() );
	///


	///
	class_<std::function<bool( float )>>( "ProgressCallback" )
		.constructor<>()
		.function( "opcall", &std::function<bool( float )>::operator() );
	///


	///
	class_<std::function<void( EdgeId, EdgeId )>>( "VoidFunctorEdgeIdEdgeId" )
		.constructor<>()
		.function( "opcall", &std::function<void( EdgeId, EdgeId )>::operator() );
	///


	///
	class_<std::function<bool( VertId )>>( "VertPredicate" )
		.constructor<>()
		.function( "opcall", &std::function<bool( VertId )>::operator() );

	class_<std::function<bool( FaceId )>>( "FacePredicate" )
		.constructor<>()
		.function( "opcall", &std::function<bool( FaceId )>::operator() );

	class_<std::function<bool( EdgeId )>>( "EdgePredicate" )
		.constructor<>()
		.function( "opcall", &std::function<bool( EdgeId )>::operator() );

	class_<std::function<bool( UndirectedEdgeId )>>( "UndirectedEdgePredicate" )
		.constructor<>()
		.function( "opcall", &std::function<bool( UndirectedEdgeId )>::operator() );
	///


	///
	class_<std::function<float( VertId )>>( "VertMetric" )
		.constructor<>()
		.function( "opcall", &std::function<float( VertId )>::operator() );

	class_<std::function<float( FaceId )>>( "FaceMetric" )
		.constructor<>()
		.function( "opcall", &std::function<float( FaceId )>::operator() );

	class_<std::function<float( EdgeId )>>( "EdgeMetric" )
		.constructor<>()
		.function( "opcall", &std::function<float( EdgeId )>::operator() );

	class_<std::function<float( UndirectedEdgeId )>>( "UndirectedEdgeMetric" )
		.constructor<>()
		.function( "opcall", &std::function<float( UndirectedEdgeId )>::operator() );
	///


	///
	class_<std::function<float( Triangulation )>>( "FloatFunctorTriangulation" )
		.constructor<>()
		.function( "opcall", &std::function<float( Triangulation )>::operator() );
	
	class_<std::function<float( Dipoles )>>( "FloatFunctorDipoles" )
		.constructor<>()
		.function( "opcall", &std::function<float( Dipoles )>::operator() );
	class_<std::function<float( FaceMap )>>( "FloatFunctorFaceMap" )
		.constructor<>()
		.function( "opcall", &std::function<float( FaceMap )>::operator() );
	
	class_<std::function<float( VertMap )>>( "FloatFunctorVertMap" )
		.constructor<>()
		.function( "opcall", &std::function<float( VertMap )>::operator() );
	
	class_<std::function<float( EdgeMap )>>( "FloatFunctorEdgeMap" )
		.constructor<>()
		.function( "opcall", &std::function<float( EdgeMap )>::operator() );
	
	class_<std::function<float( UndirectedEdgeMap )>>( "FloatFunctorUndirectedEdgeMap" )
		.constructor<>()
		.function( "opcall", &std::function<float( UndirectedEdgeMap )>::operator() );
	
	class_<std::function<float( ObjMap )>>( "FloatFunctorObjMap" )
		.constructor<>()
		.function( "opcall", &std::function<float( ObjMap )>::operator() );
	///


	///
	class_<std::function<float( FaceBitSet )>>( "FloatFunctorFaceBitSet" )
		.constructor<>()
		.function( "opcall", &std::function<float( FaceBitSet )>::operator() );
	
	class_<std::function<float( VertBitSet )>>( "FloatFunctorVertBitSet" )
		.constructor<>()
		.function( "opcall", &std::function<float( VertBitSet )>::operator() );
	
	class_<std::function<float( EdgeBitSet )>>( "FloatFunctorEdgeBitSet" )
		.constructor<>()
		.function( "opcall", &std::function<float( EdgeBitSet )>::operator() );
	
	class_<std::function<float( UndirectedEdgeBitSet )>>( "FloatFunctorUndirectedEdgeBitSet" )
		.constructor<>()
		.function( "opcall", &std::function<float( UndirectedEdgeBitSet )>::operator() );
	
	class_<std::function<float( PixelBitSet )>>( "FloatFunctorPixelBitSet" )
		.constructor<>()
		.function( "opcall", &std::function<float( PixelBitSet )>::operator() );
	
	class_<std::function<float( VoxelBitSet )>>( "FloatFunctorVoxelBitSet" )
		.constructor<>()
		.function( "opcall", &std::function<float( VoxelBitSet )>::operator() );
	
	class_<std::function<float( RegionBitSet )>>( "FloatFunctorRegionBitSet" )
		.constructor<>()
		.function( "opcall", &std::function<float( RegionBitSet )>::operator() );
	
	class_<std::function<float( NodeBitSet )>>( "FloatFunctorNodeBitSet" )
		.constructor<>()
		.function( "opcall", &std::function<float( NodeBitSet )>::operator() );
	
	class_<std::function<float( ObjBitSet )>>( "FloatFunctorObjBitSet" )
		.constructor<>()
		.function( "opcall", &std::function<float( ObjBitSet )>::operator() );
	
	class_<std::function<float( TextureBitSet )>>( "FloatFunctorTextureBitSet" )
		.constructor<>()
		.function( "opcall", &std::function<float( TextureBitSet )>::operator() );
	
	class_<std::function<float( GraphVertBitSet )>>( "FloatFunctorGraphVertBitSet" )
		.constructor<>()
		.function( "opcall", &std::function<float( GraphVertBitSet )>::operator() );
	
	class_<std::function<float( GraphEdgeBitSet )>>( "FloatFunctorGraphEdgeBitSet" )
		.constructor<>()
		.function( "opcall", &std::function<float( GraphEdgeBitSet )>::operator() );
	///


	///
	class_<std::function<Expected<SurfacePath>( const MeshTriPoint&, const MeshTriPoint&, int, int )>>( "ExpectedSurfacePathFunctorMeshTriPoint" )
		.constructor<>()
		.function( "opcall", &std::function<Expected<SurfacePath>( const MeshTriPoint&, const MeshTriPoint&, int, int )>::operator() );
	///


	///
	class_<std::function<Vector3f ( const Vector3f & )>>( "Vector3fFunctorVector3f" )
		.constructor<>()
		.function( "opcall", &std::function<Vector3f ( const Vector3f & )>::operator() );
	///
}
