#pragma once

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshTopology.h>

using namespace emscripten;
using namespace MR;

namespace MRJS {

// Helper function to export mesh data using typed_memory_view
inline auto exportMeshData = []( const Mesh& meshToExport ) -> val {
    // === Export point data ===
    auto _points = meshToExport.points;
    size_t pointCount = _points.size();
    size_t totalPointElements = pointCount * 3;
    const float* pointData = reinterpret_cast<const float*>( _points.data() );

    // Use typed_memory_view for vertices
    val pointsArray = val( typed_memory_view(
        totalPointElements, 
        pointData
    ) );

    // === Export triangle data ===
    Triangulation _tri = meshToExport.topology.getTriangulation();
    size_t triangleCount = _tri.size();
    size_t totalTriElements = triangleCount * 3; // Each triangle has three indexes
    const int* triData = reinterpret_cast<const int*>( _tri.data() );

    // Use typed_memory_view for triangles
    val triangleArray = val( typed_memory_view(
        totalTriElements, 
        triData
    ) );
    
    val meshData = val::object();
    meshData.set( "vertices", pointsArray );
    meshData.set( "vertexCount", pointCount );
    meshData.set( "indices", triangleArray );
    meshData.set( "triangleCount", triangleCount );

    return meshData;
};

} // namespace MRUtil
