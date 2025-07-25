#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MREnums.h>

#include <MRVoxels/MROffset.h>

#include "MRUtils.h"

using namespace emscripten;
using namespace MR;

namespace MRJS {

val thickenMeshImpl( const Mesh& mesh, float offset, const GeneralOffsetParameters& params );
val thickenMeshImplFilled( const Mesh& mesh, float offset, const GeneralOffsetParameters& params );

} // namespace MRJS
