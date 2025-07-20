#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRMatrix2.h>
#include <MRMesh/MRMatrix3.h>
#include <MRMesh/MRAffineXf.h>
#include <MRMesh/MR2to3.h>

#include "MR2to3.h"

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( MR2to3Module )
{
    MRJS::bindTyped2to3Conversions<Vector2f, Vector3f, Matrix2f, Matrix3f, AffineXf2f, AffineXf3f>( "f" );
    MRJS::bindTyped2to3Conversions<Vector2d, Vector3d, Matrix2d, Matrix3d, AffineXf2d, AffineXf3d>( "d" );
}
