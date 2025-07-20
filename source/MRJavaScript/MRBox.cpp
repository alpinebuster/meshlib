#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>

#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRBox.h>

using namespace emscripten;
using namespace MR;

// Helper function for squaring
template<typename T>
T sqr( const T& x )
{
	return x * x;
}


EMSCRIPTEN_BINDINGS( BoxModule )
{
    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Box1*`
    // ------------------------------------------------------------------------
	class_<Box1f>( "Box1f" )
		.constructor<>()
		.constructor<const float&, const float&>();
	
	class_<Box1i>( "Box1i" )
		.constructor<>()
		.constructor<const int&, const int&>();
	
	class_<Box1ll>( "Box1ll" )
		.constructor<>()
		.constructor<const long long&, const long long&>();
	
	class_<Box1d>( "Box1d" )
		.constructor<>()
		.constructor<const double&, const double&>();

	
    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Box2*`
    // ------------------------------------------------------------------------
	class_<Box2f>( "Box2f" )
		// Constructors
		.constructor<>()
		.constructor<const Vector2f&, const Vector2f&>()

		// Static factory methods
		.class_function( "fromMinAndSize", &Box2f::fromMinAndSize )
		.class_function( "getMinBoxCorner", &Box2f::getMinBoxCorner )
		.class_function( "getMaxBoxCorner", &Box2f::getMaxBoxCorner )

		// Properties (using property for direct access)
		.property( "min", &Box2f::min )
		.property( "max", &Box2f::max )

		// Methods
		.function( "valid", &Box2f::valid )
		.function( "center", &Box2f::center )
		.function( "corner", &Box2f::corner )
		.function( "size", &Box2f::size )
		.function( "diagonal", &Box2f::diagonal )
		.function( "volume", &Box2f::volume )
		.function( "include", select_overload<void( const Vector2f& )>( &Box2f::include ) )
		.function( "includeBox", select_overload<void( const Box2f& )>( &Box2f::include ) )
		.function( "contains", select_overload<bool( const Vector2f& ) const>( &Box2f::contains ) )
		.function( "containsBox", select_overload<bool( const Box2f& ) const>( &Box2f::contains ) )
		.function( "getBoxClosestPointTo", &Box2f::getBoxClosestPointTo )
		.function( "intersects", &Box2f::intersects )
		.function( "intersection", &Box2f::intersection )
		.function( "intersect", &Box2f::intersect, return_value_policy::reference() )
		.function( "getDistanceSqToBox", select_overload<float( const Box2f& ) const>( &Box2f::getDistanceSq ) )
		.function( "getDistanceSqToPoint", select_overload<float( const Vector2f& ) const>( &Box2f::getDistanceSq ) )
		.function( "expanded", &Box2f::expanded )
		.function( "insignificantlyExpanded", &Box2f::insignificantlyExpanded );
	
	class_<Box2i>( "Box2i" )
		.constructor<>()
		.constructor<const Vector2i&, const Vector2i&>();
	
	class_<Box2ll>( "Box2ll" )
		.constructor<>()
		.constructor<const Vector2ll&, const Vector2ll&>();
	
	class_<Box2d>( "Box2d" )
		.constructor<>()
		.constructor<const Vector2d&, const Vector2d&>();

	
    // ------------------------------------------------------------------------
    // Bind the Embind interface for `Box3*`
    // ------------------------------------------------------------------------
	class_<Box3f>( "Box3f" )
		// Constructors
		.constructor<>()
		.constructor<const Vector3f&, const Vector3f&>()

		// Static factory methods
		.class_function( "fromMinAndSize", &Box3f::fromMinAndSize )
		.class_function( "getMinBoxCorner", &Box3f::getMinBoxCorner )
		.class_function( "getMaxBoxCorner", &Box3f::getMaxBoxCorner )

		// Properties
		.property( "min", &Box3f::min )
		.property( "max", &Box3f::max )

		// Methods
		.function( "valid", &Box3f::valid )
		.function( "center", &Box3f::center )
		.function( "corner", &Box3f::corner )
		.function( "size", &Box3f::size )
		.function( "diagonal", &Box3f::diagonal )
		.function( "volume", &Box3f::volume )
		.function( "include", select_overload<void( const Vector3f& )>( &Box3f::include ) )
		.function( "includeBox", select_overload<void( const Box3f& )>( &Box3f::include ) )
		.function( "contains", select_overload<bool( const Vector3f& ) const>( &Box3f::contains ) )
		.function( "containsBox", select_overload<bool( const Box3f& ) const>( &Box3f::contains ) )
		.function( "getBoxClosestPointTo", &Box3f::getBoxClosestPointTo )
		.function( "intersects", &Box3f::intersects )
		.function( "intersection", &Box3f::intersection )
		.function( "intersect", &Box3f::intersect, return_value_policy::reference() )
		.function( "getDistanceSqToBox", select_overload<float( const Box3f& ) const>( &Box3f::getDistanceSq ) )
		.function( "getDistanceSqToPoint", select_overload<float( const Vector3f& ) const>( &Box3f::getDistanceSq ) )
		.function( "expanded", &Box3f::expanded )
		.function( "insignificantlyExpanded", &Box3f::insignificantlyExpanded );
	
	class_<Box3i>( "Box3i" )
		.constructor<>()
		.constructor<const Vector3i&, const Vector3i&>();
	
	class_<Box3ll>( "Box3ll" )
		.constructor<>()
		.constructor<const Vector3ll&, const Vector3ll&>();
	
	class_<Box3d>( "Box3d" )
		.constructor<>()
		.constructor<const Vector3d&, const Vector3d&>();
}
