#include <array>

#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRVector4.h>
#include <MRMesh/MRVectorTraits.h>
#include <MRMesh/MRBezier.h>

#include "MRBezier.h"

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( CubicBezierCurve )
{
    MRJS::bindTypedCubicBezierCurve<CubicBezierCurve2f, Vector2f>( "CubicBezierCurve2f" );
    MRJS::bindTypedCubicBezierCurve<CubicBezierCurve2d, Vector2d>( "CubicBezierCurve2d" );
    MRJS::bindTypedCubicBezierCurve<CubicBezierCurve3f, Vector3f>( "CubicBezierCurve3f" );
    MRJS::bindTypedCubicBezierCurve<CubicBezierCurve3d, Vector3d>( "CubicBezierCurve3d" );
    MRJS::bindTypedCubicBezierCurve<CubicBezierCurve<Vector4f>, Vector4f>( "CubicBezierCurve4f" );
    MRJS::bindTypedCubicBezierCurve<CubicBezierCurve<Vector4d>, Vector4d>( "CubicBezierCurve4d" );
}
