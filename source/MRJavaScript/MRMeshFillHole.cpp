#include <functional>

#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRPlane3.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRMeshFillHole.h>

#include "MRUtils.h"

using namespace emscripten;
using namespace MR;

// 1. `extendHole()` with Plane3f
// Basic version without output parameter
EdgeId extendHoleBasicImpl( Mesh& mesh, EdgeId a, const Plane3f& plane )
{
	return extendHole( mesh, a, plane, nullptr );
}
// Version with output parameter
val extendHoleWithOutputImpl( Mesh& mesh, EdgeId a, const Plane3f& plane )
{
	FaceBitSet outNewFaces;
	EdgeId result = extendHole( mesh, a, plane, &outNewFaces );

	int resultId = static_cast<int>( result );

	const auto& bits = outNewFaces.bits(); // Obtain the `uint64_t` block array
	auto bitsView = typed_memory_view( bits.size(), bits.data() );
	val bitsArray = val( bitsView );

	val returnObj = val::object();
	returnObj.set( "edgeId", resultId );
	returnObj.set( "newFaces", bitsArray );

	return returnObj;
}

// 2. `extendAllHoles()`
// Basic version
std::vector<EdgeId> extendAllHolesBasicImpl( Mesh& mesh, const Plane3f& plane )
{
	return extendAllHoles( mesh, plane, nullptr );
}
// Version with output parameter
val extendAllHolesWithOutputImpl( Mesh& mesh, const Plane3f& plane )
{
	FaceBitSet outNewFaces;
	std::vector<EdgeId> result = extendAllHoles( mesh, plane, &outNewFaces );

	const int* resultIds = reinterpret_cast<const int*>( result.data() );
	size_t resultIdsSize = result.size();
	val resultIdsArray = val( typed_memory_view( resultIdsSize, resultIds ) );

	const auto& bits = outNewFaces.bits(); // Obtain the `uint64_t` block array
	auto bitsView = typed_memory_view( bits.size(), bits.data() );
	val bitsArray = val( bitsView );

	val returnObj = val::object();
	returnObj.set( "edgeIds", resultIdsArray );
	returnObj.set( "newFaces", bitsArray );

	return returnObj;
}

// 3. `extendHole()` with function
// Basic version
EdgeId extendHoleWithFuncBasicImpl( Mesh& mesh, EdgeId a, val jsFunc )
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
val extendHoleWithFuncAndOutputImpl( Mesh& mesh, EdgeId a, val jsFunc )
{
	std::function<Vector3f( const Vector3f& )> cppFunc = [jsFunc] ( const Vector3f& pos ) -> Vector3f
	{
		val result = jsFunc( pos );
		return result.as<Vector3f>();
	};

	FaceBitSet outNewFaces;
	EdgeId result = extendHole( mesh, a, cppFunc, &outNewFaces );

	int resultId = static_cast<int>(result);

	const auto& bits = outNewFaces.bits(); // Obtain the `uint64_t` block array
	auto bitsView = typed_memory_view( bits.size(), bits.data() );
	val bitsArray = val( bitsView );

	val returnObj = val::object();
	returnObj.set( "edgeId", resultId );
	returnObj.set( "newFaces", bitsArray );

	return returnObj;
}

// 4. `buildBottom()`
// Basic version
EdgeId buildBottomBasicImpl( Mesh& mesh, EdgeId a, Vector3f dir, float holeExtension )
{
	return buildBottom( mesh, a, dir, holeExtension, nullptr );
}
// Version with output parameter
val buildBottomWithOutput( Mesh& mesh, EdgeId a, Vector3f dir, float holeExtension )
{
	FaceBitSet outNewFaces;
	EdgeId result = buildBottom( mesh, a, dir, holeExtension, &outNewFaces );

	int resultId = static_cast<int>(result);
	
	const auto& bits = outNewFaces.bits(); // Obtain the `uint64_t` block array
	auto bitsView = typed_memory_view( bits.size(), bits.data() );
	val bitsArray = val( bitsView );

	val returnObj = val::object();
	returnObj.set( "edgeId", resultId );
	returnObj.set( "newFaces", bitsArray );

	return returnObj;
}

// 5. `makeDegenerateBandAroundHole()`
// Basic version
EdgeId makeDegenerateBandAroundHoleBasicImpl( Mesh& mesh, EdgeId a )
{
	return makeDegenerateBandAroundHole( mesh, a, nullptr );
}
// Version with output parameter
val makeDegenerateBandAroundHoleWithOutputImpl( Mesh& mesh, EdgeId a )
{
	FaceBitSet outNewFaces;
	EdgeId result = makeDegenerateBandAroundHole( mesh, a, &outNewFaces );

	int resultId = static_cast<int>(result);

	const auto& bits = outNewFaces.bits(); // Obtain the `uint64_t` block array
	auto bitsView = typed_memory_view( bits.size(), bits.data() );
	val bitsArray = val( bitsView );

	val returnObj = val::object();
	returnObj.set( "edgeId", resultId );
	returnObj.set( "newFaces", bitsArray );

	return returnObj;
}

val fillHolesImpl( Mesh& mesh )
{
	auto holeEdges = mesh.topology.findHoleRepresentiveEdges();

	for ( EdgeId e : holeEdges )
	{
		FillHoleParams params;
		fillHole( mesh, e, params );
	}

	val meshData = MRJS::exportMeshMemoryView( mesh );

	val geoObj = val::object();
	geoObj.set( "success", true );
	geoObj.set( "mesh", meshData );

	return geoObj;
}


