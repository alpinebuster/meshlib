#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRRelaxParams.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( RelaxParamsModule )
{
    enum_<RelaxApproxType>( "RelaxApproxType" )
        .value( "Planar", RelaxApproxType::Planar )
        .value( "Quadric", RelaxApproxType::Quadric );

    class_<RelaxParams>( "RelaxParams" )
		.constructor<>()
        .property( "iterations", &RelaxParams::iterations )
        .property( "region", &RelaxParams::region, allow_raw_pointers() )
        .property( "force", &RelaxParams::force )
        .property( "limitNearInitial", &RelaxParams::limitNearInitial )
        .property( "maxInitialDist", &RelaxParams::maxInitialDist );
}
