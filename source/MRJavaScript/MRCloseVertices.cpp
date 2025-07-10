#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRPointCloud.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRAABBTreePoints.h>
#include <MRMesh/MRProgressCallback.h>
#include <MRMesh/MRDipole.h>
#include <MRMesh/MRCloseVertices.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( CloseVerticesModule )
{
	function( "findSmallestCloseVertices", select_overload<std::optional<VertMap>( const Mesh&, float, const ProgressCallback& )>( &findSmallestCloseVertices ) );
	function( "findSmallestCloseVerticesFromCloud", select_overload<std::optional<VertMap>( const PointCloud&, float, const ProgressCallback& )>( &findSmallestCloseVertices ) );
	function( "findSmallestCloseVerticesFromCoords", select_overload<std::optional<VertMap>( const VertCoords&, float, const VertBitSet*, const ProgressCallback& )>( &findSmallestCloseVertices ), allow_raw_pointers() );

	function( "findSmallestCloseVerticesUsingTree", &findSmallestCloseVerticesUsingTree, allow_raw_pointers() );

	function( "findCloseVertices", select_overload<std::optional<VertBitSet>( const Mesh&, float, const ProgressCallback& )>( &findCloseVertices ) );
	function( "findCloseVerticesFromCloud", select_overload<std::optional<VertBitSet>( const PointCloud&, float, const ProgressCallback& )>( &findCloseVertices ) );
	function( "findCloseVerticesFromCoords", select_overload<std::optional<VertBitSet>( const VertCoords&, float, const VertBitSet*, const ProgressCallback& )>( &findCloseVertices ), allow_raw_pointers() );
	function( "findCloseVerticesFromMap", select_overload<VertBitSet( const VertMap& )>( &findCloseVertices ) );

	function( "findTwinEdgePairs", &findTwinEdgePairs );

	function( "findTwinEdges", select_overload<EdgeBitSet( const Mesh&, float )>( &findTwinEdges ) );
	function( "findTwinEdgesFromEdgePairs", select_overload<EdgeBitSet( const std::vector<EdgePair>& )>( &findTwinEdges ) );

	function( "findTwinUndirectedEdges", select_overload<UndirectedEdgeBitSet( const Mesh&, float )>( &findTwinUndirectedEdges ) );
	function( "findTwinUndirectedEdgesFromEdgePairs", select_overload<UndirectedEdgeBitSet( const std::vector<EdgePair>& )>( &findTwinUndirectedEdges ) );

	function( "findTwinUndirectedEdgeHashMap", select_overload<UndirectedEdgeHashMap( const Mesh&, float )>( &findTwinUndirectedEdgeHashMap ) );
	function( "findTwinUndirectedEdgeHashMapFromEdgePairs", select_overload<UndirectedEdgeHashMap( const std::vector<EdgePair>& )>( &findTwinUndirectedEdgeHashMap ) );
}
