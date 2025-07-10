#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRMeshTriPoint.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshTriPointModule )
{
    value_object<WeightedVertex>( "WeightedVertex" )
        .field( "v", &WeightedVertex::v )
        .field( "weight", &WeightedVertex::weight );
    using WVArr3 = std::array<WeightedVertex, 3>;
    value_array<WVArr3>( "WeightedVertexArray3" )
        .element( emscripten::index<0>() )
        .element( emscripten::index<1>() )
        .element( emscripten::index<2>() );

    class_<MeshTriPoint>( "MeshTriPoint" )
        .constructor<>()
        .constructor<EdgeId, TriPointf>()
    
        .property( "e", &MeshTriPoint::e )
        .property( "bary", &MeshTriPoint::bary )
        .function( "valid", &MeshTriPoint::valid )
        .function( "asBool", select_overload<bool() const>( &MeshTriPoint::operator bool ) )
        .function( "inVertex", select_overload<bool() const>( &MeshTriPoint::inVertex ))
        .function( "onEdge", &MeshTriPoint::onEdge )
        // NOTE:
        // `[[nodiscard]] MRMESH_API bool isBd( const MeshTopology & topology, const FaceBitSet * region = nullptr ) const;`
        .function( "isBd", &MeshTriPoint::isBd, allow_raw_pointers() )
        .function( "fromTriangle", &MeshTriPoint::fromTriangle )
        .function( "lnext", &MeshTriPoint::lnext )
        .function( "canonical", &MeshTriPoint::canonical )
        .function( "getWeightedVerts", &MeshTriPoint::getWeightedVerts );
}
