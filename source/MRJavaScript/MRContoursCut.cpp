#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRPolyline.h>
#include <MRMesh/MRLine3.h>
#include <MRMesh/MRMeshProject.h>
#include <MRMesh/MRContoursCut.h>
#include <MRMesh/MRPolylineProject.h>
#include <MRMesh/MRMeshBoolean.h>
#include <MRMesh/MROneMeshContours.h>
#include <MRMesh/MRMeshIntersect.h>
#include <MRMesh/MRParallelFor.h>
#include <MRMesh/MRFillContour.h>
#include <MRMesh/MREdgePaths.h>

#include "MRUtils.h"

using namespace emscripten;
using namespace MR;

class BoolResults {
public:
    float* vertices;
    size_t verticesLength;
    int* faces;
    size_t facesLength;

    // Constructor
    BoolResults() : vertices(nullptr), verticesLength(0), faces(nullptr), facesLength(0) {}

    ~BoolResults() {
        delete[] vertices;
        delete[] faces;
    }
};

/**
 *@brief CutMesh with contour and extracting cutted parts
 * 
 *  using EdgePath = std::vector<EdgeId>;
 *  using EdgeLoop = std::vector<EdgeId>;
 *  using EdgeLoops = std::vector<EdgeLoop>;
 *
 * @param mesh 
 * @param cut 
 * @return std::pair<Mesh, Mesh> 
 */
std::pair<Mesh, Mesh> returnParts_( const Mesh& mesh, const std::vector<EdgePath>& cut )
{
    Mesh innerMesh;
    auto innerBitSet = fillContourLeft( mesh.topology, cut );
    innerMesh.addMeshPart( {mesh, &innerBitSet} );

    Mesh outerMesh;
    auto cutReverse = cut;
    MR::reverse( cutReverse );
    auto outerBitSet = fillContourLeft( mesh.topology, cutReverse  );
	outerMesh.addMeshPart( {mesh, &outerBitSet} );
	
	return { innerMesh, outerMesh };
}

/**
 *@brief Cut mesh with polyline
 *
 * 1. Project points of polyline to mesh
 * 2. Convert result vector to `cutMesh()` input type
 * 3. Do `cutMesh()` (it works only with contours without self-intersections)
 *
 * @param mesh
 * @param coordinates Must be closed
 * @param coordinatesLength 
 * @return val 
 */
val cutMeshWithPolyline( Mesh& mesh, const std::vector<float>& coordinates )
{
	std::vector<Vector3f> polyline;

    int coordinatesLength = coordinates.size();
    if (coordinatesLength % 3 != 0) {
		val obj = val::object();
		obj.set( "success", false );
		obj.set( "error", "Coordinates length must be a multiple of 3!" );

		return obj;
    }

	polyline.reserve( coordinatesLength / 3 );

	for ( size_t i = 0; i < coordinatesLength; i += 3 )
	{
		polyline.emplace_back( coordinates[i], coordinates[i + 1], coordinates[i + 2] );
	}
	Polyline3 initialPolyline;
	initialPolyline.addFromPoints( polyline.data(), polyline.size() );

	std::vector<MeshTriPoint> projectedPolyline;
	projectedPolyline.reserve( initialPolyline.points.size() );
	MeshPart m = MeshPart( mesh, nullptr );


	val jsTestProjectedPoint = val::array();

	mesh.getAABBTree(); // Create tree in parallel before loop
	for ( Vector3f pt : initialPolyline.points )
	{
		MeshProjectionResult mpr = findProjection( pt, m );
		projectedPolyline.push_back( mpr.mtp );


		val projPoint = val::object();
		projPoint.set("x", mpr.proj.point.x);
		projPoint.set("y", mpr.proj.point.y);
		projPoint.set("z", mpr.proj.point.z);
		jsTestProjectedPoint.call<void>("push", projPoint);
	}

	auto meshContour = convertMeshTriPointsToMeshContour( mesh, projectedPolyline );
	if ( meshContour )
	{
    	const MR::OneMeshContour& testContour = *meshContour;
		val jsTestProjectedContour = val::array();
		for (const auto& intersection : testContour.intersections)
		{
			val point = val::object();
			point.set("x", intersection.coordinate.x);
			point.set("y", intersection.coordinate.y);
			point.set("z", intersection.coordinate.z);
			jsTestProjectedContour.call<void>("push", point);
		}


		CutMeshResult cutResults = cutMesh( mesh, { *meshContour } );


		val jsTestCutPoints = val::array();
		for (const auto& loop : cutResults.resultCut) {
			for (const auto& edge : loop) {
				Vector3f p = mesh.orgPnt(edge);
				val point = val::object();
				point.set("x", p.x);
				point.set("y", p.y);
				point.set("z", p.z);
				jsTestCutPoints.call<void>("push", point);
			}
		}
		
		// FIXME:
		// auto [innerMesh, outerMesh] = returnParts_( mesh, cutResults.resultCut );

		auto innerBitSet = fillContourLeft( mesh.topology, cutResults.resultCut );
		Mesh innerMesh = mesh.cloneRegion( innerBitSet );

		val innerMeshData = MRJS::exportMeshMemoryView( innerMesh );
		// val outerMeshData = MRJS::exportMeshMemoryView( outerMesh );




		val obj = val::object();
		obj.set( "success", true );
		obj.set( "innerMesh", innerMeshData );
		// obj.set( "outerMesh", outerMeshData );
		obj.set( "jsTestProjectedPoint", jsTestProjectedPoint );
		obj.set( "jsTestProjectedContour", jsTestProjectedContour );
		obj.set( "jsTestCutPoints", jsTestCutPoints );

		return obj;
	} else {
		std::string error = meshContour.error();

		val obj = val::object();
		obj.set( "success", false );
		obj.set( "error", "convertMeshTriPointsToMeshContour: " + error );
	
		return obj;
	}
}

