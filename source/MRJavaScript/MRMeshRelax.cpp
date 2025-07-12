#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshRelax.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRVector4.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRRelaxParams.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRProgressCallback.h>
#include <MRMesh/MRRegionBoundary.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshRelaxModule )
{
	class_<MeshRelaxParams, base<RelaxParams>>( "MeshRelaxParams" )
		.constructor<>()
		.property( "hardSmoothTetrahedrons", &MeshRelaxParams::hardSmoothTetrahedrons )
		.property( "weights", &MeshRelaxParams::weights, allow_raw_pointers() );

	class_<MeshEqualizeTriAreasParams, base<MeshRelaxParams>>( "MeshEqualizeTriAreasParams" )
		.constructor<>()
		.property( "noShrinkage", &MeshEqualizeTriAreasParams::noShrinkage );

	class_<MeshApproxRelaxParams, base<MeshRelaxParams>>( "MeshApproxRelaxParams" )
		.constructor<>()
		.property( "surfaceDilateRadius", &MeshApproxRelaxParams::surfaceDilateRadius )
		.property( "type", &MeshApproxRelaxParams::type );

	function( "relax", select_overload<bool( Mesh&, const MeshRelaxParams&, const ProgressCallback& )>( &relax ) );
	function( "relaxWithTopology", select_overload<bool( const MeshTopology&, VertCoords&, const MeshRelaxParams&, const ProgressCallback& )>( &relax ) );

	function( "vertexPosEqualNeiAreas", select_overload<Vector3f( const Mesh&, VertId, bool )>( &vertexPosEqualNeiAreas ) );
	function( "vertexPosEqualNeiAreasWithTopology", select_overload<Vector3f( const MeshTopology&, const VertCoords&, VertId, bool )>( &vertexPosEqualNeiAreas ) );

	function( "equalizeTriAreas", select_overload<bool( Mesh&, const MeshEqualizeTriAreasParams&, const ProgressCallback& )>( &equalizeTriAreas ) );
	function( "equalizeTriAreasWithTopology", select_overload<bool( const MeshTopology&, VertCoords&, const MeshEqualizeTriAreasParams&, const ProgressCallback& )>( &equalizeTriAreas ) );

	function( "relaxKeepVolume", select_overload<bool( Mesh&, const MeshRelaxParams&, const ProgressCallback& )>( &relaxKeepVolume ) );
	function( "relaxKeepVolumeWithTopology", select_overload<bool( const MeshTopology&, VertCoords&, const MeshRelaxParams&, const ProgressCallback& )>( &relaxKeepVolume ) );

	function( "relaxApprox", select_overload<bool( Mesh&, const MeshApproxRelaxParams&, const ProgressCallback& )>( &relaxApprox ) );
	function( "relaxApproxWithTopology", select_overload<bool( const MeshTopology&, VertCoords&, const MeshApproxRelaxParams&, const ProgressCallback& )>( &relaxApprox ) );

	function( "removeSpikes", select_overload<void( Mesh &, int, float, const VertBitSet* )>( &removeSpikes ), allow_raw_pointers() );
	function( "removeSpikesWithTopology", select_overload<void( const MeshTopology&, VertCoords&, int, float, const VertBitSet* )>( &removeSpikes ), allow_raw_pointers() );

	function( "smoothRegionBoundary", &smoothRegionBoundary );

	function( "hardSmoothTetrahedrons", select_overload<void( Mesh &, const VertBitSet* )>( &hardSmoothTetrahedrons ), allow_raw_pointers() );
	function( "hardSmoothTetrahedrons_topology", select_overload<void( const MeshTopology&, VertCoords&,const VertBitSet* )>( &hardSmoothTetrahedrons ), allow_raw_pointers() );
}
