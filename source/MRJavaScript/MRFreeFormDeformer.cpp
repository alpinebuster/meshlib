#include <span>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRAffineXf.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRFreeFormDeformer.h>

using namespace emscripten;
using namespace MR;


std::shared_ptr<FreeFormDeformer> makeFreeFormDeformerFromMesh( Mesh& mesh, const VertBitSet* region )
{
	return std::make_shared<FreeFormDeformer>( mesh, region );
}
std::shared_ptr<FreeFormDeformer> makeFreeFormDeformerFromCoords( VertCoords& coords, const VertBitSet& valid )
{
	return std::make_shared<FreeFormDeformer>( coords, valid );
}


EMSCRIPTEN_BINDINGS( FreeFormDeformerModule )
{
	class_<FreeFormDeformer>( "FreeFormDeformer" )
		.smart_ptr<std::shared_ptr<FreeFormDeformer>>( "FreeFormDeformerSharedPtr" )

		.constructor<VertCoords&, const VertBitSet&>()
		.class_function( "createFreeFormDeformerFromMesh", &makeFreeFormDeformerFromMesh, allow_raw_pointers() )
		.class_function( "createFreeFormDeformerFromCoords", &makeFreeFormDeformerFromCoords, allow_raw_pointers() )

		.function( "init", &FreeFormDeformer::init )
		.function( "setRefGridPointPosition", &FreeFormDeformer::setRefGridPointPosition )
		.function( "getRefGridPointPosition", &FreeFormDeformer::getRefGridPointPosition, allow_raw_pointers() )
		.function( "apply", &FreeFormDeformer::apply )
		.function( "applySinglePoint", &FreeFormDeformer::applySinglePoint )
		.function( "getIndex", &FreeFormDeformer::getIndex )
		.function( "getCoord", &FreeFormDeformer::getCoord )
		.function( "getAllRefGridPositions", &FreeFormDeformer::getAllRefGridPositions, allow_raw_pointers() )
		.function( "setAllRefGridPositions", &FreeFormDeformer::setAllRefGridPositions )
		.function( "getResolution", &FreeFormDeformer::getResolution, allow_raw_pointers() );

	class_<FreeFormBestFit>( "FreeFormBestFit" )
		.constructor<const Box3d&, const Vector3i&>()

		.function( "addPaird", select_overload<void( const Vector3d&, const Vector3d&, double )>( &FreeFormBestFit::addPair ) )
		.function( "addPairf", select_overload<void( const Vector3f&, const Vector3f&, float )>( &FreeFormBestFit::addPair ) )
		.function( "addOther", &FreeFormBestFit::addOther )
		.function( "setStabilizer", &FreeFormBestFit::setStabilizer )
		.function( "getStabilizer", &FreeFormBestFit::getStabilizer )
		.function( "findBestDeformationReferenceGrid", &FreeFormBestFit::findBestDeformationReferenceGrid );


	function( "makeFreeFormOriginGrid", &makeFreeFormOriginGrid );
	function( "findBestFreeformDeformation", &findBestFreeformDeformation, allow_raw_pointers() );
}
