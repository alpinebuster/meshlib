#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRAABBTree.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( AABBTreeModule )
{
	class_<AABBTree>( "AABBTree" )
		.constructor<>();

}
