#include <emscripten/bind.h>

#include <MRMesh/MRVector.h>

using namespace emscripten;
using namespace MR;

using IntVector    = Vector<int,    size_t>;
using FloatVector  = Vector<float,  size_t>;
using DoubleVector = Vector<double, size_t>;

EMSCRIPTEN_BINDINGS( VectorModule )
{
    register_vector<int>( "StdVectori" );
    register_vector<float>( "StdVectorf" );
    register_vector<double>( "StdVectord" );
    register_vector<long long>( "StdVectorll" );
    register_vector<uint64_t>( "StdVectorUint64" );

    class_<IntVector>( "Vectori" )
        .constructor<>()                           // Default constructor
        .constructor<size_t>()                     // Size constructor  
        .constructor<size_t, const int&>()         // Size + value constructor

        // Core container operations
        // These become methods can be called from JavaScript
        .function( "size", &IntVector::size )
        .function( "empty", &IntVector::empty )
        .function( "clear", &IntVector::clear )

        // Element access - this is where the custom indexing comes in
        // JavaScript will see this as vector.get(index)
        .function( "get", select_overload<const int& ( size_t ) const>( &IntVector::operator[] ) )
        .function( "set", select_overload<int& (size_t)>( &IntVector::operator[] ))

        // Resize operations - essential for dynamic containers
        .function( "resize", select_overload<void( size_t )>( &IntVector::resize ) )
        .function( "resizeWithValue", select_overload<void( size_t, const int& )>( &IntVector::resize ) )
        // Advanced resize - this showcases container's unique features
        .function( "resizeWithReserve", select_overload<void( size_t )>( &IntVector::resizeWithReserve ) )
        .function( "resizeWithReserveAndValue", select_overload<void( size_t, const int& )>( &IntVector::resizeWithReserve ) )

        // Automatic resizing - this is a unique feature of Vector class
        .function( "autoResizeAt", &IntVector::autoResizeAt, allow_raw_pointers() )
        .function( "autoResizeSet", select_overload<void( size_t, int )>( &IntVector::autoResizeSet ) )

        // Stack-like operations
        .function( "pushBack", select_overload<void( const int& )>( &IntVector::push_back ) )
        .function( "popBack", &IntVector::pop_back )

        // Access to front/back elements
        .function( "front", select_overload<const int& ( ) const>( &IntVector::front ) )
        .function( "back", select_overload<const int& ( ) const>( &IntVector::back ) )

        // ID-based access
        .function( "beginId", &IntVector::beginId )
        .function( "backId", &IntVector::backId )
        .function( "endId", &IntVector::endId )

        // Memory management info
        .function( "capacity", &IntVector::capacity )
        .function( "reserve", &IntVector::reserve )
        .function( "heapBytes", &IntVector::heapBytes )

        // Comparison operators - JavaScript will be able to use == comparison
        .function("equals", optional_override( [](const IntVector& self, const IntVector& other ) {return self == other;} ))
        .function("notEquals", optional_override( [](const IntVector& self, const IntVector& other ) {return self != other;} ))

        // Direct access to underlying data - useful for performance-critical operations
        // We use typed_memory_view to create JavaScript TypedArrays
        .function( "getData", optional_override( [] ( IntVector& self )
        {
            return val( typed_memory_view( self.size(), self.data() ) );
        }))
        .function( "getDataConst", optional_override( [] ( const IntVector& self )
        {
            return val( typed_memory_view( self.size(), self.data() ) );
        }));

    // Repeat similar bindings for other types
    class_<FloatVector>( "Vectorf" )
        .constructor<>()
        .constructor<size_t>()
        .constructor<size_t, const float&>()

        .function( "size", &FloatVector::size )
        .function( "empty", &FloatVector::empty )
        .function( "clear", &FloatVector::clear )

        .function( "get", select_overload<const float& ( size_t ) const>( &FloatVector::operator[] ) )
        .function( "set", select_overload<float& ( size_t )>( &FloatVector::operator[] ) )

        .function( "resize", select_overload<void( size_t )>( &FloatVector::resize ) )
        .function( "resizeWithValue", select_overload<void( size_t, const float& )>( &FloatVector::resize ) )
        .function( "resizeWithReserve", select_overload<void( size_t )>( &FloatVector::resizeWithReserve ) )
        .function( "resizeWithReserveAndValue", select_overload<void( size_t, const float& )>( &FloatVector::resizeWithReserve ) )

        .function( "autoResizeAt", &FloatVector::autoResizeAt, allow_raw_pointers() )
        .function( "autoResizeSet", select_overload<void( size_t, float )>( &FloatVector::autoResizeSet ) )
    
        .function( "pushBack", select_overload<void( const float& )>( &FloatVector::push_back ) )
        .function( "popBack", &FloatVector::pop_back )

        .function( "front", select_overload<const float& ( ) const>( &FloatVector::front ) )
        .function( "back", select_overload<const float& ( ) const>( &FloatVector::back ) )

        .function( "beginId", &FloatVector::beginId )
        .function( "backId", &FloatVector::backId )
        .function( "endId", &FloatVector::endId )

        .function( "capacity", &FloatVector::capacity )
        .function( "reserve", &FloatVector::reserve )
        .function( "heapBytes", &FloatVector::heapBytes )

        .function("equals", optional_override( [](const FloatVector& self, const FloatVector& other ) {return self == other;} ))
        .function("notEquals", optional_override( [](const FloatVector& self, const FloatVector& other ) {return self != other;} ))

        .function( "getData", optional_override( [] ( FloatVector& self )
        {
            return val( typed_memory_view( self.size(), self.data() ) );
        }))
        .function( "getDataConst", optional_override( [] ( const FloatVector& self )
        {
            return val( typed_memory_view( self.size(), self.data() ) );
        }));

    function( "getAti", select_overload<int   (const IntVector&,   size_t, int)>( &getAt ));
    function( "getAtf", select_overload<float (const FloatVector&, size_t, float)>( &getAt ));
}
