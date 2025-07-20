#include <MRPch/MRWasm.h>

#include <MRMesh/MRId.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRBitSet.h>

#include "MRBitSet.h"

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( __internalBoostDynamicBitsetModule )
{
    using BoostDynamicBitset = boost::dynamic_bitset<std::uint64_t>;

    class_<BoostDynamicBitset>("__InternalDynamicBitset")
        .constructor<>()
        .constructor<size_t>() // Optional, for bypass construction checks only
        .constructor<size_t, bool>();
}


// `BitSet` base class bindings
EMSCRIPTEN_BINDINGS( BitSetModule )
{
    class_<BitSet>( "BitSet" )
        .smart_ptr<std::shared_ptr<BitSet>>( "BitSetSharedPtr" )
        
        .constructor<>()
        .constructor<size_t>()
        .constructor<size_t, bool>()
        .class_function( "createFromValue", optional_override( [] ( size_t numBits, bool fillValue )
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
    // NOTE:
    // 
    // Interface 'FaceBitSet' incorrectly extends interface 'BitSet'.
    // Types of property 'test' are incompatible.
    //     Type '(_0: FaceId) => boolean' is not assignable to type '(_0: number) => boolean'.
    //     Types of parameters '_0' and '_0' are incompatible.
    //         Type 'number' is not assignable to type 'FaceId'.ts(2430)
    // 
    // class_<FaceBitSet, base<BitSet>>( "FaceBitSet" )
    // 
    bindTypedBitSet<FaceBitSet>( "FaceBitSet" );
    bindTypedBitSet<VertBitSet>( "VertBitSet" );
    bindTypedBitSet<EdgeBitSet>( "EdgeBitSet" );
    bindTypedBitSet<UndirectedEdgeBitSet>( "UndirectedEdgeBitSet" );
    bindTypedBitSet<PixelBitSet>( "PixelBitSet" );
    bindTypedBitSet<VoxelBitSet>( "VoxelBitSet" );
    bindTypedBitSet<RegionBitSet>( "RegionBitSet" );
    bindTypedBitSet<NodeBitSet>( "NodeBitSet" );
    bindTypedBitSet<ObjBitSet>( "ObjBitSet" );
    bindTypedBitSet<TextureBitSet>( "TextureBitSet" );
    bindTypedBitSet<GraphVertBitSet>( "GraphVertBitSet" );
    bindTypedBitSet<GraphEdgeBitSet>( "GraphEdgeBitSet" );
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
