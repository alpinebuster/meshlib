#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MROneMeshContours.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRIntersectionContour.h>
#include <MRMesh/MREnums.h>

using namespace emscripten;
using namespace MR;

std::unique_ptr<SortIntersectionsData> createSortIntersectionsData(
    const Mesh& otherMesh,
    const ContinuousContours& contours,
    CoordinateConverters& converters,
    const AffineXf3f* xf,
    size_t vertsNum,
    bool isOtherA )
{
    return std::make_unique<SortIntersectionsData>(
        SortIntersectionsData{
            otherMesh,
            contours,
            converters.toInt,
            xf,
            vertsNum,
            isOtherA
        }
    );
}


EMSCRIPTEN_BINDINGS( OneMeshContoursModule )
{
    class_<SortIntersectionsData>( "SortIntersectionsData" )
        // NOTE: NO constructor!
        // Use `createSortIntersectionsData()` to create it

        .property( "rigidB2A", &SortIntersectionsData::rigidB2A, return_value_policy::reference() )
        .property( "meshAVertsNum", &SortIntersectionsData::meshAVertsNum )
        .property( "isOtherA", &SortIntersectionsData::isOtherA )

        // Safer accessors
        // NOTE: See `MRJavaScript/MRPrecisePredicates3.cpp` for more details
        .function( "getConverter", optional_override( [] ( const SortIntersectionsData& d )
        {
            return d.converter;
        } ) )
        .function("getOtherMesh", optional_override([]( const SortIntersectionsData& d ) -> const Mesh& {
            return d.otherMesh;
        }), allow_raw_pointers())
        .function("getContours", optional_override([]( const SortIntersectionsData& d ) -> const ContinuousContours& {
            return d.contours;
        }), allow_raw_pointers());

    function( "createSortIntersectionsData", &createSortIntersectionsData, allow_raw_pointers() );
}
