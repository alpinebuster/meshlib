#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshExtrude.h>
#include <MRMesh/MRPrecisePredicates3.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRBox.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( PrecisePredicates3Module )
{
	// NOTE: Just to make `embind` happy!
	class_<ConvertToFloatVector>( "ConvertToFloatVector" );
	class_<ConvertToIntVector>( "ConvertToIntVector" );

	///
	// ```js
	// const conv = new Module.CoordinateConverters();
	// 
	// conv.toInt = Module.createConvertToIntVector( function( v3f ) {
	// 	return [Math.floor( v3f[0] ), Math.floor( v3f[1] ), Math.floor( v3f[2] )];
	// });
	// 
	// conv.toFloat = Module.createConvertToFloatVector( function( v3i ) {
	// 	return [v3i[0] + 0.5, v3i[1] + 0.5, v3i[2] + 0.5];
	// });
	// 
	// // Use conv.toInt( someVector3f )...
	// ```
	///
	function( "createConvertToIntVector", optional_override( [] ( const val& func ) -> ConvertToIntVector
	{
		return [func] ( const Vector3f& input ) -> Vector3i
		{
			return func( input ).as<Vector3i>();
		};
	} ) );
	function( "createConvertToFloatVector", optional_override( [] ( const val& func ) -> ConvertToFloatVector
	{
		return [func] ( const Vector3i& input ) -> Vector3f
		{
			return func( input ).as<Vector3f>();
		};
	} ) );

	// struct
	class_<CoordinateConverters>( "CoordinateConverters" )
		.constructor<>()

		.function( "setToInt", optional_override( [] ( CoordinateConverters& c, const val& f )
		{
			c.toInt = [f] ( const Vector3f& v3f )
			{
				return f( v3f ).as<Vector3i>();
			};
		} ) )
		.function( "callToInt", optional_override( [] ( const CoordinateConverters& c, const Vector3f& v3f )
		{
			return c.toInt( v3f );
		} ) )

		.function( "setToFloat", optional_override( [] ( CoordinateConverters& c, const val& f )
		{
			c.toFloat = [f] ( const Vector3i& v3i )
			{
				return f( v3i ).as<Vector3f>();
			};
		} ) )
		.function( "callToFloat", optional_override( [] ( const CoordinateConverters& c, const Vector3i& v3i )
		{
			return c.toFloat( v3i );
		} ) );
}
