#include <emscripten/bind.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MRIdModule )
{
    // 1) Expose `NoInit` as an empty value type
    value_object<MR::NoInit>( "NoInit" );
    // 2) Expose the global constant `noInit` to JS
    constant( "noInit", MR::noInit );

    // Bind `UndirectedEdgeId` first (needed for `EdgeId` constructor)
    class_<Id<UndirectedEdgeTag>>( "UndirectedEdgeId" )
        .constructor<>()
        .constructor<int>()

        .function( "valid", &Id<UndirectedEdgeTag>::valid )
        .function( "toInt", select_overload<int() const>( static_cast<int( Id<UndirectedEdgeTag>::* )() const >( &Id<UndirectedEdgeTag>::operator int ) ) )
        .function( "toBool", optional_override( []( const Id<UndirectedEdgeTag>& self ) { return bool( self ); }))
        .function( "get", &Id<UndirectedEdgeTag>::get )
        .function( "equals", optional_override([](const Id<UndirectedEdgeTag>& self, const Id<UndirectedEdgeTag>& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const Id<UndirectedEdgeTag>& self, const Id<UndirectedEdgeTag>& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const Id<UndirectedEdgeTag>& self, const Id<UndirectedEdgeTag>& other){ return self < other; }) )
        .function( "increment", select_overload<Id<UndirectedEdgeTag>&()>( &Id<UndirectedEdgeTag>::operator-- ) )
        .function( "decrement", select_overload<Id<UndirectedEdgeTag>&()>( &Id<UndirectedEdgeTag>::operator++ ) )
        .function( "incrementByInt", select_overload<Id<UndirectedEdgeTag>( int )>( &Id<UndirectedEdgeTag>::operator-- ) )
        .function( "decrementByInt", select_overload<Id<UndirectedEdgeTag>( int )>( &Id<UndirectedEdgeTag>::operator++ ) );

    class_<Id<EdgeTag>>( "EdgeId" )
        // Constructors
        .constructor<>()
        .constructor<int>()
        .class_function( "fromUndirected", optional_override( []( const UndirectedEdgeId& u ) {return Id<EdgeTag>( u );}))

        // Validity check
        .function( "valid", &Id<EdgeTag>::valid )
        // Conversion
        .function( "toInt", optional_override([](const Id<EdgeTag>& self){ return int(self); }))
        .function( "toBool", optional_override([](const Id<EdgeTag>& self){ return bool(self); }))
        // Access underlying value
        .function( "get", optional_override([](Id<EdgeTag>& self){ return self.get(); }))
        // Symmetry operations
        .function( "sym", &Id<EdgeTag>::sym )
        .function( "even", &Id<EdgeTag>::even )
        .function( "odd", &Id<EdgeTag>::odd )
        // Undirected conversion
        .function( "undirected", &Id<EdgeTag>::undirected )
        .function( "toUndirected", optional_override([](const Id<EdgeTag>& self) { return self.undirected(); }) )
        // Comparison
        .function( "equals", optional_override( [](const Id<EdgeTag>& self, const Id<EdgeTag>& other) { return self == other; } ) )
        .function( "notEquals", optional_override([](const Id<EdgeTag>& self, const Id<EdgeTag>& other){ return self != other; }) )
        .function( "lessThan", optional_override( [](const Id<EdgeTag>& self, const Id<EdgeTag>& other){ return self < other; } ) )
        // Increment / Decrement
        .function( "increment", select_overload<Id<EdgeTag>&()>( &Id<EdgeTag>::operator-- ) )
        .function( "decrement", select_overload<Id<EdgeTag>&()>( &Id<EdgeTag>::operator++ ) )
        .function( "incrementByInt", select_overload<Id<EdgeTag>( int )>( &Id<EdgeTag>::operator-- ) )
        .function( "decrementByInt", select_overload<Id<EdgeTag>( int )>( &Id<EdgeTag>::operator++ ) );
    
    class_<Id<FaceTag>>( "FaceId" )
        .constructor<>()
        .constructor<int>()

        .function( "valid", &Id<FaceTag>::valid )
        .function( "toInt", select_overload<int () const>( static_cast<int( Id<FaceTag>::* ) () const>( &Id<FaceTag>::operator int )))
        .function( "toBool", optional_override( []( const Id<FaceTag>& self ) { return bool( self ); }))
        .function( "get", &Id<FaceTag>::get )
        .function( "equals", optional_override([](const Id<FaceTag>& self, const Id<FaceTag>& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const Id<FaceTag>& self, const Id<FaceTag>& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const Id<FaceTag>& self, const Id<FaceTag>& other){ return self < other; }) )
        .function( "increment", select_overload<Id<FaceTag>&()>( &Id<FaceTag>::operator-- ) )
        .function( "decrement", select_overload<Id<FaceTag>&()>( &Id<FaceTag>::operator++ ) )
        .function( "incrementByInt", select_overload<Id<FaceTag>( int )>( &Id<FaceTag>::operator-- ) )
        .function( "decrementByInt", select_overload<Id<FaceTag>( int )>( &Id<FaceTag>::operator++ ) );

    class_<Id<VertTag>>( "VertId" )
        .constructor<>()
        .constructor<int>()

        .function( "valid", &Id<VertTag>::valid )
        .function( "toInt", select_overload<int() const>( static_cast<int ( Id<VertTag>::* ) () const>( &Id<VertTag>::operator int ) ) )
        .function( "toBool", optional_override( [] ( const Id<VertTag>& self ) { return bool( self ); }))
        .function( "get", &Id<VertTag>::get )
        .function( "equals", optional_override([](const Id<VertTag>& self, const Id<VertTag>& other){ return self == other; }) )
        .function( "notEquals", optional_override([](const Id<VertTag>& self, const Id<VertTag>& other){ return self != other; }) )
        .function( "lessThan", optional_override([](const Id<VertTag>& self, const Id<VertTag>& other){ return self < other; }) )
        .function( "increment", select_overload<Id<VertTag>&()>( &Id<VertTag>::operator-- ) )
        .function( "decrement", select_overload<Id<VertTag>&()>( &Id<VertTag>::operator++ ) )
        .function( "incrementByInt", select_overload<Id<VertTag>( int )>( &Id<VertTag>::operator-- ) )
        .function( "decrementByInt", select_overload<Id<VertTag>( int )>( &Id<VertTag>::operator++ ) );
}
