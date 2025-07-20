#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshSubdivide.h>
#include <MRMesh/MRPositionVertsSmoothly.h>
#include <MRMesh/MRMeshComponents.h>
#include <MRMesh/MRFillHoleNicely.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( FillHoleNicelyModule )
{
	class_<FillHoleNicelySettings>( "FillHoleNicelySettings" )
		.constructor<>()

		.property( "triangulateParams", &FillHoleNicelySettings::triangulateParams )
		.property( "triangulateOnly", &FillHoleNicelySettings::triangulateOnly )
		.property( "maxEdgeLen", &FillHoleNicelySettings::maxEdgeLen )
		.property( "maxEdgeSplits", &FillHoleNicelySettings::maxEdgeSplits )
		.property( "maxAngleChangeAfterFlip", &FillHoleNicelySettings::maxAngleChangeAfterFlip )
		.property( "smoothCurvature", &FillHoleNicelySettings::smoothCurvature )
		.property( "naturalSmooth", &FillHoleNicelySettings::naturalSmooth )
		.property( "beforeEdgeSplit", &FillHoleNicelySettings::beforeEdgeSplit )
		.property( "onEdgeSplit", &FillHoleNicelySettings::onEdgeSplit )
		.property( "edgeWeights", &FillHoleNicelySettings::edgeWeights )
		.property( "vmass", &FillHoleNicelySettings::vmass )
		.property( "uvCoords", &FillHoleNicelySettings::uvCoords, allow_raw_pointers() )
		.property( "colorMap", &FillHoleNicelySettings::colorMap, allow_raw_pointers() )
		.property( "faceColors", &FillHoleNicelySettings::faceColors, allow_raw_pointers() );

	function( "fillHoleNicely", &fillHoleNicely );
}
