#pragma once

#include <optional>
#include <string>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRBuffer.h>

using namespace emscripten;
using namespace MR;


namespace MRJS
{

template<typename T, typename I>
class BufferBinding {

public:
	BufferBinding( const std::string& jsName ) : binding_( class_<Buffer<T, I>>( jsName.c_str() ) )
	{
		binding_.constructor<>();
		binding_.constructor<size_t>();
	}

	BufferBinding& init()
	{
		binding_.function( "capacity", &Buffer<T, I>::capacity );
		binding_.function( "size", &Buffer<T, I>::size );
		binding_.function( "empty", &Buffer<T, I>::empty );
		binding_.function( "clear", &Buffer<T, I>::clear );
		binding_.function( "resize", &Buffer<T, I>::resize );

		binding_.function( "beginId", &Buffer<T, I>::beginId );
		binding_.function( "backId", &Buffer<T, I>::backId );
		binding_.function( "endId", &Buffer<T, I>::endId );
		binding_.function( "heapBytes", &Buffer<T, I>::heapBytes );

		///
		// FIXME: Why `select_override` does not work??
		binding_.function( "get", optional_override( []( const Buffer<T, I>& self, I id ) -> T {
			return self[id];
		}));
		binding_.function( "set", optional_override( []( Buffer<T, I>& self, I id, const T& value ) {
			self[id] = value;
		}));
		///


		///
		// FIXME: Why this does not work??
		// Error: `no matching function for call to 'select_overload<T* ( Buffer<T, I>::* )()>( &Buffer<T, I>::data )'`
		// 
		// binding_.function( "data", select_overload<T * ( Buffer<T, I>::* )( )>( &Buffer<T, I>::data ), allow_raw_pointers() );
		// binding_.function( "dataConst", select_overload<const T* ( Buffer<T, I>::* )() const>( &Buffer<T, I>::data ), allow_raw_pointers() );
		// 
		binding_.function( "data", optional_override( [] ( Buffer<T, I>& self )
		{
			return self.data();
		} ), allow_raw_pointers() );
		binding_.function( "dataConst", optional_override( [] ( const Buffer<T, I>& self ) -> const T*
		{
			return self.data();
		} ), allow_raw_pointers() );
		///

		return *this;
	}

private:
	class_<Buffer<T, I>> binding_;
};

}
