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


namespace MRJS
{

template <typename Vec2, typename Vec3, typename Mat2, typename Mat3, typename Xf2, typename Xf3>
void bindTyped2to3Conversions( const std::string& suffix )
{
    function( ( "to3dimVec" + suffix ).c_str(), select_overload<Vec3( const Vec2& )>( &to3dim<typename Vec2::ValueType> ) );
    function( ( "to2dimVec" + suffix ).c_str(), select_overload<Vec2( const Vec3& )>( &to2dim<typename Vec2::ValueType> ) );

    function( ( "to3dimMat" + suffix ).c_str(), select_overload<Mat3( const Mat2& )>( &to3dim<typename Vec2::ValueType> ) );
    function( ( "to2dimMat" + suffix ).c_str(), select_overload<Mat2( const Mat3& )>( &to2dim<typename Vec2::ValueType> ) );

    function( ( "to3dimXf" + suffix ).c_str(), select_overload<Xf3( const Xf2& )>( &to3dim<typename Vec2::ValueType> ) );
    function( ( "to2dimXf" + suffix ).c_str(), select_overload<Xf2( const Xf3& )>( &to2dim<typename Vec2::ValueType> ) );
}

} // MRJS

