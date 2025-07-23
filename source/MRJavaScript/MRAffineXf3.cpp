#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRAffineXf.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRConstants.h>
#include <MRMesh/MRPlane3.h>

#include "MRAffineXf.h"

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( AffineXf3Module ) {
    // BIND_AFFINE_XF( AffineXf3f, Vector3f );
    // BIND_AFFINE_XF( AffineXf3d, Vector3d );
    bindAffineXf<AffineXf3f, Vector3f>( "AffineXf3f" ); 
    bindAffineXf<AffineXf3d, Vector3d>( "AffineXf3d" );
}
