#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshSubdivide.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshSubdivideModule )
{
	class_<SubdivideSettings>( "SubdivideSettings" )
		.constructor<>()

		.property( "maxEdgeLen", &SubdivideSettings::maxEdgeLen )
		.property( "maxEdgeSplits", &SubdivideSettings::maxEdgeSplits )
		.property( "maxDeviationAfterFlip", &SubdivideSettings::maxDeviationAfterFlip )
		.property( "maxAngleChangeAfterFlip", &SubdivideSettings::maxAngleChangeAfterFlip )
		.property( "criticalAspectRatioFlip", &SubdivideSettings::criticalAspectRatioFlip )
		.property( "region", &SubdivideSettings::region, return_value_policy::reference() )
		.property( "notFlippable", &SubdivideSettings::notFlippable, return_value_policy::reference() )
		.property( "newVerts", &SubdivideSettings::newVerts, return_value_policy::reference() )
		.property( "subdivideBorder", &SubdivideSettings::subdivideBorder )
		.property( "maxTriAspectRatio", &SubdivideSettings::maxTriAspectRatio )
		.property( "maxSplittableTriAspectRatio", &SubdivideSettings::maxSplittableTriAspectRatio )
		.property( "smoothMode", &SubdivideSettings::smoothMode )
		.property( "minSharpDihedralAngle", &SubdivideSettings::minSharpDihedralAngle )
		.property( "projectOnOriginalMesh", &SubdivideSettings::projectOnOriginalMesh );
}
