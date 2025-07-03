#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRICP.h>
#include <MRMesh/MRMeshNormals.h>
#include <MRMesh/MRAligningTransform.h>
#include <MRMesh/MRBestFit.h>
#include <MRMesh/MRMeshOrPoints.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( ICPModule ) {
    class_<ICP>( "ICP" )
        .constructor<const MeshOrPoints&, const MeshOrPoints&, const AffineXf3f&, const AffineXf3f&, const VertBitSet&, const VertBitSet&>()
        .constructor<const MeshOrPointsXf&, const MeshOrPointsXf&, const VertBitSet&, const VertBitSet&>()
        .constructor<const MeshOrPoints&, const MeshOrPoints&, const AffineXf3f&, const AffineXf3f&, float>()
        .constructor<const MeshOrPointsXf&, const MeshOrPointsXf&, float>()

        // .function("setParams", &ICP::setParams)
        .function("setCosineLimit", &ICP::setCosineLimit)
        .function("setDistanceLimit", &ICP::setDistanceLimit)
        .function("setBadIterCount", &ICP::setBadIterCount)
        .function("setFarDistFactor", &ICP::setFarDistFactor)
        .function("setFltSamples", &ICP::setFltSamples)
        .function("sampleFltPoints", &ICP::sampleFltPoints)
        .function("setRefSamples", &ICP::setRefSamples)
        .function("sampleRefPoints", &ICP::sampleRefPoints)
        .function("samplePoints", &ICP::samplePoints)
        // .function("recomputeBitSet", &ICP::recomputeBitSet)
        .function("setXfs", &ICP::setXfs)
        .function("setFloatXf", &ICP::setFloatXf)
        .function("autoSelectFloatXf", &ICP::autoSelectFloatXf)
        .function("updatePointPairs", &ICP::updatePointPairs)
        // .function("getParams", &ICP::getParams, allow_raw_pointers())
        .function("getStatusInfo", &ICP::getStatusInfo)
        .function("getNumSamples", &ICP::getNumSamples)
        .function("getNumActivePairs", &ICP::getNumActivePairs)
        .function("getMeanSqDistToPoint", &ICP::getMeanSqDistToPoint)
        .function("getMeanSqDistToPlane", &ICP::getMeanSqDistToPlane)
        // .function("getFlt2RefPairs", &ICP::getFlt2RefPairs, allow_raw_pointers())
        // .function("getRef2FltPairs", &ICP::getRef2FltPairs, allow_raw_pointers())
        .function("calculateTransformation", &ICP::calculateTransformation);
}
