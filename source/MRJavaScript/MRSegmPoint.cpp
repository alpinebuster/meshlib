#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRSegmPoint.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( SegmPointModule )
{
	class_<SegmPointf>( "SegmPointf" )
        .constructor<>();
    
    class_<SegmPointd>( "SegmPointd" )
		.constructor<>();
}
