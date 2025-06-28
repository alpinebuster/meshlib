#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRId.h>
#include <MRMesh/MRMeshFwd.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( IdModule )
{
	// Bind EdgeId (Id<EdgeTag>)
	class_<EdgeId>( "EdgeId" )
		.constructor<>() // Default constructor creates invalid ID (-1)
		.constructor<int>() // Constructor from integer
		.function( "valid", &EdgeId::valid ) // Check if ID is valid (>= 0)
		.function( "get", select_overload<EdgeId::ValueType & ( )>( &EdgeId::get ) ) // Get the underlying integer value
		.function( "toInt", [] ( const EdgeId& id )
	{
		return static_cast< int >( id );
	} ) // Explicit conversion to int
		// Comparison operators
		.function( "equals", [] ( const EdgeId& a, const EdgeId& b )
	{
		return a == b;
	} )
		.function( "lessThan", [] ( const EdgeId& a, const EdgeId& b )
	{
		return a < b;
	} )
		// Increment/decrement operators
		.function( "preIncrement", [] ( EdgeId& id ) -> EdgeId&
	{
		return ++id;
	}, allow_raw_pointers() )
		.function( "postIncrement", [] ( EdgeId& id )
	{
		return id++;
	} )
		.function( "preDecrement", [] ( EdgeId& id ) -> EdgeId&
	{
		return --id;
	}, allow_raw_pointers() )
		.function( "postDecrement", [] ( EdgeId& id )
	{
		return id--;
	} )
		// Arithmetic assignment operators
		.function( "addAssign", [] ( EdgeId& id, int value ) -> EdgeId&
	{
		return id += value;
	}, allow_raw_pointers() )
		.function( "subAssign", [] ( EdgeId& id, int value ) -> EdgeId&
	{
		return id -= value;
	}, allow_raw_pointers() );

	// Bind UndirectedEdgeId (Id<UndirectedEdgeTag>)
	class_<UndirectedEdgeId>( "UndirectedEdgeId" )
		.constructor<>()
		.constructor<int>()
		.function( "valid", &UndirectedEdgeId::valid )
		.function( "get", select_overload<UndirectedEdgeId::ValueType & ( )>( &UndirectedEdgeId::get ) )
		.function( "toInt", [] ( const UndirectedEdgeId& id )
	{
		return static_cast< int >( id );
	} )
		.function( "equals", [] ( const UndirectedEdgeId& a, const UndirectedEdgeId& b )
	{
		return a == b;
	} )
		.function( "lessThan", [] ( const UndirectedEdgeId& a, const UndirectedEdgeId& b )
	{
		return a < b;
	} )
		.function( "preIncrement", [] ( UndirectedEdgeId& id ) -> UndirectedEdgeId&
	{
		return ++id;
	}, allow_raw_pointers() )
		.function( "postIncrement", [] ( UndirectedEdgeId& id )
	{
		return id++;
	} )
		.function( "preDecrement", [] ( UndirectedEdgeId& id ) -> UndirectedEdgeId&
	{
		return --id;
	}, allow_raw_pointers() )
		.function( "postDecrement", [] ( UndirectedEdgeId& id )
	{
		return id--;
	} )
		.function( "addAssign", [] ( UndirectedEdgeId& id, int value ) -> UndirectedEdgeId&
	{
		return id += value;
	}, allow_raw_pointers() )
		.function( "subAssign", [] ( UndirectedEdgeId& id, int value ) -> UndirectedEdgeId&
	{
		return id -= value;
	}, allow_raw_pointers() );

	// Bind FaceId (Id<FaceTag>)
	class_<FaceId>( "FaceId" )
		.constructor<>()
		.constructor<int>()
		.function( "valid", &FaceId::valid )
		.function( "get", select_overload<FaceId::ValueType & ( )>( &FaceId::get ) )
		.function( "toInt", [] ( const FaceId& id )
	{
		return static_cast< int >( id );
	} )
		.function( "equals", [] ( const FaceId& a, const FaceId& b )
	{
		return a == b;
	} )
		.function( "lessThan", [] ( const FaceId& a, const FaceId& b )
	{
		return a < b;
	} )
		.function( "preIncrement", [] ( FaceId& id ) -> FaceId&
	{
		return ++id;
	}, allow_raw_pointers() )
		.function( "postIncrement", [] ( FaceId& id )
	{
		return id++;
	} )
		.function( "preDecrement", [] ( FaceId& id ) -> FaceId&
	{
		return --id;
	}, allow_raw_pointers() )
		.function( "postDecrement", [] ( FaceId& id )
	{
		return id--;
	} )
		.function( "addAssign", [] ( FaceId& id, int value ) -> FaceId&
	{
		return id += value;
	}, allow_raw_pointers() )
		.function( "subAssign", [] ( FaceId& id, int value ) -> FaceId&
	{
		return id -= value;
	}, allow_raw_pointers() );

	// Bind VertId (Id<VertTag>)
	class_<VertId>( "VertId" )
		.constructor<>()
		.constructor<int>()
		.function( "valid", &VertId::valid )
		.function( "get", select_overload<VertId::ValueType & ( )>( &VertId::get ) )
		.function( "toInt", [] ( const VertId& id )
	{
		return static_cast< int >( id );
	} )
		.function( "equals", [] ( const VertId& a, const VertId& b )
	{
		return a == b;
	} )
		.function( "lessThan", [] ( const VertId& a, const VertId& b )
	{
		return a < b;
	} )
		.function( "preIncrement", [] ( VertId& id ) -> VertId&
	{
		return ++id;
	}, allow_raw_pointers() )
		.function( "postIncrement", [] ( VertId& id )
	{
		return id++;
	} )
		.function( "preDecrement", [] ( VertId& id ) -> VertId&
	{
		return --id;
	}, allow_raw_pointers() )
		.function( "postDecrement", [] ( VertId& id )
	{
		return id--;
	} )
		.function( "addAssign", [] ( VertId& id, int value ) -> VertId&
	{
		return id += value;
	}, allow_raw_pointers() )
		.function( "subAssign", [] ( VertId& id, int value ) -> VertId&
	{
		return id -= value;
	}, allow_raw_pointers() );

	class_<PixelId>( "PixelId" )
		.constructor<>();

	class_<VoxelId>( "VoxelId" )
		.constructor<>();

	class_<RegionId>( "RegionId" )
		.constructor<>();

	class_<NodeId>( "NodeId" )
		.constructor<>();

	class_<ObjId>( "ObjId" )
		.constructor<>();

	class_<TextureId>( "TextureId" )
		.constructor<>();

	class_<GraphVertId>( "GraphVertId" )
		.constructor<>();

	class_<GraphEdgeId>( "GraphEdgeId" )
		.constructor<>();
}
