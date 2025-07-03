#include <emscripten/bind.h>

#include <MRMesh/MRConstants.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( ConstantsModule )
{
	constant( "PI", PI );
	constant( "PI2", PI2 );
	constant( "PI_F", PI_F );
	constant( "PI2_F", PI2_F );
}
