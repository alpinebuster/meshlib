#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshBuilder.h>

using namespace emscripten;
using namespace MR;
using namespace MeshBuilder;

EMSCRIPTEN_BINDINGS( MeshBuilderModule )
{
    register_vector<VertDuplication>( "VectorVertDuplication" );

	class_<UniteCloseParams>( "UniteCloseParams" )
		.constructor<>()

		.property( "closeDist", &UniteCloseParams::closeDist )
		.property( "uniteOnlyBd", &UniteCloseParams::uniteOnlyBd )
        .property( "region", &UniteCloseParams::region, return_value_policy::reference() )
		.property( "duplicateNonManifold", &UniteCloseParams::duplicateNonManifold )
		.property( "optionalVertOldToNew", &UniteCloseParams::optionalVertOldToNew, return_value_policy::reference() )
        .property( "optionalDuplications", &UniteCloseParams::optionalDuplications, return_value_policy::reference() );

    class_<VertDuplication>( "VertDuplication" )
		.constructor<>()

		.property( "srcVert", &VertDuplication::srcVert )
		.property( "dupVert", &VertDuplication::dupVert );

    function( "uniteCloseVertices", select_overload<int( Mesh&, const UniteCloseParams& )>( &uniteCloseVertices ) );
}
