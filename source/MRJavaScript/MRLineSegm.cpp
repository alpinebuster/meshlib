#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRLine.h>
#include <MRMesh/MRLineSegm.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( LineSegmModule )
{
	///
	class_<LineSegm2f>( "LineSegm2f" )
		.constructor<>()
		.constructor<const Vector2f&, const Vector2f&>()
	
		.property( "a", &LineSegm2f::a )
		.property( "b", &LineSegm2f::b )

		.function( "dir", &LineSegm2f::dir )
		.function( "lengthSq", &LineSegm2f::lengthSq )
		.function( "length", &LineSegm2f::length )

        .function( "equals", optional_override([](const LineSegm2f& self, const LineSegm2f& other){ return self.a == other.a && self.b == other.b; }) )
		.function( "opcall", &LineSegm2f::operator() );

	class_<LineSegm2d>( "LineSegm2d" )
		.constructor<>()
		.constructor<const Vector2d&, const Vector2d&>()

		.property( "a", &LineSegm2d::a )
		.property( "b", &LineSegm2d::b )

		.function( "dir", &LineSegm2d::dir )
		.function( "lengthSq", &LineSegm2d::lengthSq )
		.function( "length", &LineSegm2d::length )

        .function( "equals", optional_override([](const LineSegm2d& self, const LineSegm2d& other){ return self.a == other.a && self.b == other.b; }) )
		.function( "opcall", &LineSegm2d::operator() );
	///


	///
	class_<LineSegm3f>( "LineSegm3f" )
		.constructor<>()
		.constructor<const Vector3f&, const Vector3f&>()

		.property( "a", &LineSegm3f::a )
		.property( "b", &LineSegm3f::b )

		.function( "dir", &LineSegm3f::dir )
		.function( "lengthSq", &LineSegm3f::lengthSq )
		.function( "length", &LineSegm3f::length )

        .function( "equals", optional_override([](const LineSegm3f& self, const LineSegm3f& other){ return self.a == other.a && self.b == other.b; }) )
		.function( "opcall", &LineSegm3f::operator() );

	class_<LineSegm3d>( "LineSegm3d" )
		.constructor<>()
		.constructor<const Vector3d&, const Vector3d&>()

		.property( "a", &LineSegm3d::a )
		.property( "b", &LineSegm3d::b )
		
		.function( "dir", &LineSegm3d::dir )
		.function( "lengthSq", &LineSegm3d::lengthSq )
		.function( "length", &LineSegm3d::length )

        .function( "equals", optional_override([](const LineSegm3d& self, const LineSegm3d& other){ return self.a == other.a && self.b == other.b; }) )
		.function( "opcall", &LineSegm3d::operator() );
	///


	function( "closestPointOnLineSegm2f", &closestPointOnLineSegm<Vector2f> );
	function( "closestPointOnLineSegm2d", &closestPointOnLineSegm<Vector2d> );
	function( "closestPointOnLineSegm3f", &closestPointOnLineSegm<Vector3f> );
	function( "closestPointOnLineSegm3d", &closestPointOnLineSegm<Vector3d> );

	function( "doSegmentsIntersect2f", optional_override( [] ( const LineSegm<Vector2f>& x, const LineSegm<Vector2f>& y, float xPos, float yPos  )
	{
		return doSegmentsIntersect(x, y, &xPos, &yPos);
	} ) );
	function( "doSegmentsIntersect2d", optional_override( [] ( const LineSegm<Vector2d>& x, const LineSegm<Vector2d>& y, double xPos, double yPos  )
	{
		return doSegmentsIntersect(x, y, &xPos, &yPos);
	} ) );

	function( "doSegmentLineIntersect2f", optional_override( [] ( const LineSegm<Vector2f>& x, const Line<Vector2f>& y, float xPos, float yPos  )
	{
		return doSegmentLineIntersect(x, y, &xPos, &yPos);
	} ) );
	function( "doSegmentLineIntersect2d", optional_override( [] ( const LineSegm<Vector2d>& x, const Line<Vector2d>& y, double xPos, double yPos  )
	{
		return doSegmentLineIntersect(x, y, &xPos, &yPos);
	} ) );
}
