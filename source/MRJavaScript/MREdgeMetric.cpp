#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MREdgeMetric.h>

#include "MREdgeMetric.h"

using namespace emscripten;
using namespace MR;


float EdgeMetricWrapper::evaluate( EdgeId edgeId ) const
{
	return metric( edgeId );
}

const EdgeMetric& EdgeMetricWrapper::getMetric() const
{
	return metric;
}
EdgeMetric& EdgeMetricWrapper::getMetric()
{
	return metric;
}

EdgeMetricWrapper& EdgeMetricWrapper::operator=( const EdgeMetricWrapper& other )
{
	if ( this != &other )
	{
		metric = other.metric;
	}
	return *this;
}


// Factory functions that return wrapped metrics
EdgeMetricWrapper createIdentityMetric()
{
	return EdgeMetricWrapper( identityMetric() );
}

EdgeMetricWrapper createEdgeLengthMetric( const Mesh& mesh )
{
	return EdgeMetricWrapper( edgeLengthMetric( mesh ) );
}

EdgeMetricWrapper createEdgeLengthMetricFromTopology( const MeshTopology& topology, const VertCoords& points )
{
	return EdgeMetricWrapper( edgeLengthMetric( topology, points ) );
}

EdgeMetricWrapper createDiscreteAbsMeanCurvatureMetric( const Mesh& mesh )
{
	return EdgeMetricWrapper( discreteAbsMeanCurvatureMetric( mesh ) );
}

EdgeMetricWrapper createDiscreteAbsMeanCurvatureMetricFromTopology( const MeshTopology& topology, const VertCoords& points )
{
	return EdgeMetricWrapper( discreteAbsMeanCurvatureMetric( topology, points ) );
}

EdgeMetricWrapper createDiscreteMinusAbsMeanCurvatureMetric( const Mesh& mesh )
{
	return EdgeMetricWrapper( discreteMinusAbsMeanCurvatureMetric( mesh ) );
}

EdgeMetricWrapper createDiscreteMinusAbsMeanCurvatureMetricFromTopology( const MeshTopology& topology, const VertCoords& points )
{
	return EdgeMetricWrapper( discreteMinusAbsMeanCurvatureMetric( topology, points ) );
}

EdgeMetricWrapper createEdgeCurvMetric( const Mesh& mesh, float angleSinFactor = 2.0f, float angleSinForBoundary = 0.0f )
{
	return EdgeMetricWrapper( edgeCurvMetric( mesh, angleSinFactor, angleSinForBoundary ) );
}

EdgeMetricWrapper createEdgeCurvMetricFromTopology( const MeshTopology& topology, const VertCoords& points,
												   float angleSinFactor = 2.0f, float angleSinForBoundary = 0.0f )
{
	return EdgeMetricWrapper( edgeCurvMetric( topology, points, angleSinFactor, angleSinForBoundary ) );
}

EdgeMetricWrapper createEdgeTableSymMetric( const MeshTopology& topology, const EdgeMetricWrapper& metric )
{
	return EdgeMetricWrapper( edgeTableSymMetric( topology, metric.getMetric() ) );
}


EMSCRIPTEN_BINDINGS( EdgeMetricModule )
{
	// Register the `EdgeMetricWrapper` class
	class_<EdgeMetricWrapper>( "EdgeMetricWrapper" )
		.constructor<const EdgeMetricWrapper&>()
		.class_function( "createEdgeMetricWrapper",
			optional_override( [] ( const EdgeMetricWrapper& other )
			{
				return EdgeMetricWrapper( other );
			} ))

		.function( "evaluate", &EdgeMetricWrapper::evaluate );

	// Register factory functions for creating different types of metrics
	function( "identityMetric", &createIdentityMetric );

	// Edge length metrics
	function( "edgeLengthMetric", &createEdgeLengthMetric );
	function( "edgeLengthMetricFromTopology", &createEdgeLengthMetricFromTopology );

	// Discrete mean curvature metrics
	function( "discreteAbsMeanCurvatureMetric", &createDiscreteAbsMeanCurvatureMetric );
	function( "discreteAbsMeanCurvatureMetricFromTopology", &createDiscreteAbsMeanCurvatureMetricFromTopology );

	// Discrete minus mean curvature metrics
	function( "discreteMinusAbsMeanCurvatureMetric", &createDiscreteMinusAbsMeanCurvatureMetric );
	function( "discreteMinusAbsMeanCurvatureMetricFromTopology", &createDiscreteMinusAbsMeanCurvatureMetricFromTopology );

	// Edge curvature metrics
	function( "edgeCurvMetric", &createEdgeCurvMetric );
	function( "edgeCurvMetricFromTopology", &createEdgeCurvMetricFromTopology );

	// Edge table symmetric metric
	function( "edgeTableSymMetric", &createEdgeTableSymMetric );
}
