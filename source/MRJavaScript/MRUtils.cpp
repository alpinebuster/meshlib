
#include <emscripten/bind.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRMeshOrPoints.h>
#include <MRMesh/MRBitSet.h>

#include "MRUtils.h"

using namespace emscripten;
using namespace MR;

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
	// FIXME: `std:optional`
	// MRJS::register_optional<MeshOrPoints>( "OptionalMeshOrPoints" );
	// MRJS::register_optional<Vector3f>( "OptionalVector3f" );
	// MRJS::register_optional<VertBitSet>( "OptionalVertBitSet" );
}
