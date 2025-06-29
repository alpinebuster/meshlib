#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRMeshFwd.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( BoostDynamicBitsetModule ) {
    using BoostDynamicBitset = boost::dynamic_bitset<std::uint64_t>;

    class_<BoostDynamicBitset>("__InternalDynamicBitset")
        .constructor<>()
        .constructor<size_t>() // Optional, for bypass construction checks only
        .constructor<size_t, bool>();
}

// BitSet base class bindings
EMSCRIPTEN_BINDINGS( BitSetModule )
{
    class_<BitSet>( "BitSet" )
        .constructor<>()
        .constructor<size_t>()
        .constructor<size_t, bool>()
        .class_function( "createWithBool", optional_override( [] ( size_t numBits, bool fillValue )
        {
            return BitSet( numBits, fillValue );
        } ) )

        // Basic operations
        .function( "size", &BitSet::size )
        .function( "count", &BitSet::count )
        .function( "empty", &BitSet::empty )
        .function( "clear", &BitSet::clear )

        // Bit operations
        .function( "test", &BitSet::test )
        .function( "set", select_overload<BitSet & ( size_t, bool )>( &BitSet::set ) )
        .function( "setAll", select_overload<BitSet & ( )>( &BitSet::set ) )
        .function( "setRange", select_overload<BitSet & ( size_t, size_t, bool )>( &BitSet::set ) )
        .function( "reset", select_overload<BitSet & ( size_t )>( &BitSet::reset ) )
        .function( "resetAll", select_overload<BitSet & ( )>( &BitSet::reset ) )
        .function( "resetRange", select_overload<BitSet & ( size_t, size_t )>( &BitSet::reset ) )
        .function( "flip", select_overload<BitSet & ( size_t )>( &BitSet::flip ) )
        .function( "flipAll", select_overload<BitSet & ( )>( &BitSet::flip ) )

        // Search operations
        .function( "find_first", &BitSet::find_first )
        .function( "find_next", &BitSet::find_next )
        .function( "find_last", &BitSet::find_last )
        .function( "nthSetBit", &BitSet::nthSetBit )

        // Collection operations
        .function( "bitwiseAndAssign", select_overload<BitSet & ( const BitSet& )>( &BitSet::operator&= ), return_value_policy::reference() )
        .function( "bitwiseOrAssign", select_overload<BitSet & ( const BitSet& )>( &BitSet::operator|= ), return_value_policy::reference() )
        .function( "bitwiseXorAssign", select_overload<BitSet & ( const BitSet& )>( &BitSet::operator^= ), return_value_policy::reference() )
        .function( "subtractAssign", select_overload<BitSet & ( const BitSet& )>( &BitSet::operator-= ), return_value_policy::reference() )
        .function( "subtract", select_overload<BitSet & ( const BitSet&, int )>( &BitSet::subtract ), return_value_policy::reference() )

        // Automatic resize operation
        .function( "autoResizeSet", select_overload<void( size_t, bool )>( &BitSet::autoResizeSet ) )
        .function( "autoResizeSetRange", select_overload<void( size_t, size_t, bool )>( &BitSet::autoResizeSet ) )
        .function( "autoResizeTestSet", &BitSet::autoResizeTestSet )

        // Memory related
        .function( "heapBytes", &BitSet::heapBytes )
        .function( "resize", &BitSet::resize )
        .function( "resizeWithReserve", &BitSet::resizeWithReserve )
        .function( "push_back", &BitSet::push_back )
        .function( "pop_back", &BitSet::pop_back )

        // ID range
        .function( "backId", &BitSet::backId )
        .function( "endId", &BitSet::endId )
        .class_function( "beginId", &BitSet::beginId );
}

