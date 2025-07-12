#include <optional>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshPart.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRPointCloud.h>
#include <MRMesh/MRProgressCallback.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRGridSampling.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( GridSamplingModule )
{
    class_<ModelPointsData>( "ModelPointsData" )
        .constructor<>()
        .property( "points", &ModelPointsData::points, allow_raw_pointers() )
        .property( "validPoints", &ModelPointsData::validPoints, allow_raw_pointers() )
        .property( "xf", &ModelPointsData::xf, allow_raw_pointers() )
        .property( "fakeObjId", &ModelPointsData::fakeObjId );
    register_optional<ModelPointsData>();


    class_<ObjVertId>( "ObjVertId" )
        .constructor<>()

        .property( "objId", &ObjVertId::objId )
        .property( "vId", &ObjVertId::vId )

        .function( "equals", optional_override( [] ( const ObjVertId& self, const ObjVertId& other )
        {
            return self == other;
        } ) );
    register_optional<MultiObjsSamples>();


    function( "verticesGridSampling", &verticesGridSampling );
    function( "pointGridSampling", &pointGridSampling );
    function( "multiModelGridSampling", &multiModelGridSampling );
}
