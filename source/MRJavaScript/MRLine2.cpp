#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRLine.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( Line2Module )
{
	class_<Line2f>( "Line2f" )
		.constructor<>()
		.constructor<const Vector2f&, const Vector2f&>()

		.property( "p", &Line2f::p )
		.property( "d", &Line2f::d )

		.function( "project", &Line2f::project )
		.function( "normalized", &Line2f::normalized )
		.function( "distanceSq", &Line2f::distanceSq )
		.function( "opcall", &Line2f::operator() );

	class_<Line2d>( "Line2d" )
		.constructor<>()
		.constructor<const Vector2d&, const Vector2d&>()

		.property( "p", &Line2d::p )
		.property( "d", &Line2d::d )

		.function( "project", &Line2d::project )
		.function( "normalized", &Line2d::normalized )
		.function( "distanceSq", &Line2d::distanceSq )
		.function( "opcall", &Line2d::operator() );
}
