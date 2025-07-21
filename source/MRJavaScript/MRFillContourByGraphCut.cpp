#include <MRPch/MRWasm.h>

#include <MRMesh/MRSurroundingContour.h>
#include <MRMesh/MRFillContourByGraphCut.h>
#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MREdgeMetric.h>

#include "MRUtils.h"

using namespace emscripten;
using namespace MR;


/**
 * @brief Segment a mesh around some key vertices
 *
 * Step 1: Create closed loops that pass through specified points (either edges or vertices) while minimizing a cost metric by using `surroundingContour()`.
 *
 * Step 2: The `fillContourLeftByGraphCut()` function use graph cut algorithms with contours to find optimal regions
 *
 * @param mesh
 * @param keyVertices
 */
class MeshSegmentation {
private:
	Mesh mesh_;
	EdgeMetric edgeMetric_;

public:
	/**
	 * @brief Constructor - initializes with a mesh and default edge metric
	 */
	MeshSegmentation( const Mesh& mesh ) : mesh_( mesh )
	{
		// Initialize with a default edge metric
		// e.g. `discreteAbsMeanCurvatureMetric()` & `edgeCurvMetric()`
		edgeMetric_ = discreteAbsMeanCurvatureMetric( mesh_ );
	}
	void setMesh( const Mesh& m )
	{
		mesh_ = m;
	}
	void setEdgeMetric( const EdgeMetric& metric )
	{
		edgeMetric_ = metric;
	}

	/**
	 * @brief Main segmentation function called from JavaScript
	 * Takes coordinates as flat array and direction vector, returns emscripten val object
	 *
	 * @param coordinates Flat array of coordinates [x1,y1,z1, x2,y2,z2, x3,y3,z3, ...]
	 * @param dir Direction vector components for contour orientation [dirX, dirY, dirZ]
	 */
	val segmentByPoints( const std::vector<float>& coordinates, const std::vector<float>& dir )
	{
		val result = val::object();

		// Input validation
		if ( mesh_.points.empty() )
		{
			result.set( "success", false );
			result.set( "error", std::string( "Mesh not initialized" ) );

			return result;
		}

		try
		{
			VertCoords inputPoints = MRJS::parseJSVertices( coordinates );

			if ( inputPoints.size() < 2 || inputPoints.size() > 3 )
			{
				result.set( "success", false );
				result.set( "error", std::string( "Need exactly 2 or 3 input points" ) );

				return result;
			}

			// Step 1: Find closest vertices on the mesh for each input point using `findProjection()`
			std::vector<VertId> keyVertices;
			keyVertices.reserve( inputPoints.size() );

			MeshPart m = MeshPart( mesh_ );

			mesh_.getAABBTree();
			for ( const Vector3f& point : inputPoints )
			{
				MeshProjectionResult closestVert = findProjection( point, m );
				if ( !closestVert.valid() )
				{
					result.set( "success", false );
					result.set( "error", std::string( "Could not find valid vertex for input point" ) );

					return result;
				}
				keyVertices.push_back( mesh_.getClosestVertex( closestVert.proj ) );
			}

			// Step 2: Use the direction provided by JavaScript
			Vector3f contourDirection( dir[0], dir[1], dir[2] );

			// Normalize the direction vector to ensure it's a unit vector
			float dirLength = contourDirection.length();
			if ( dirLength < 1e-6f )
			{
				result.set( "success", false );
				result.set( "error", std::string( "Direction vector is too small or zero" ) );

				return result;
			}
			contourDirection /= dirLength;

			///
			// Use Gram-Schmidt-like orthogonalization to infer direction:
			// 1. cross(pointsDir, meshDir) to obtain a vector perpendicular to both directions.
			// 2. Then cross it with pointsDir to get a vector that lies in the plane of meshDir and is orthogonal to pointsDir.
			// 3. Then determine if it is in the same direction or the opposite direction as meshDir.
			Vector3f meshDir = Vector3f{ mesh_.dirArea() };
			Vector3f pointsDir = mesh_.points[keyVertices[0]] - mesh_.points[keyVertices[1]];

			Vector3f guessDir = cross(cross(pointsDir, meshDir), pointsDir);

			// Direction Correction
			if (dot(guessDir, meshDir) < 0)
				guessDir = -guessDir;

			Vector3f direction = guessDir.normalized();
			///

			// Step 3: Create surrounding contour
			auto contourResult = surroundingContour( mesh_, keyVertices, edgeMetric_, direction /*contourDirection*/ );

			if ( !contourResult )
			{
				result.set( "success", false );
				result.set( "error", std::string( "Failed to create surrounding contour: " ) + contourResult.error() );

				return result;
			}

			EdgeLoop contour = contourResult.value();

			// Step 4: Convert EdgeLoop to EdgePath for `fillContourLeftByGraphCut()`
			EdgePath contourPath( contour.begin(), contour.end() );

			// Step 5: Fill the contour to get the segmented region
			Mesh segMesh;
			FaceBitSet segmentedFaces = fillContourLeftByGraphCut( mesh_.topology, contourPath, edgeMetric_ );
			segMesh.addMeshPart( {mesh_, &segmentedFaces} );

			// Step 6: Convert results to JavaScript-friendly format using emscripten val
			val meshData = MRJS::exportMeshData( segMesh );
						
			// Since `EdgeId` has an implicit conversion operator to int, and it is internally represented as an int
			// We can directly reinterpret `EdgeId*` as `int*`
			const int* contourData = reinterpret_cast<const int*>( contour.data() );
			size_t contourSize = contour.size();
			val contourEdgesArray = val( typed_memory_view( contourSize, contourData ) );

			// Build the result object
			result.set( "success", true );
			result.set( "contourEdges", contourEdgesArray );
			result.set( "mesh", meshData );
		}
		catch ( const std::exception& e )
		{
			result.set( "success", false );
			result.set( "error", std::string( "Exception during segmentation: " ) + e.what() );
		}

		return result;
	}
};


EMSCRIPTEN_BINDINGS( MeshSegmentationModule )
{
	class_<MeshSegmentation>( "MeshSegmentation" )
		.constructor<const Mesh&>()

		.function( "segmentByPoints", &MeshSegmentation::segmentByPoints );
}
