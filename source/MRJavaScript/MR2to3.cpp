#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRMatrix2.h>
#include <MRMesh/MRMatrix3.h>
#include <MRMesh/MRAffineXf.h>
#include <MRMesh/MR2to3.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MR2to3Module )
{
    // ------------------------------------------------------------------------
    // Bind the Embind interface for `float`
    // ------------------------------------------------------------------------
    function( "to3dimVecf", select_overload<Vector3f( const Vector2f& )>( &to3dim<float> ) );
    function( "to2dimVecf", select_overload<Vector2f( const Vector3f& )>( &to2dim<float> ) );

    function( "to3dimMatf", select_overload<Matrix3f( const Matrix2f& )>( &to3dim<float> ) );
    function( "to2dimMatf", select_overload<Matrix2f( const Matrix3f& )>( &to2dim<float> ) );

    function( "to3dimXff", select_overload<AffineXf3f( const AffineXf2f& )>( &to3dim<float> ) );
    function( "to2dimXff", select_overload<AffineXf2f( const AffineXf3f& )>( &to2dim<float> ) );


    // ------------------------------------------------------------------------
    // Bind the Embind interface for `double`
    // ------------------------------------------------------------------------
    function( "to3dimVecd", select_overload<Vector3d( const Vector2d& )>( &to3dim<double> ) );
    function( "to2dimVecd", select_overload<Vector2d( const Vector3d& )>( &to2dim<double> ) );

    function( "to3dimMatd", select_overload<Matrix3d( const Matrix2d& )>( &to3dim<double> ) );
    function( "to2dimMatd", select_overload<Matrix2d( const Matrix3d& )>( &to2dim<double> ) );

    function( "to3dimXfd", select_overload<AffineXf3d( const AffineXf2d& )>( &to3dim<double> ) );
    function( "to2dimXfd", select_overload<AffineXf2d( const AffineXf3d& )>( &to2dim<double> ) );
}
