#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFillHole.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRPlane3.h>
#include <MRMesh/MRId.h>

using namespace emscripten;
using namespace MR;

// emscripten bindings for hole extension functions
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <functional>

using namespace emscripten;

// 1. `extendHole()` with Plane3f
// Basic version without output parameter
EdgeId extendHoleBasic( Mesh& mesh, EdgeId a, const Plane3f& plane )
{
	return extendHole( mesh, a, plane, nullptr );
}
// Version with output parameter
val extendHoleWithOutput( Mesh& mesh, EdgeId a, const Plane3f& plane )
{
	FaceBitSet outNewFaces;
	EdgeId result = extendHole( mesh, a, plane, &outNewFaces );

	val returnObj = val::object();
	returnObj.set( "edgeId", result );
	returnObj.set( "newFaces", outNewFaces );

	return returnObj;
}

// 2. `extendAllHoles()`
// Basic version
std::vector<EdgeId> extendAllHolesBasic( Mesh& mesh, const Plane3f& plane )
{
	return extendAllHoles( mesh, plane, nullptr );
}
// Version with output parameter
val extendAllHoles_withOutput( Mesh& mesh, const Plane3f& plane )
{
	FaceBitSet outNewFaces;
	std::vector<EdgeId> result = extendAllHoles( mesh, plane, &outNewFaces );

	val returnObj = val::object();
	returnObj.set( "edgeIds", result );
	returnObj.set( "newFaces", outNewFaces );

	return returnObj;
}

// 3. `extendHole()` with function
// Basic version
EdgeId extendHoleFuncBasic( Mesh& mesh, EdgeId a, val jsFunc )
{
	// Convert JavaScript function to C++ function
	std::function<Vector3f( const Vector3f& )> cppFunc = [jsFunc] ( const Vector3f& pos ) -> Vector3f
	{
		val result = jsFunc( pos );
		return result.as<Vector3f>();
	};

	return extendHole( mesh, a, cppFunc, nullptr );
}
// Version with output parameter
val extendHoleFuncWithOutput( Mesh& mesh, EdgeId a, val jsFunc )
{
	std::function<Vector3f( const Vector3f& )> cppFunc = [jsFunc] ( const Vector3f& pos ) -> Vector3f
	{
		val result = jsFunc( pos );
		return result.as<Vector3f>();
	};

	FaceBitSet outNewFaces;
	EdgeId result = extendHole( mesh, a, cppFunc, &outNewFaces );

	val returnObj = val::object();
	returnObj.set( "edgeId", result );
	returnObj.set( "newFaces", outNewFaces );

	return returnObj;
}

// 4. `buildBottom()`
// Basic version
EdgeId buildBottomBasic( Mesh& mesh, EdgeId a, Vector3f dir, float holeExtension )
{
	return buildBottom( mesh, a, dir, holeExtension, nullptr );
}
// Version with output parameter
val buildBottomWithOutput( Mesh& mesh, EdgeId a, Vector3f dir, float holeExtension )
{
	FaceBitSet outNewFaces;
	EdgeId result = buildBottom( mesh, a, dir, holeExtension, &outNewFaces );

	val returnObj = val::object();
	returnObj.set( "edgeId", result );
	returnObj.set( "newFaces", outNewFaces );

	return returnObj;
}

// 5. `makeDegenerateBandAroundHole()`
// Basic version
EdgeId makeDegenerateBandAroundHoleBasic( Mesh& mesh, EdgeId a )
{
	return makeDegenerateBandAroundHole( mesh, a, nullptr );
}
// Version with output parameter
val makeDegenerateBandAroundHoleWithOutput( Mesh& mesh, EdgeId a )
{
	FaceBitSet outNewFaces;
	EdgeId result = makeDegenerateBandAroundHole( mesh, a, &outNewFaces );

	val returnObj = val::object();
	returnObj.set( "edgeId", result );
	returnObj.set( "newFaces", outNewFaces );

	return returnObj;
}

EMSCRIPTEN_BINDINGS( MeshFillHoleModule )
{
	class_<FillHoleParams>( "FillHoleParams" )
		.constructor<>()

		// TODO
		// .property( "metric", &FillHoleParams::metric )
		.property( "makeDegenerateBand", &FillHoleParams::makeDegenerateBand )
		.property( "maxPolygonSubdivisions", &FillHoleParams::maxPolygonSubdivisions );

	function( "fillHole", &fillHole );
	function( "fillHoles", &fillHoles );

	// Basic versions without output
	function( "extendHole", &extendHoleBasic );
	function( "extendAllHoles", &extendAllHolesBasic );
	function( "extendHoleWithFunc", &extendHoleFuncBasic );
	function( "buildBottom", &buildBottomBasic );
	function( "makeDegenerateBandAroundHole", &makeDegenerateBandAroundHoleBasic );

	// Versions with output parameter (returning objects with both result and new faces)
	function( "extendHoleWithOutput", &extendHoleWithOutput );
	function( "extendAllHolesWithOutput", &extendAllHoles_withOutput );
	function( "extendHoleWithFuncAndOutput", &extendHoleFuncWithOutput );
	function( "buildBottomWithOutput", &buildBottomWithOutput );
	function( "makeDegenerateBandAroundHoleWithOutput", &makeDegenerateBandAroundHoleWithOutput );
}
