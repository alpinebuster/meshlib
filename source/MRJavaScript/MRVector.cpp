#include <emscripten/bind.h>

#include <MRMesh/MRVector.h>

#include "MRVector.h"

using namespace emscripten;
using namespace MR;

using IntVector    = Vector<int,    size_t>;
using FloatVector  = Vector<float,  size_t>;
using DoubleVector = Vector<double, size_t>;


// ------------------------------------------------------------------------
// Bind the Embind interface for `Vector*`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( VectorModule )
{
    bindTypedVector<IntVector>( "Vectori" );
    bindTypedVector<FloatVector>( "Vectorf" );
    bindTypedVector<DoubleVector>( "Vectord" );

    function( "getAti", select_overload<int   ( const IntVector&,    size_t, int    )>( &getAt ));
    function( "getAtf", select_overload<float ( const FloatVector&,  size_t, float  )>( &getAt ) );
    function( "getAtd", select_overload<double( const DoubleVector&, size_t, double )>( &getAt ) );
}
