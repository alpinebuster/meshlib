#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MREdgeMetric.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( EdgeMetricModule )
{
	function( "identityMetric", &identityMetric );

	function( "edgeLengthMetric", select_overload<EdgeMetric( const Mesh& )>( &edgeLengthMetric ) );
	function( "edgeLengthMetricFromTopology", select_overload<EdgeMetric( const MeshTopology&, const VertCoords& )>( &edgeLengthMetric ) );

	function( "discreteAbsMeanCurvatureMetric", select_overload<EdgeMetric( const Mesh& )>( &discreteAbsMeanCurvatureMetric ) );
	function( "discreteAbsMeanCurvatureMetricFromTopology", select_overload<EdgeMetric( const MeshTopology&, const VertCoords& )>( &discreteAbsMeanCurvatureMetric ) );

	function( "discreteMinusAbsMeanCurvatureMetric", select_overload<EdgeMetric( const Mesh& )>( &discreteMinusAbsMeanCurvatureMetric ) );
	function( "discreteMinusAbsMeanCurvatureMetricFromTopology", select_overload<EdgeMetric( const MeshTopology&, const VertCoords& )>( &discreteMinusAbsMeanCurvatureMetric ) );

	function( "edgeCurvMetric", select_overload<EdgeMetric( const Mesh&, float, float )>( &edgeCurvMetric ) );
	function( "edgeCurvMetricFromTopology", select_overload<EdgeMetric( const MeshTopology&, const VertCoords&, float, float )>( &edgeCurvMetric ) );

	function( "edgeTableSymMetric", &edgeTableSymMetric );
}