/**
 *@brief Cut and extrude mesh with polyline
 *
 * 1. Project points of polyline to mesh
 * 2. Convert result vector to `cutMesh()` input type
 * 3. Do `cutMesh()` (it works only with contours without self-intersections)
 * 4. Pull resultCut vertices to corresponding original polyline positions
 *
 * @param mesh
 * @param coordinates 
 * @param coordinatesLength 
 * @return val 
 */
BoolResults cutAndExtrudeMeshWithPolyline( Mesh * mesh, float coordinates[], int coordinatesLength )
{
	std::vector<Vector3f> polyline;
	polyline.reserve( coordinatesLength / 3 );

	for ( size_t i = 0; i < coordinatesLength; i += 3 )
	{
		polyline.emplace_back( coordinates[i], coordinates[i + 1], coordinates[i + 2] );
	}
	Polyline3 initialPolyline;
	initialPolyline.addFromPoints( polyline.data(), polyline.size() );

	// We are initializing the vector with a certain length
	std::vector<MeshTriPoint> projectedPolyline( initialPolyline.points.size() );
	const MeshPart m = MeshPart( *mesh, nullptr );
	const Vector3f vectorUp = Vector3f( 0, 0, 1 );
	// const Vector3f vectorDown = Vector3f( 0, 0, -1 );

	mesh->getAABBTree(); // Create tree in parallel before loop
	ParallelFor( initialPolyline.points, [&] ( VertId v )
	{
		const auto& pt = initialPolyline.points[v];
		auto rmi = rayMeshIntersect( m, Line3f( pt - 100 * vectorUp, vectorUp ) );

		if ( rmi ) projectedPolyline[v.get()] = rmi.mtp;
	} );

	// Make sure we weed out points which never hit the target mesh
	std::vector<MeshTriPoint> validPoints;
	std::copy_if( projectedPolyline.begin(), projectedPolyline.end(), std::back_inserter( validPoints ), [] ( const MeshTriPoint& point )
	{
		return point.e.valid();
	} );

	if ( !validPoints.empty() )
	{
		auto meshContour = convertMeshTriPointsToMeshContour( *mesh, validPoints );
		if ( meshContour ) {
			CutMeshResult cutResults = cutMesh( *mesh, { *meshContour } );

			initialPolyline.getAABBTree(); // create tree in parallel before loop
			for ( const EdgeLoop& cut : cutResults.resultCut )
			{
				ParallelFor( cut, [&] ( size_t i )
				{
					Vector3f& orgP = mesh->points[mesh->topology.org( cut[i] )];
					orgP = findProjectionOnPolyline( Line3f( orgP, vectorUp ), initialPolyline ).point;
				} );

				if ( mesh->topology.org( cut.front() ) != mesh->topology.dest( cut.back() ) )
				{
					Vector3f& destP = mesh->points[mesh->topology.dest( cut.back() )];
					destP = findProjectionOnPolyline( Line3f( destP, vectorUp ), initialPolyline ).point;
				}
			}

			// important to call after manual changing of mesh structure fields
			mesh->invalidateCaches();
		} else {
			std::string error = meshContour.error();
			// ...
		}
	}
	
	BoolResults result = BoolResults();
	result.verticesLength = mesh->topology.numValidVerts() * 3;
	result.vertices = new float[result.verticesLength];

	size_t i = 0;
	for ( auto v : mesh->topology.getValidVerts() )
	{
		result.vertices[i] = mesh->points[v].x;
		result.vertices[i + 1] = mesh->points[v].y;
		result.vertices[i + 2] = mesh->points[v].z;
		i += 3;
	}

	result.facesLength = mesh->topology.numValidFaces() * 3;
	result.faces = new int[result.facesLength];

	i = 0;
	VertId v[3];
	for ( FaceId f : mesh->topology.getFaceIds( nullptr ) )
	{
		mesh->topology.getTriVerts( f, v );
		result.faces[i] = ( uint32_t )v[0];
		result.faces[i + 1] = ( uint32_t )v[1];
		result.faces[i + 2] = ( uint32_t )v[2];
		i += 3;
	}
	
	return result;
}

EMSCRIPTEN_BINDINGS( ContoursCutModule )
{
	class_<NewEdgesMap>( "NewEdgesMap" )
        .constructor<>()
        .property( "splitEdges", &NewEdgesMap::splitEdges )
		.property( "map", &NewEdgesMap::map );
	
	enum_<CutMeshParameters::ForceFill>( "ForceFill" )
		.value( "None", CutMeshParameters::ForceFill::None )
		.value( "Good", CutMeshParameters::ForceFill::Good )
		.value( "All", CutMeshParameters::ForceFill::All );
	
	class_<CutMeshParameters>( "CutMeshParameters" )
		.constructor<>()  // for JS‐side `new`
		// .property("sortData",         &CutMeshParameters::sortData) // SortIntersectionsData*
		.property( "new2OldMap", &CutMeshParameters::new2OldMap, allow_raw_pointers() ) // FaceMap*
		.property( "forceFillMode", &CutMeshParameters::forceFillMode )
		.property( "new2oldEdgesMap", &CutMeshParameters::new2oldEdgesMap, allow_raw_pointers() ) // NewEdgesMap*
		;

	value_object<CutMeshResult>( "CutMeshResult" )
		.field( "resultCut", &CutMeshResult::resultCut )
		.field( "fbsWithContourIntersections", &CutMeshResult::fbsWithContourIntersections );

	function( "cutMeshWithPolyline", &cutMeshWithPolyline );
}
