#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRPointsToMeshProjector.h>

using namespace emscripten;
using namespace MR;

VertScalars findSignedDistancesWrapper(
    const Mesh& refMesh,
    const Mesh& mesh,
    const MeshProjectionParameters& params,
    int projectorPtr = 0 )  // Using int for pointers
{
    IPointsToMeshProjector* projector = nullptr;
    std::unique_ptr<PointsToMeshProjector> defaultProjector;

    if ( projectorPtr != 0 )
    {
        // Using externally passed in projectors (life cycle managed by JavaScript)
        projector = reinterpret_cast< IPointsToMeshProjector* >( projectorPtr );
    }
    else
    {
        defaultProjector = std::make_unique<PointsToMeshProjector>();
        projector = defaultProjector.get();
    }

    return findSignedDistances( refMesh, mesh, params, projector );
}

EMSCRIPTEN_BINDINGS( PointsToMeshProjectorModule )
{
    class_<IPointsToMeshProjector>( "IPointsToMeshProjector" )
        .smart_ptr<std::shared_ptr<IPointsToMeshProjector>>( "IPointsToMeshProjector" )
        .function( "updateMeshData", &IPointsToMeshProjector::updateMeshData, pure_virtual() )
        .function( "findProjections", &IPointsToMeshProjector::findProjections, pure_virtual() )
        .function( "projectionsHeapBytes", &IPointsToMeshProjector::projectionsHeapBytes, pure_virtual() );

    class_<PointsToMeshProjector, base<IPointsToMeshProjector>>( "PointsToMeshProjector" )
        .constructor<>()
        .function( "updateMeshData", &PointsToMeshProjector::updateMeshData )
        .function( "findProjections", &PointsToMeshProjector::findProjections )
        .function( "projectionsHeapBytes", &IPointsToMeshProjector::projectionsHeapBytes );

    class_<MeshProjectionParameters>( "MeshProjectionParameters" )
        .constructor<>()
        .property( "loDistLimitSq", &MeshProjectionParameters::loDistLimitSq )
        .property( "upDistLimitSq", &MeshProjectionParameters::upDistLimitSq )
        .property( "refXf", &MeshProjectionParameters::refXf, return_value_policy::reference() )
        .property( "xf", &MeshProjectionParameters::xf, return_value_policy::reference() );

    // NOTE: We dont need CUDA in WASM/Web, so the `IPointsToMeshProjector` is NOT needed
    function( "findSignedDistancesByPoints",
        select_overload< VertScalars(
            const Mesh&,
            const VertCoords&,
            const VertBitSet*,
            const MeshProjectionParameters&,
            IPointsToMeshProjector*
        )>( &findSignedDistances ), allow_raw_pointers() );

    function( "findSignedDistancesByMesh",
        select_overload< VertScalars(
            const Mesh&,
            const Mesh&,
            const MeshProjectionParameters&,
            IPointsToMeshProjector*
        )>( &findSignedDistances ), allow_raw_pointers()
    );
}