EMSCRIPTEN_BINDINGS( MeshFillHoleModule )
{
    enum_<FillHoleParams::MultipleEdgesResolveMode>( "MultipleEdgesResolveMode" )
        .value( "None", FillHoleParams::MultipleEdgesResolveMode::None )
        .value( "Simple", FillHoleParams::MultipleEdgesResolveMode::Simple )
        .value( "Strong", FillHoleParams::MultipleEdgesResolveMode::Strong );
	
	class_<FillHoleParams>( "FillHoleParams" )
		.constructor<>()

		.property( "metric", &FillHoleParams::metric )
		.property( "outNewFaces", &FillHoleParams::outNewFaces, return_value_policy::reference() )
		.property( "multipleEdgesResolveMode", &FillHoleParams::multipleEdgesResolveMode )
		.property( "makeDegenerateBand", &FillHoleParams::makeDegenerateBand )
		.property( "maxPolygonSubdivisions", &FillHoleParams::maxPolygonSubdivisions )

		.function( "getStopBeforeBadTriangulation", optional_override( [] ( FillHoleParams& self )
		{
			if ( !self.stopBeforeBadTriangulation ) throw std::runtime_error( "stopBeforeBadTriangulation is null" );
			return *self.stopBeforeBadTriangulation;
		}))
		.function( "setStopBeforeBadTriangulation", optional_override( [] ( FillHoleParams& self, bool v )
		{
			if ( !self.stopBeforeBadTriangulation ) self.stopBeforeBadTriangulation = new bool;
			*self.stopBeforeBadTriangulation = v;
		}));

	class_<StitchHolesParams>( "StitchHolesParams" )
		.constructor<>()

		.property( "metric", &StitchHolesParams::metric )
		.property( "outNewFaces", &StitchHolesParams::outNewFaces, return_value_policy::reference() );

	
	value_object<FillHoleItem>( "FillHoleItem" )
		.field( "edgeCode1", &FillHoleItem::edgeCode1 )
		.field( "edgeCode2", &FillHoleItem::edgeCode2 );

	value_object<HoleFillPlan>( "HoleFillPlan" )
		.field( "items", &HoleFillPlan::items )
		.field( "numTris", &HoleFillPlan::numTris );

	class_<MakeBridgeResult>( "MakeBridgeResult" )
		.constructor<>()

		.property( "newFaces", &MakeBridgeResult::newFaces )
		.property( "na", &MakeBridgeResult::na )
		.property( "nb", &MakeBridgeResult::nb )

        .function( "opbool", select_overload<bool() const>( &MakeBridgeResult::operator bool ) );


	///
	function( "buildCylinderBetweenTwoHolesWithEdges", select_overload<void( Mesh&, EdgeId, EdgeId, const StitchHolesParams& )>( &buildCylinderBetweenTwoHoles ) );
	function( "buildCylinderBetweenTwoHoles", select_overload<bool( Mesh&, const StitchHolesParams& )>( &buildCylinderBetweenTwoHoles ) );

	function( "fillHole", &fillHole );
	function( "fillHoles", &fillHoles );

	function( "isHoleBd", &isHoleBd );
	function( "getHoleFillPlan", &getHoleFillPlan );
	function( "getHoleFillPlans", &getHoleFillPlans );
	function( "getPlanarHoleFillPlan", &getPlanarHoleFillPlan );
	function( "getPlanarHoleFillPlans", &getPlanarHoleFillPlans );

	function( "executeHoleFillPlan", &executeHoleFillPlan, allow_raw_pointers() );
	function( "fillHoleTrivially", &fillHoleTrivially, allow_raw_pointers() );

	function( "extendHole", select_overload<EdgeId( Mesh&, EdgeId, const Plane3f &, FaceBitSet * )>( &extendHole ), allow_raw_pointers() );
	function( "extendAllHoles", &extendAllHoles, allow_raw_pointers() );
	function( "extendHoleWithFunctor", select_overload<EdgeId( Mesh&, EdgeId, std::function<Vector3f(const Vector3f &)>, FaceBitSet * )>( &extendHole ), allow_raw_pointers() );

	function( "buildBottom", &buildBottom, allow_raw_pointers() );
	function( "makeDegenerateBandAroundHole", &makeDegenerateBandAroundHole, allow_raw_pointers() );

	function( "makeQuadBridge", &makeQuadBridge, allow_raw_pointers() );
	function( "makeBridge", &makeBridge, allow_raw_pointers() );
	function( "makeSmoothBridge", &makeSmoothBridge, allow_raw_pointers() );
	function( "makeBridgeEdge", &makeBridgeEdge );
	function( "splitQuad", &splitQuad, allow_raw_pointers() );
	///


	///
	function( "fillHolesImpl", &fillHolesImpl );

	// Basic versions without output
	function( "extendHoleBasicImpl", &extendHoleBasicImpl );
	function( "extendAllHolesBasicImpl", &extendAllHolesBasicImpl );
	function( "extendHoleWithFuncBasicImpl", &extendHoleWithFuncBasicImpl );
	function( "buildBottomBasicImpl", &buildBottomBasicImpl );
	function( "makeDegenerateBandAroundHoleBasicImpl", &makeDegenerateBandAroundHoleBasicImpl );

	// Versions with output parameter (returning objects with both result and new faces)
	function( "extendHoleWithOutputImpl", &extendHoleWithOutputImpl );
	function( "extendAllHolesWithOutputImpl", &extendAllHolesWithOutputImpl );
	function( "extendHoleWithFuncAndOutputImpl", &extendHoleWithFuncAndOutputImpl );
	function( "buildBottomWithOutput", &buildBottomWithOutput );
	function( "makeDegenerateBandAroundHoleWithOutputImpl", &makeDegenerateBandAroundHoleWithOutputImpl );
	///
}
