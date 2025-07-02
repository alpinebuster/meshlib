
#include <emscripten/bind.h>

#include <MRMesh/MRVector.h>

#include "MRUtils.h"

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( UtilsModule )
{
	register_vector<int>( "StdVectori" );
	register_vector<float>( "StdVectorf" );
	register_vector<double>( "StdVectord" );
	register_vector<long long>( "StdVectorll" );
	register_vector<uint64_t>( "StdVectorUint64" );
}
