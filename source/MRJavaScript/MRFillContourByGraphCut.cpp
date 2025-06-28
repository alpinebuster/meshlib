#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRSurroundingContour.h>
#include <MRMesh/MRFillContourByGraphCut.h>
#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MREdgeMetric.h>

using namespace emscripten;
using namespace MR;


/**
 * @brief Segment a mesh around some key vertices
 *
 * Step 1: Create closed loops that pass through specified points (either edges or vertices) while minimizing a cost metric by using `surroundingContour()`.
 *
 * Step 2:  Once you have contours, the `fillContourLeftByGraphCut()` function use graph cut algorithms to find optimal regions
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
		// Initialize with a default edge metric (you may want to customize this)
		// e.g. `discreteAbsMeanCurvatureMetric()` & `edgeCurvMetric()`
		edgeMetric_ = discreteAbsMeanCurvatureMetric( mesh_ );
	}

	void setMesh( const Mesh& m )
	{
		mesh_ = m;
	}
	/**
	 * @brief Set a custom edge metric function
	 * This allows you to customize how edge costs are calculated
	 */
	void setEdgeMetric( const EdgeMetric& metric )
	{
		edgeMetric_ = metric;
	}

	/**
	 * @brief Helper function to convert flat coordinate array to Vector3f points
	 * This design is more JavaScript-friendly than individual Point3D objects
	 * coordinates should contain [x1,y1,z1, x2,y2,z2, x3,y3,z3, ...] for each point
	 */
	std::vector<Vector3f> parseCoordinates( const std::vector<float>& coordinates )
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
			// Parse coordinates into Vector3f points
			std::vector<Vector3f> inputPoints = parseCoordinates( coordinates );

			if ( inputPoints.size() < 2 || inputPoints.size() > 3 )
			{
				result.set( "success", false );
				result.set( "error", std::string( "Need exactly 2 or 3 input points" ) );
				return result;
			}

			// Step 1: Find closest vertices on the mesh for each input point using `findProjection()`
			std::vector<VertId> keyVertices( inputPoints.size() );
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

			// Step 3: Create surrounding contour using your existing algorithm
			auto contourResult = surroundingContour( mesh_, keyVertices, edgeMetric_, contourDirection );

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
			// val contourEdgesArray = val::array();
			// for ( size_t i = 0; i < contour.size(); ++i )
			// {
			// 	contourEdgesArray.set( i, static_cast< int >( contour[i] ) );
			// }

			// Build the result object
			result.set( "success", true );
			// result.set( "contourEdges", contourEdgesArray );
			result.set( "segMesh", segMesh );
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
