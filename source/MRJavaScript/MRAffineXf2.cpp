#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRAffineXf.h>
#include <MRMesh/MRAffineXf2.h>
#include <MRMesh/MRConstants.h>
#include <MRMesh/MRPlane3.h>

#include "MRAffineXf.h"

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( AffineXf2Module ) {
    // BIND_AFFINE_XF( AffineXf2f, Vector2f );
    // BIND_AFFINE_XF( AffineXf2d, Vector2d );
    bindAffineXf<AffineXf2f, Vector2f>( "AffineXf2f" ); 
    bindAffineXf<AffineXf2d, Vector2d>( "AffineXf2d" );
}
