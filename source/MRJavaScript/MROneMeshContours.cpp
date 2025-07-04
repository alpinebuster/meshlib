#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MROneMeshContours.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRIntersectionContour.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( OneMeshContoursModule )
{
    // class_<SortIntersectionsData>( "SortIntersectionsData" )
	// 	// .constructor<>()
    //     .constructor<
    //         const Mesh&,
    //         const ContinuousContours&,
    //         ConvertToIntVector,
    //         const AffineXf3f*,
    //         size_t,
    //         bool
    //     >()

    //     // .property( "otherMesh", &SortIntersectionsData::otherMesh, return_value_policy::reference() )
    //     // .property( "contours", &SortIntersectionsData::contours, return_value_policy::reference() )
    //     // .property( "converter", &SortIntersectionsData::converter )
    //     .property( "rigidB2A", &SortIntersectionsData::rigidB2A, return_value_policy::reference() )
    //     .property( "meshAVertsNum", &SortIntersectionsData::meshAVertsNum )
    //     .property( "isOtherA", &SortIntersectionsData::isOtherA );
}
