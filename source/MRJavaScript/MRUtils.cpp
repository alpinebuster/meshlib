#include <optional>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRMeshOrPoints.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MREdgePaths.h>
#include <MRMesh/MRFillContour.h>
#include <MRMesh/MREdgeMetric.h>
#include <MRMesh/MRPointCloud.h>
#include <MRMesh/MRAABBTreePoints.h>
#include <MRMesh/MRDipole.h>

#include "MRUtils.h"

using namespace emscripten;
using namespace MR;


namespace MRJS
{

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


EMSCRIPTEN_BINDINGS( UtilsModule )
{
	register_vector<int>( "StdVectori" );
	register_vector<float>( "StdVectorf" );
	register_vector<double>( "StdVectord" );
	register_vector<long long>( "StdVectorll" );
	register_vector<uint64_t>( "StdVectorUi64" );
    // register_vector<bool>( "StdVectorb" );

	
	// ------------------------------------------------------------------------
    // Bind the Embind interface for `Array2*`
    // ------------------------------------------------------------------------
	value_array<std::array<float, 2>>( "Array2f" )
		.element( emscripten::index<0>() )
		.element( emscripten::index<1>() );
	value_array<std::array<double, 2>>( "Array2d" )
		.element( emscripten::index<0>() )
		.element( emscripten::index<1>() );


	// ------------------------------------------------------------------------
    // Bind the Embind interface for `Array3*`
    // ------------------------------------------------------------------------
	value_array<std::array<float, 3>>( "Array3f" )
		.element( emscripten::index<0>() )
		.element( emscripten::index<1>() )
		.element( emscripten::index<2>() );
	value_array<std::array<double, 3>>( "Array3d" )
		.element( emscripten::index<0>() )
		.element( emscripten::index<1>() )
		.element( emscripten::index<2>() );


	// ------------------------------------------------------------------------
    // Bind the Embind interface for `Array4*`
    // ------------------------------------------------------------------------
	value_array<std::array<float, 4>>( "Array4f" )
		.element( emscripten::index<0>() )
		.element( emscripten::index<1>() )
		.element( emscripten::index<2>() )
		.element( emscripten::index<3>() );
	value_array<std::array<double, 4>>( "Array4d" )
		.element( emscripten::index<0>() )
		.element( emscripten::index<1>() )
		.element( emscripten::index<2>() )
		.element( emscripten::index<3>() );


	// ------------------------------------------------------------------------
    // Bind the Embind interface for `Array*Id`
    // ------------------------------------------------------------------------
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


	// ------------------------------------------------------------------------
    // Bind the Embind interface for `Optional*`
	// ------------------------------------------------------------------------
	///
	register_optional<float>();
	register_optional<int>();
	register_optional<bool>();
	register_optional<double>();
	register_optional<long long>();
	///


	///
	register_optional<MeshOrPoints>();
	///


	///
	register_optional<Triangulation>();
	register_optional<Dipoles>();
	register_optional<FaceMap>();
	register_optional<VertMap>();
	register_optional<EdgeMap>();
	register_optional<UndirectedEdgeMap>();
	register_optional<ObjMap>();
	///


	///
	register_optional<Vector3b>();
	register_optional<Vector3i>();
	register_optional<Vector3ll>();
	register_optional<Vector3f>();
	register_optional<Vector3d>();
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

	
	// ------------------------------------------------------------------------
    // Bind the Embind interface for `*Functor*`
	// ------------------------------------------------------------------------
	class_<std::function<std::string( std::string )>>( "StringFunctorString" )
		.constructor<>()
		.function( "opcall", &std::function<std::string( std::string )>::operator() );

	class_<std::function<bool( float )>>( "ProgressCallback" )
		.constructor<>()
		.function( "opcall", &std::function<bool( float )>::operator() );

	
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
}
