#pragma once

#include <optional>
#include <string>
#include <type_traits>

#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRMesh.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRPointCloud.h>
#include <MRMesh/MRMeshOrPoints.h>
#include <MRMesh/MREdgeLengthMesh.h>
#include <MRMesh/MRAABBTree.h>
#include <MRMesh/MRAABBTreePoints.h>
#include <MRMesh/MRAABBTreeObjects.h>
#include <MRMesh/MRCloudPartMapping.h>
#include <MRMesh/MRPartMapping.h>
#include <MRMesh/MRExpected.h>

using namespace emscripten;
using namespace MR;


namespace MRJS
{

template<typename T>
auto bindExpected( const std::string& className )
{
	auto cls = class_<Expected<T>>( className.c_str() )
		.function( "hasValue", &Expected<T>::has_value )
		.function( "opbool", optional_override( [] ( const Expected<T>& self ) -> bool
		{
			return static_cast< bool >( self );
		} ) )
		.function( "error", optional_override( [] ( const Expected<T>& self ) -> const std::string&
		{
			return self.error();
		} ) )
		.function( "hasError", optional_override( [] ( const Expected<T>& self )
		{
			return !self.has_value();
		} ) );

	// If `T` is bool, return the value, not a reference
	if constexpr ( std::is_same<T, bool>::value )
	{
		cls
			.function( "value", optional_override( [] ( Expected<T>& self ) -> bool
			{
				return self.value();
			} ) )
			.function( "getValuePtr", optional_override( [] ( Expected<T>& self ) -> bool
			{
				return self.has_value() ? *self : false;
			} ) )
			.function( "get", optional_override( [] ( Expected<T>& self ) -> bool
			{
				return *self;
			} ) );
	}
	else
	{
		cls
			.function( "value", optional_override( [] ( Expected<T>& self ) -> T&
			{
				return self.value();
			} ), return_value_policy::reference() )
			.function( "get", optional_override( [] ( Expected<T>& self ) -> T&
			{
				return *self;
			} ), return_value_policy::reference() );

		if constexpr ( std::is_same<T, std::string>::value )
		{
			cls.function( "getValuePtr", optional_override( [] ( Expected<T>& self ) -> std::string
			{
				return self.has_value() ? *self : std::string{};
			} ) );
		}
		else if constexpr ( !requires { typename T::first_type; typename T::second_type; } )
		{
			cls.function( "getValuePtr", optional_override( [] ( Expected<T>& self ) -> T*
			{
				return self.has_value() ? &( *self ) : nullptr;
			} ), allow_raw_pointers() );
		}
	}

	// Only bind `valueOr` if T is `is_copy_constructible`
	if constexpr ( std::is_copy_constructible<T>::value )
	{
		cls.function( "valueOr", optional_override( [] ( const Expected<T>& self, const T& defaultValue )
		{
			return self.value_or( defaultValue );
		} ) );
	}

	return cls;
}

}
