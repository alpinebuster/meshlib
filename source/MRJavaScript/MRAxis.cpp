#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRAxis.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( AxisModule )
{
    enum_<Axis>( "Axis" )
        .value( "X", Axis::X )
        .value( "Y", Axis::Y )
        .value( "Z", Axis::Z )
        .value( "Count", Axis::Count );
}
