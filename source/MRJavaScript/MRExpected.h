#pragma once

#include <optional>
#include <string>
#include <type_traits>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRMesh.h>
#include <MRMesh/MRId.h>
#include <MRPch/MRExpected.h>
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
		.function( "value", optional_override( [] ( Expected<T>& self ) -> T&
		{
			return self.value();
		} ), return_value_policy::reference() )
		.function( "error", optional_override( [] ( const Expected<T>& self ) -> const std::string&
		{
			return self.error();
		} ) )
		.function( "hasError", optional_override( [] ( const Expected<T>& self )
		{
			return !self.has_value();
		} ) )
		.function( "getValuePtr", optional_override( [] ( Expected<T>& self ) -> T*
		{
			return self.has_value() ? &( *self ) : nullptr;
		} ), allow_raw_pointers() )
		.function( "get", optional_override( [] ( Expected<T>& self ) -> T&
		{
			return *self;
		} ), return_value_policy::reference() );

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
