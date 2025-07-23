#include <MRPch/MRWasm.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRMeshTriPoint.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshTriPointModule )
{
    value_object<WeightedVertex>( "WeightedVertex" )
        .field( "v", &WeightedVertex::v )
        .field( "weight", &WeightedVertex::weight );


    class_<MeshTriPoint>( "MeshTriPoint" )
        .constructor<>()
        .constructor<EdgeId, TriPointf>()
    
        .property( "e", &MeshTriPoint::e )
        .property( "bary", &MeshTriPoint::bary )
        .function( "valid", &MeshTriPoint::valid )
        .function( "opbool", select_overload<bool() const>( &MeshTriPoint::operator bool ) )
        .function( "inVertex", select_overload<bool() const>( &MeshTriPoint::inVertex ))
        .function( "onEdge", &MeshTriPoint::onEdge )

        .function( "isBd", &MeshTriPoint::isBd, allow_raw_pointers() )
        .function( "fromTriangle", &MeshTriPoint::fromTriangle )
        .function( "lnext", &MeshTriPoint::lnext )
        .function( "canonical", &MeshTriPoint::canonical )
        .function( "getWeightedVerts", &MeshTriPoint::getWeightedVerts );
}
