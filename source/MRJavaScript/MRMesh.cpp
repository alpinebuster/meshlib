#include <string>
#include <vector>
#include <memory>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRExpected.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRVectorTraits.h>
#include <MRMesh/MRMeshFillHole.h>
#include <MRMesh/MRSurroundingContour.h>
#include <MRMesh/MRFillContourByGraphCut.h>
#include <MRMesh/MREdgeMetric.h>
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
#include <MRMesh/MREnums.h>
#include <MRMesh/MRSignDetectionMode.h>
#include <MRMesh/MRMeshBuilder.h>
#include <MRMesh/MRMeshFillHole.h>
#include <MRMesh/MRMeshSubdivide.h>
#include <MRMesh/MRPositionVertsSmoothly.h>
#include <MRMesh/MRRegionBoundary.h>
#include <MRMesh/MRPolyline.h>
#include <MRMesh/MRTimer.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRAABBTree.h>
#include <MRMesh/MRAABBTreePoints.h>
#include <MRMesh/MRBuffer.h>
#include <MRMesh/MRPartMapping.h>

#include <MRVoxels/MRFixUndercuts.h>
#include <MRVoxels/MROffset.h>

#include "MRMesh.h"
#include "MRUtils.h"
#include "MREdgeMetric.h"

using namespace emscripten;
using namespace MR;

