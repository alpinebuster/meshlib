#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshCollide.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRMeshBoolean.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRMeshFixer.h>
#include <MRMesh/MRProgressCallback.h>
#include <MRMesh/MRUniteManyMeshes.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( UniteManyMeshesModule )
{
    enum_<NestedComponenetsMode>( "NestedComponenetsMode" )
        .value( "Remove", NestedComponenetsMode::Remove )
        .value( "Merge", NestedComponenetsMode::Merge )
        .value( "Union", NestedComponenetsMode::Union );


	class_<UniteManyMeshesParams>( "UniteManyMeshesParams" )
		.constructor<>()
		.property( "useRandomShifts", &UniteManyMeshesParams::useRandomShifts )
		.property( "fixDegenerations", &UniteManyMeshesParams::fixDegenerations )
		.property( "maxAllowedError", &UniteManyMeshesParams::maxAllowedError )
		.property( "randomShiftsSeed", &UniteManyMeshesParams::randomShiftsSeed )
		.property( "newFaces", &UniteManyMeshesParams::newFaces, allow_raw_pointers() )
		.property( "nestedComponentsMode", &UniteManyMeshesParams::nestedComponentsMode )
		.property( "mergeOnFail", &UniteManyMeshesParams::mergeOnFail )
		.property( "forceCut", &UniteManyMeshesParams::forceCut )
		.property( "progressCb", &UniteManyMeshesParams::progressCb );


    function( "uniteManyMeshes", &uniteManyMeshes, allow_raw_pointers() );
}

