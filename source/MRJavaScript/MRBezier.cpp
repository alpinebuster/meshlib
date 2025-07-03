#include <array>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRVector4.h>
#include <MRMesh/MRVectorTraits.h>
#include <MRMesh/MRBezier.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( CubicBezierCurve )
{
    // ------------------------------------------------------------------------
    // Bind the Embind interface for `CubicBezierCurve2*`
    // ------------------------------------------------------------------------
    class_<CubicBezierCurve2f>( "CubicBezierCurve2f" )
        .constructor<>()
        .function( "getPoint", &CubicBezierCurve2f::getPoint )
        .function( "setPoint", optional_override( [] ( CubicBezierCurve2f& self, int idx, const Vector2f& p )
        {
            if ( idx >= 0 && idx < 4 )
                self.p[idx] = p;
        } ) )
        .class_function( "getWeights", &CubicBezierCurve2f::getWeights );
    class_<CubicBezierCurve2d>( "CubicBezierCurve2d" )
        .constructor<>()
        .function( "getPoint", &CubicBezierCurve2d::getPoint )
        .function( "setPoint", optional_override( [] ( CubicBezierCurve2d& self, int idx, const Vector2d& p )
        {
            if ( idx >= 0 && idx < 4 )
                self.p[idx] = p;
        } ) )
        .class_function( "getWeights", &CubicBezierCurve2d::getWeights );


    // ------------------------------------------------------------------------
    // Bind the Embind interface for `CubicBezierCurve3*`
    // ------------------------------------------------------------------------
    class_<CubicBezierCurve3f>( "CubicBezierCurve3f" )
        .constructor<>()
        .function( "getPoint", &CubicBezierCurve3f::getPoint )
        .function( "setPoint", optional_override( [] ( CubicBezierCurve3f& self, int idx, const Vector3f& p )
        {
            if ( idx >= 0 && idx < 4 )
                self.p[idx] = p;
        } ) )
        .class_function( "getWeights", &CubicBezierCurve3f::getWeights );
    class_<CubicBezierCurve3d>( "CubicBezierCurve3d" )
        .constructor<>()
        .function( "getPoint", &CubicBezierCurve3d::getPoint )
        .function( "setPoint", optional_override( [] ( CubicBezierCurve3d& self, int idx, const Vector3d& p )
        {
            if ( idx >= 0 && idx < 4 )
                self.p[idx] = p;
        } ) )
        .class_function( "getWeights", &CubicBezierCurve3d::getWeights );


    // ------------------------------------------------------------------------
    // Bind the Embind interface for `CubicBezierCurve4*`
    // ------------------------------------------------------------------------
    class_<CubicBezierCurve<Vector4f>>( "CubicBezierCurve4f" )
        .constructor<>()
        .function( "getPoint", &CubicBezierCurve<Vector4f>::getPoint )
        .function( "setPoint", optional_override( [] ( CubicBezierCurve<Vector4f>& self, int idx, const Vector4f& p )
        {
            if ( idx >= 0 && idx < 4 )
                self.p[idx] = p;
        } ) )
        .class_function( "getWeights", &CubicBezierCurve<Vector4f>::getWeights );
    class_<CubicBezierCurve<Vector4d>>( "CubicBezierCurve4d" )
        .constructor<>()
        .function( "getPoint", &CubicBezierCurve<Vector4d>::getPoint )
        .function( "setPoint", optional_override( [] ( CubicBezierCurve<Vector4d>& self, int idx, const Vector4d& p )
        {
            if ( idx >= 0 && idx < 4 )
                self.p[idx] = p;
        } ) )
        .class_function( "getWeights", &CubicBezierCurve<Vector4d>::getWeights );
}
