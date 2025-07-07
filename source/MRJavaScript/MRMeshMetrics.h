#pragma once

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshMetrics.h>
#include <MRMesh/MRPlane3.h>

using namespace emscripten;
using namespace MR;


class FillHoleMetricWrapper {
private:
	FillHoleMetric fillHoleMetric;

public:
    FillHoleMetricWrapper() : fillHoleMetric() {}
	FillHoleMetricWrapper( FillHoleMetric m ) : fillHoleMetric( std::move( m ) ) {}
	FillHoleMetricWrapper( const FillHoleMetricWrapper& other ) : fillHoleMetric( other.fillHoleMetric ) {}

	const FillHoleMetric& getFillHoleMetric() const;
	FillHoleMetric& getFillHoleMetric();

	const FillTriangleMetric& getFillTriangleMetric() const;
	FillTriangleMetric& getFillTriangleMetric();

	const FillEdgeMetric& getFillEdgeMetric() const;
	FillEdgeMetric& getFillEdgeMetric();

	const FillCombineMetric& getFillCombineMetric() const;
	FillCombineMetric& getFillCombineMetric();

	FillHoleMetricWrapper& operator=( const FillHoleMetricWrapper& other );
};
