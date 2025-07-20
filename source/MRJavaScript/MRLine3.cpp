#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRLine3.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRLine.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( Line3Module )
{
	class_<Line3f>( "Line3f" )
		.constructor<>()
		.constructor<const Vector3f&, const Vector3f&>()

		.property( "p", &Line3f::p )
		.property( "d", &Line3f::d )
	
		.function( "project", &Line3f::project )
		.function( "normalized", &Line3f::normalized )
		.function( "distanceSq", &Line3f::distanceSq )
		.function( "opcall", &Line3f::operator() );

	class_<Line3d>( "Line3d" )
		.constructor<>()
		.constructor<const Vector3d&, const Vector3d&>()
		
		.property( "p", &Line3d::p )
		.property( "d", &Line3d::d )

		.function( "project", &Line3d::project )
		.function( "normalized", &Line3d::normalized )
		.function( "distanceSq", &Line3d::distanceSq )
		.function( "opcall", &Line3d::operator() );
}
