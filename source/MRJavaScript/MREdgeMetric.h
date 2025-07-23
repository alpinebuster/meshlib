#pragma once

#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MREdgeMetric.h>

using namespace emscripten;
using namespace MR;


// Wrapper class to make `EdgeMetric` more JavaScript-friendly
class EdgeMetricWrapper {
private:
	EdgeMetric metric;

public:
    EdgeMetricWrapper() : metric() {}
	EdgeMetricWrapper( EdgeMetric m ) : metric( std::move( m ) ) {}
	// Allow copying for JavaScript use
	EdgeMetricWrapper( const EdgeMetricWrapper& other ) : metric( other.metric ) {}
	
	// Method to evaluate the metric for a given edge
	float evaluate( EdgeId edgeId ) const;

	const EdgeMetric& getMetric() const;
	EdgeMetric& getMetric();

	EdgeMetricWrapper& operator=( const EdgeMetricWrapper& other );
};