namespace MRJS
{

EMSCRIPTEN_BINDINGS( MeshModule )
{
	// ------------------------------------------------------------------------
	// Bindings for `Mesh`
	// ------------------------------------------------------------------------
	class_<Mesh>( "Mesh" )
		.smart_ptr<std::shared_ptr<Mesh>>( "Mesh" )

		.constructor<>()

		.property( "topology", &Mesh::topology )
		.property( "points", &Mesh::points )

		.function( "volume", &Mesh::volume, allow_raw_pointers() )
		.function( "normalWithFaceId", select_overload<Vector3f ( const FaceId ) const>( &Mesh::normal ))
		.function( "normalWithMeshTriPoint", select_overload<Vector3f ( VertId ) const>( &Mesh::normal ))
		.function( "normal", select_overload<Vector3f ( const MeshTriPoint & ) const>( &Mesh::normal ))

		.function( "getBoundingBox", &Mesh::getBoundingBox )
		.function( "computeBoundingBoxWithFaceBitSet", select_overload<Box3f ( const AffineXf3f * ) const>( &Mesh::computeBoundingBox ), allow_raw_pointers() )
		.function( "computeBoundingBox", select_overload<Box3f ( const FaceBitSet*, const AffineXf3f* ) const>( &Mesh::computeBoundingBox ), allow_raw_pointers() )
		.function( "transform", &Mesh::transform, allow_raw_pointers() )
		.function( "addPoint", &Mesh::addPoint )
		.function( "addSeparateEdgeLoop", &Mesh::addSeparateEdgeLoop )
		.function( "addSeparateContours", &Mesh::addSeparateContours, allow_raw_pointers() )
		.function( "attachEdgeLoopPart", &Mesh::attachEdgeLoopPart )
	
		.function( "addMeshWithPartMapping", select_overload<void( const Mesh&, PartMapping, bool )>( &Mesh::addMesh ) )
		.function( "addMesh", select_overload<void (const Mesh &, FaceMap *, VertMap *, WholeEdgeMap *, bool)>( &Mesh::addMesh ), allow_raw_pointers())
		.function( "addMeshPartWithPartMapping", select_overload<void ( const MeshPart &, const PartMapping& )>( &Mesh::addMeshPart ))
		.function( "addMeshPart", select_overload<void ( const MeshPart &, bool,
        const std::vector<EdgePath> &, const std::vector<EdgePath> &, PartMapping )>( &Mesh::addMeshPart ))
		.function( "cloneRegion", &Mesh::cloneRegion )
		
		.function( "packWithPartMapping", select_overload<void( const PartMapping&, bool )>( &Mesh::pack ) )
		.function( "packWithMap", select_overload<void( FaceMap*, VertMap*, WholeEdgeMap*, bool )>( &Mesh::pack ), allow_raw_pointers() )
		// .function( "pack", &Mesh::pack )

		// FIXME: `copy constructor of 'PackMapping' is implicitly deleted because field 'e' has a deleted copy constructor`
		// .function( "packOptimally", select_overload<PackMapping( bool )>( &Mesh::packOptimally ) )
		.function( "deleteFaces", &Mesh::deleteFaces, allow_raw_pointers() )
		
		.function( "projectPointWithPointOnFace", select_overload<bool( const Vector3f&, PointOnFace&, float, const FaceBitSet*, const AffineXf3f* ) const>( &Mesh::projectPoint ), allow_raw_pointers() )
		.function( "projectPointWithProjectionResult", select_overload<bool ( const Vector3f&, MeshProjectionResult&, float, const FaceBitSet*, const AffineXf3f * ) const>( &Mesh::projectPoint ), allow_raw_pointers() )
		.function( "projectPoint", select_overload<MeshProjectionResult ( const Vector3f&, float, const FaceBitSet *, const AffineXf3f * ) const>( &Mesh::projectPoint ), allow_raw_pointers() )
		.function( "findClosestPointWithProjectionResult", select_overload<bool ( const Vector3f&, MeshProjectionResult&, float, const FaceBitSet*, const AffineXf3f * ) const>( &Mesh::findClosestPoint ), allow_raw_pointers() )
		.function( "findClosestPoint", select_overload<MeshProjectionResult ( const Vector3f&, float, const FaceBitSet *, const AffineXf3f * ) const>( &Mesh::findClosestPoint ), allow_raw_pointers() )

		// FIXME
		// .function( "getAABBTree", &Mesh::getAABBTree, return_value_policy::reference() ) // <- Causes error
		.function( "getAABBTreeNotCreate", &Mesh::getAABBTreeNotCreate, allow_raw_pointers() )
		// .function( "getAABBTreePoints", &Mesh::getAABBTreePoints, allow_raw_pointers() ) // <- Causes error
		.function( "getAABBTreePointsNotCreate", &Mesh::getAABBTreePointsNotCreate, allow_raw_pointers() )
		.function( "getDipolesNotCreate", &Mesh::getDipolesNotCreate, allow_raw_pointers() )
		.function( "invalidateCaches", &Mesh::invalidateCaches )
		.function( "updateCaches", &Mesh::updateCaches )
		.function( "heapBytes", &Mesh::heapBytes )
		.function( "shrinkToFit", &Mesh::shrinkToFit )
		.function( "mirror", &Mesh::mirror )
		.function( "signedDistance", select_overload<float( const Vector3f& ) const>( &Mesh::signedDistance ) );

	function( "computeVertexNormals", +[] ( const Mesh& mesh )
	{
		std::vector<Vector3f> normals;
		for ( VertId v{ 0 }; v < mesh.topology.vertSize(); ++v )
		{
			if ( mesh.topology.hasVert( v ) )
			{
				normals.push_back( mesh.normal( v ) );
			}
		}
		
		return MRJS::vector3fToFloat32Array( normals );
	} );
}


// Helper function to create Vector3f from JavaScript array
Vector3f arrayToVector3f( const val& arr )
{
	return Vector3f( arr[0].as<float>(), arr[1].as<float>(), arr[2].as<float>() );
}

// Helper function to convert Vector3f to JavaScript array
val vector3fToArray( const Vector3f& v )
{
	val arr = val::array();
	arr.set( 0, v.x );
	arr.set( 1, v.y );
	arr.set( 2, v.z );
	return arr;
}

// Helper function to convert Box3F to JavaScript object
val box3fToObject( const Box<Vector3<float>>& box )
{
	val obj = val::object();
	obj.set( "min", vector3fToArray( box.min ) );
	obj.set( "max", vector3fToArray( box.max ) );
	return obj;
}


// ------------------------------------------------------------------------
// Wrapper for `Mesh`
// ------------------------------------------------------------------------
MeshWrapper::MeshWrapper( const Mesh& m ) : mesh( m ) {}

Mesh* MeshWrapper::getMeshPtr() { return &mesh; }

// Static factory methods for creating meshes from various sources
val MeshWrapper::fromTrianglesImpl( const val& vertexCoords, const val& triangles )
{
	try
	{
		// Convert JavaScript arrays to C++ vectors
		VertCoords coords;
		int numVerts = vertexCoords["length"].as<int>();
		coords.resize( numVerts );

		for ( int i = 0; i < numVerts; ++i )
		{
			val vertex = vertexCoords[i];
			coords[VertId( i )] = arrayToVector3f( vertex );
		}

		// Convert triangles array
		Triangulation triangulation;
		int numTris = triangles["length"].as<int>();

		for ( int i = 0; i < numTris; ++i )
		{
			val tri = triangles[i];
			triangulation.push_back( {
				VertId( tri[0].as<int>() ),
				VertId( tri[1].as<int>() ),
				VertId( tri[2].as<int>() )
			} );
		}

		auto mesh = Mesh::fromTriangles( std::move( coords ), triangulation );
		val result = val::object();
		result.set( "success", true );
		result.set( "mesh", MeshWrapper( mesh ) );

		return result;
	}
	catch ( const std::exception& e )
	{
		val result = val::object();
		result.set( "success", false );
		result.set( "error", std::string( e.what() ) );

		return result;
	}
}
// val MeshWrapper::fromTrianglesMemoryView( const float* vertexPtr,
// 										  size_t        numVerts,
// 										  const uint32_t* triPtr,
// 										  size_t         numTris )
// {

// }

// Geometric queries
val MeshWrapper::getBoundingBox() const
{
	return box3fToObject( mesh.getBoundingBox() );
}

val MeshWrapper::getVertexPosition( int vertId ) const
{
	if ( vertId >= 0 && vertId < ( int )mesh.points.size() )
	{
		return vector3fToArray( mesh.points[VertId( vertId )] );
	}
	return val::null();
}

void MeshWrapper::setVertexPosition( int vertId, const val& position )
{
	if ( vertId >= 0 && vertId < ( int )mesh.points.size() )
	{
		mesh.points[VertId( vertId )] = arrayToVector3f( position );
		mesh.invalidateCaches(); // Important: invalidate caches after modification
	}
}

int MeshWrapper::getVertexCount() const
{
	return ( int )mesh.topology.lastValidVert() + 1;
}

int MeshWrapper::getFaceCount() const
{
	return ( int )mesh.topology.lastValidFace() + 1;
}

double MeshWrapper::getVolume() const
{
	return mesh.volume();
}

double MeshWrapper::getArea() const
{
	return mesh.area();
}

val MeshWrapper::findCenter() const
{
	return vector3fToArray( mesh.findCenterFromBBox() );
}

// Face operations
val MeshWrapper::getFaceVertices( int faceId ) const
{
	if ( faceId >= 0 && faceId < ( int )mesh.topology.lastValidFace() + 1 )
	{
		FaceId f( faceId );
		if ( mesh.topology.hasFace( f ) )
		{
			val result = val::array();
			EdgeId e = mesh.topology.edgeWithLeft( f );

			for ( int i = 0; i < 3; ++i )
			{ // Assuming triangular faces
				result.set( i, ( int )mesh.topology.org( e ) );
				e = mesh.topology.next( e );
			}
			return result;
		}
	}
	return val::null();
}

val MeshWrapper::getFaceNormal( int faceId ) const
{
	if ( faceId >= 0 && faceId < ( int )mesh.topology.lastValidFace() + 1 )
	{
		FaceId f( faceId );
		if ( mesh.topology.hasFace( f ) )
		{
			return vector3fToArray( mesh.normal( f ) );
		}
	}
	return val::null();
}

val MeshWrapper::segmentByPointsImpl(
	const std::vector<float>& coordinates, const std::vector<float>& dir,
	const EdgeMetricWrapper& edgeMetricWrapper )
{
	val result = val::object();

	// TODO: More performance gains? 
	Mesh meshCopy;
	meshCopy.topology = mesh.topology;
	meshCopy.points = mesh.points;

	// Input validation
	if ( meshCopy.points.empty() )
	{
		result.set( "success", false );
		result.set( "error", std::string( "Mesh not initialized!" ) );

		return result;
	}

	try
	{
		auto edgeMetric_ = edgeMetricWrapper.getMetric();
		// Parse coordinates into Vector3f points
		std::vector<Vector3f> inputPoints = MRJS::parseJSCoordinates( coordinates );

		if ( inputPoints.size() < 2 )
		{
			result.set( "success", false );
			result.set( "error", std::string( "Segmenting mesh needs exactly 2 or 3 input points!" ) );

			return result;
		}

		// Step 1: Find closest vertices on the mesh for each input point using `findProjection()`
		std::vector<VertId> keyVertices;
		keyVertices.reserve( inputPoints.size() );

		MeshPart m = MeshPart( meshCopy );

		meshCopy.getAABBTree();
		for ( const Vector3f& point : inputPoints )
		{
			MeshProjectionResult closestVert = findProjection( point, m );
			if ( !closestVert.valid() )
			{
				result.set( "success", false );
				result.set( "error", std::string( "Could not find valid vertex for input point" ) );

				return result;
			}
			keyVertices.push_back( meshCopy.getClosestVertex( closestVert.proj ) );
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

		// Step 3: Create surrounding contour
		auto contourResult = surroundingContour( meshCopy, keyVertices, edgeMetric_, contourDirection );

		if ( !contourResult )
		{
			result.set( "success", false );
			result.set( "error", std::string( "Failed to create surrounding contour: " ) + contourResult.error() );

			return result;
		}

		// Step 4: Convert EdgeLoop to EdgePath for `fillContourLeftByGraphCut()`
		EdgeLoop contour = contourResult.value();
		EdgePath contourPath( contour.begin(), contour.end() );

		// Step 5: Fill the contour to get the segmented region
		Mesh segMesh;
		FaceBitSet segmentedFaces = fillContourLeftByGraphCut( meshCopy.topology, contourPath, edgeMetric_ );
		segMesh.addMeshPart( {meshCopy, &segmentedFaces} );

		// Step 6: Convert results to JavaScript-friendly format using emscripten val
		val meshData = MRJS::exportMeshMemoryView( segMesh );

		// FIXME: `Uint32Array` error for threejs
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

val MeshWrapper::thickenMeshImpl( float offset, GeneralOffsetParameters &params )
{
	// Return the mesh wrapped in an object that indicates success
	val returnObj = val::object();
	
	// TODO: More performance gains? 
	Mesh meshCopy;
	meshCopy.addMeshPart( mesh );

	MeshBuilder::uniteCloseVertices( meshCopy, meshCopy.computeBoundingBox().diagonal() * 1e-6 );
	auto result = thickenMesh( mesh, offset, params );
	if ( result )
	{
		Mesh& shell = result.value();

		///

		// // Stitch boundaries 
		// auto holes = shell.topology.findHoleRepresentiveEdges();
		// if ( holes.size() != 2 )
		// {
		// 	returnObj.set( "success", false );

		// 	std::string errorMessage = "Expected 2 holes, found " + std::to_string( holes.size() ) + "\n";
		// 	returnObj.set( "error: ", errorMessage );
		// 	return returnObj;
		// }

		///

		// Find boundary holes
		auto holes = findRightBoundary( shell.topology );
		std::vector<float> holesLength( holes.size() );
		std::vector<Vector3f> holeCenters( holes.size() );

		for ( size_t i = 0; i < holes.size(); ++i )
		{
			float length = 0.0f;
			Vector3f center;
			for ( EdgeId e : holes[i] )
			{
				auto org = shell.topology.org( e );
				auto dest = shell.topology.dest( e );
				length += ( shell.points[dest] - shell.points[org] ).length();
				center += shell.points[org];
			}
			holesLength[i] = length;
			holeCenters[i] = center / float( holes[i].size() );
		}

		// Find largest two holes
		int maxLengthI = 0, maxLengthI2 = -1;
		float maxLength = -1.0f;
		for ( int i = 0; i < holesLength.size(); ++i )
		{
			if ( holesLength[i] > maxLength )
			{
				maxLength = holesLength[i];
				maxLengthI = i;
			}
		}

		maxLength = -1.0f;
		for ( int i = 0; i < holesLength.size(); ++i )
		{
			if ( i != maxLengthI && holesLength[i] > maxLength )
			{
				maxLength = holesLength[i];
				maxLengthI2 = i;
			}
		}

		// Build hole pairs
		std::vector<std::array<int, 2>> holePairs;
		if ( maxLengthI2 != -1 )
			holePairs.push_back( { maxLengthI, maxLengthI2 } );

		// Find nearest pairs for remaining holes
		std::vector<int> minDistancesI( holes.size(), -1 );
		for ( int i = 0; i < holes.size(); ++i )
		{
			if ( i == maxLengthI || i == maxLengthI2 )
				continue;

			float minDist = std::numeric_limits<float>::max();
			int minJ = -1;

			for ( int j = 0; j < holes.size(); ++j )
			{
				if ( j == i || j == maxLengthI || j == maxLengthI2 )
					continue;

				float dist = ( holeCenters[i] - holeCenters[j] ).length();
				if ( dist < minDist )
				{
					minDist = dist;
					minJ = j;
				}
			}
			minDistancesI[i] = minJ;
		}

		for ( int i = 0; i < holes.size() / 2; ++i )
		{
			if ( minDistancesI[i] != -1 )
				holePairs.push_back( { i, minDistancesI[i] } );
		}

		// Stitch holes with cylinders
		FaceBitSet newFaces;
		StitchHolesParams stitchParams;
		stitchParams.metric = getMinAreaMetric( shell );
		stitchParams.outNewFaces = &newFaces;

		for ( const auto& pair : holePairs )
		{
			if ( pair[0] < holes.size() && pair[1] < holes.size() )
			{
				if ( !holes[pair[0]].empty() && !holes[pair[1]].empty() )
					buildCylinderBetweenTwoHoles( shell, holes[pair[0]][0], holes[pair[1]][0], stitchParams );
			}
		}

		// Subdivide new faces
		SubdivideSettings subdivSettings;
		subdivSettings.region = &newFaces;
		subdivSettings.maxEdgeSplits = INT_MAX;
		subdivSettings.maxEdgeLen = 1.0f;

		subdivideMesh( shell, subdivSettings );

		// Smooth vertices
		auto smoothVerts = getInnerVerts( shell.topology, newFaces );
		positionVertsSmoothly( shell, smoothVerts );


		val meshData = MRJS::exportMeshMemoryView( shell );

		returnObj.set( "success", true );
		returnObj.set( "mesh", meshData );

		return returnObj;
	}
	else
	{
		// Return an error object with the error message
		val returnObj = val::object();
		returnObj.set( "success", false );
		returnObj.set( "error", result.error() );

		return returnObj;
	}
}

val MeshWrapper::cutMeshWithPolylineImpl( const std::vector<float>& coordinates )
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
		auto [innerMesh, outerMesh] = MRJS::returnParts( mesh, cutResults.resultCut );
		val innerMeshData = MRJS::exportMeshMemoryView( innerMesh );
		val outerMeshData = MRJS::exportMeshMemoryView( outerMesh );


		val obj = val::object();
		obj.set( "success", true );
		obj.set( "innerMesh", innerMeshData );
		obj.set( "outerMesh", outerMeshData );
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

val MeshWrapper::fixUndercutsImpl( const Vector3f& upDirection ) const
{
	val returnObj = val::object();

	FixUndercuts::FixParams fixParams;
	fixParams.findParameters.upDirection = upDirection.normalized();

	// TODO: More performance gains? 
	Mesh meshCopy;
	meshCopy.topology = mesh.topology;
	meshCopy.points = mesh.points;
	// meshCopy.addMeshPart( mesh );
	
	auto result = FixUndercuts::fix( meshCopy, fixParams );

	val meshData = MRJS::exportMeshMemoryView( meshCopy );
	returnObj.set( "success", true );
	returnObj.set( "mesh", meshData );
	returnObj.set( "message", "Undercuts fixed successfully!" );

    return returnObj;
}

val MeshWrapper::fillHolesImpl() const
{
	auto holeEdges = mesh.topology.findHoleRepresentiveEdges();
	// TODO: More performance gains? 
	Mesh meshCopy;
	meshCopy.topology = mesh.topology;
	meshCopy.points = mesh.points;

	for ( EdgeId e : holeEdges )
	{
		FillHoleParams params;
		fillHole( meshCopy, e, params );
	}

    return MRJS::exportMeshMemoryView( meshCopy );
}

// Point projection
val MeshWrapper::projectPoint( const val& point, float maxDistance ) const
{
	Vector3f p = arrayToVector3f( point );
	MeshProjectionResult result = mesh.projectPoint( p, maxDistance * maxDistance ); // Note: function expects squared distance

	if ( result.valid() )
	{
		val obj = val::object();
		obj.set( "success", true );
		// obj.set( "point", vector3fToArray( result.proj ) );
		// obj.set( "faceId", ( int )result->face );
		// obj.set( "distance", std::sqrt( result->distSq ) );
		return obj;
	}
	else
	{
		val result = val::object();
		result.set( "success", false );
		result.set( "error", "No projection found within distance" );

		return result;
	}
}

// Transformation
void MeshWrapper::transform( const val& matrix )
{
	// Assuming 4x4 transformation matrix as flat array of 16 elements
	if ( matrix["length"].as<int>() == 16 )
	{
		AffineXf3f xf;
		// Fill transformation matrix from JavaScript array
		for ( int i = 0; i < 4; ++i )
		{
			for ( int j = 0; j < 4; ++j )
			{
				if ( i < 3 && j < 3 )
				{
					xf.A[i][j] = matrix[i * 4 + j].as<float>();
				}
				else if ( i < 3 && j == 3 )
				{
					xf.b[i] = matrix[i * 4 + j].as<float>();
				}
			}
		}
		mesh.transform( xf );
	}
}

// Pack mesh (optimize memory layout)
void MeshWrapper::pack()
{
	mesh.pack();
}


EMSCRIPTEN_BINDINGS( MeshWrapperModule )
{
	// ------------------------------------------------------------------------
	// Bindings for `MeshWrapper`
	// ------------------------------------------------------------------------
	class_<MeshWrapper>( "MeshWrapper" )
		.smart_ptr<std::shared_ptr<MeshWrapper>>( "MeshWrapper" )

		.constructor<>()
		.constructor<const Mesh&>()
		.class_function( "fromTrianglesImpl", &MeshWrapper::fromTrianglesImpl )

		.property( "mesh", &MeshWrapper::mesh, return_value_policy::reference() )
		.function( "getMesh", &MeshWrapper::getMeshPtr, allow_raw_pointers() )

		// Geometric properties
		.function( "getBoundingBox", &MeshWrapper::getBoundingBox )
		.function( "getVertexCount", &MeshWrapper::getVertexCount )
		.function( "getFaceCount", &MeshWrapper::getFaceCount )
		.function( "getVolume", &MeshWrapper::getVolume )
		.function( "getArea", &MeshWrapper::getArea )
		.function( "findCenter", &MeshWrapper::findCenter )

		// Vertex operations
		.function( "getVertexPosition", &MeshWrapper::getVertexPosition )
		.function( "setVertexPosition", &MeshWrapper::setVertexPosition )

		// Face operations
		.function( "getFaceVertices", &MeshWrapper::getFaceVertices )
		.function( "getFaceNormal", &MeshWrapper::getFaceNormal )

		.function( "thickenMeshImpl", &MeshWrapper::thickenMeshImpl)
		.function( "cutMeshWithPolylineImpl", &MeshWrapper::cutMeshWithPolylineImpl )
		.function( "segmentByPointsImpl", &MeshWrapper::segmentByPointsImpl )
		.function( "fixUndercutsImpl", &MeshWrapper::fixUndercutsImpl )
		.function( "fillHolesImpl", &MeshWrapper::fillHolesImpl )

		// Spatial queries
		.function( "projectPoint", &MeshWrapper::projectPoint )

		// Transformations
		.function( "transform", &MeshWrapper::transform )
		.function( "pack", &MeshWrapper::pack );
}

} //namespace MRJS
