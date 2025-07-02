#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshMeshDistance.h>
#include <MRMesh/MRAffineXf3.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshMeshDistanceModule )
{
    value_object<MeshMeshDistanceResult>( "MeshMeshDistanceResult" )
        .field( "a", &MeshMeshDistanceResult::a )
        .field( "b", &MeshMeshDistanceResult::b )
        .field( "distSq", &MeshMeshDistanceResult::distSq );

    value_object<MeshMeshSignedDistanceResult>( "MeshMeshSignedDistanceResult" )
        .field( "a", &MeshMeshSignedDistanceResult::a )
        .field( "b", &MeshMeshSignedDistanceResult::b )
        .field( "signedDist", &MeshMeshSignedDistanceResult::signedDist );

    function( "findDistance", &findDistance, allow_raw_pointers() );
    function( "findSignedDistance", &findSignedDistance, allow_raw_pointers() );
    function( "findSignedDistanceAB",
        select_overload<MeshMeshSignedDistanceResult( const MeshPart&, const MeshPart& )>(
            [] ( const MeshPart& a, const MeshPart& b )
            {
                return findSignedDistance( a, b );
            } ) );
    function( "findSignedDistanceWithTransform",
        select_overload<MeshMeshSignedDistanceResult( const MeshPart&, const MeshPart&, const AffineXf3f* )>(
            [] ( const MeshPart& a, const MeshPart& b, const AffineXf3f* rigidB2A )
            {
                return findSignedDistance( a, b, rigidB2A );
            } ), allow_raw_pointers() );
    function( "findSignedDistanceWithLimit",
        select_overload<MeshMeshSignedDistanceResult( const MeshPart&, const MeshPart&, const AffineXf3f*, float )>(
            [] ( const MeshPart& a, const MeshPart& b, const AffineXf3f* rigidB2A, float upDistLimitSq )
            {
                return findSignedDistance( a, b, rigidB2A, upDistLimitSq );
            } ), allow_raw_pointers() );
            
    function( "findMaxDistanceSqOneWay", &findMaxDistanceSqOneWay, allow_raw_pointers() );
    function( "findMaxDistanceSq", &findMaxDistanceSq, allow_raw_pointers() );
}
