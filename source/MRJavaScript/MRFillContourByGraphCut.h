#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMesh.h>

using namespace emscripten;
using namespace MR;

namespace MRJS {

/**
 * @brief Segment a mesh around some key vertices
 *
 * Step 1: Create closed loops that pass through specified points (either edges or vertices) while minimizing a cost metric by using `surroundingContour()`.
 *
 * Step 2: The `fillContourLeftByGraphCut()` function use graph cut algorithms with contours to find optimal regions
 * 
 * Takes coordinates as flat array and direction vector, returns emscripten val object
 *
 * @param coordinates Flat array of coordinates [x1,y1,z1, x2,y2,z2, x3,y3,z3, ...]
 * @param dir Direction vector components for contour orientation [dirX, dirY, dirZ]
 */
val segmentByPointsImpl(  Mesh& mesh_, EdgeMetric& edgeMetric_, const std::vector<float>& coordinates, const std::vector<float>& dir );

} // namespace MRJS