EMSCRIPTEN_BINDINGS( TypedBitSetModule )
{
    class_<FaceBitSet, base<BitSet>>( "FaceBitSet" )
        // class_<FaceBitSet>( "FaceBitSet" )
        .constructor<>()
        .constructor<const BitSet&>()
        // The factory function replaces the overloaded constructor
        .class_function( "createWithSize", optional_override( [] ( size_t numBits )
        {
            return FaceBitSet( numBits );
        } ) )
        .class_function( "createWithValue", optional_override( [] ( size_t numBits, bool fillValue )
        {
            return FaceBitSet( numBits, fillValue );
        } ) )
        .class_function( "createFromBitSet", optional_override( [] ( const BitSet& src )
        {
            return FaceBitSet( src );
        } ) )
        .class_function( "createFromBitSetMove", optional_override( [] ( BitSet&& src )
        {
            return FaceBitSet( std::move( src ) );
        } ) )
        // The instance method is used for replication and movement
        .function( "copyFrom", optional_override( [] ( FaceBitSet& self, const BitSet& src ) -> FaceBitSet&
        {
            self = FaceBitSet( src );
            return self;
        } ), return_value_policy::reference() )
        .function( "moveFrom", optional_override( [] ( FaceBitSet& self, BitSet&& src ) -> FaceBitSet&
        {
            self = FaceBitSet( std::move( src ) );
            return self;
        } ), return_value_policy::reference() )

        // Type-safe bit operations
        .function( "test", &FaceBitSet::test )
        .function( "test_set", &FaceBitSet::test_set )
        .function( "set", select_overload<FaceBitSet & ( FaceId, bool )>( &FaceBitSet::set ), return_value_policy::reference() )
        .function( "setAll", select_overload<FaceBitSet & ( )>( &FaceBitSet::set ), return_value_policy::reference() )
        .function( "setRange", select_overload<FaceBitSet & ( FaceId, FaceBitSet::size_type, bool )>( &FaceBitSet::set ), return_value_policy::reference() )
        .function( "reset", select_overload<FaceBitSet & ( FaceId )>( &FaceBitSet::reset ), return_value_policy::reference() )
        .function( "resetAll", select_overload<FaceBitSet & ( )>( &FaceBitSet::reset ), return_value_policy::reference() )
        .function( "resetRange", select_overload<FaceBitSet & ( FaceId, FaceBitSet::size_type )>( &FaceBitSet::reset ), return_value_policy::reference() )
        .function( "flip", select_overload<FaceBitSet & ( FaceId )>( &FaceBitSet::flip ), return_value_policy::reference() )
        .function( "flipAll", select_overload<FaceBitSet & ( )>( &FaceBitSet::flip ), return_value_policy::reference() )

        .function( "find_first", &FaceBitSet::find_first )
        .function( "find_next", &FaceBitSet::find_next )
        .function( "find_last", &FaceBitSet::find_last )
        .function( "nthSetBit", &FaceBitSet::nthSetBit )

        .function( "bitwiseAndAssign", select_overload<FaceBitSet & ( const FaceBitSet& )>( &FaceBitSet::operator&= ), return_value_policy::reference() )
        .function( "bitwiseOrAssign", select_overload<FaceBitSet & ( const FaceBitSet& )>( &FaceBitSet::operator|= ), return_value_policy::reference() )
        .function( "bitwiseXorAssign", select_overload<FaceBitSet & ( const FaceBitSet& )>( &FaceBitSet::operator^= ), return_value_policy::reference() )
        .function( "subtractAssign", select_overload<FaceBitSet & ( const FaceBitSet& )>( &FaceBitSet::operator-= ), return_value_policy::reference() )

        .function( "is_subset_of", &FaceBitSet::is_subset_of )
        .function( "is_proper_subset_of", &FaceBitSet::is_proper_subset_of )
        .function( "intersects", &FaceBitSet::intersects )

        .function( "autoResizeSet", select_overload<void( FaceId, bool )>( &FaceBitSet::autoResizeSet ) )
        .function( "autoResizeSetRange", select_overload<void( FaceId, FaceBitSet::size_type, bool )>( &FaceBitSet::autoResizeSet ) )
        .function( "autoResizeTestSet", &FaceBitSet::autoResizeTestSet )

        .function( "backId", &FaceBitSet::backId )
        .function( "endId", &FaceBitSet::endId )
        .class_function( "beginId", &FaceBitSet::beginId );

    class_<VertBitSet>( "VertBitSet" )
        .constructor<>();

    class_<EdgeBitSet>( "EdgeBitSet" )
        .constructor<>();

    class_<UndirectedEdgeBitSet>( "UndirectedEdgeBitSet" )
        .constructor<>();

    class_<PixelBitSet>( "PixelBitSet" )
        .constructor<>();

    class_<VoxelBitSet>( "VoxelBitSet" )
        .constructor<>();

    class_<RegionBitSet>( "RegionBitSet" )
        .constructor<>();

    class_<NodeBitSet>( "NodeBitSet" )
        .constructor<>();

    class_<ObjBitSet>( "ObjBitSet" )
        .constructor<>();

    class_<TextureBitSet>( "TextureBitSet" )
        .constructor<>();

    class_<GraphVertBitSet>( "GraphVertBitSet" )
        .constructor<>();

    class_<GraphEdgeBitSet>( "GraphEdgeBitSet" )
        .constructor<>();
}

// To support operator overloading in JavaScript, add global functions
EMSCRIPTEN_BINDINGS( BitSetOperatorsModule )
{
    function( "faceBitSetAnd", +[] ( const FaceBitSet& a, const FaceBitSet& b )
    {
        return a & b;
    } );
    function( "faceBitSetOr", +[] ( const FaceBitSet& a, const FaceBitSet& b )
    {
        return a | b;
    } );
    function( "faceBitSetXor", +[] ( const FaceBitSet& a, const FaceBitSet& b )
    {
        return a ^ b;
    } );
    function( "faceBitSetSub", +[] ( const FaceBitSet& a, const FaceBitSet& b )
    {
        return a - b;
    } );
}
