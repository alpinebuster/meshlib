#include <MRPch/MRWasm.h>

#include <MRMesh/MRPlane3.h>
#include <MRMesh/MRMeshFwd.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( PlaneModule )
{
    class_<Plane3f>( "Plane3f" )
        .constructor<>()
        .constructor<const Vector3f&, float>()
        .constructor<const Plane3d&>() 

        .class_function( "fromDirAndPt", &Plane3f::fromDirAndPt )

        .property( "n", &Plane3f::n )
        .property( "d", &Plane3f::d )

        .function( "negate", emscripten::select_overload<Plane3f() const>( &Plane3f::operator- ) )
        .function( "positive", emscripten::select_overload<const Plane3f & ( ) const>( &Plane3f::operator+ ) )

        .function( "distance", &Plane3f::distance )
        .function( "normalized", &Plane3f::normalized )
        .function( "project", &Plane3f::project );

    class_<Plane3d>( "Plane3d" )
        .constructor<>()
        .constructor<const Vector3d&, double>()
        .constructor<const Plane3f&>() 

        .class_function( "fromDirAndPt", &Plane3d::fromDirAndPt )

        .property( "n", &Plane3d::n )
        .property( "d", &Plane3d::d )

        .function( "negate", select_overload<Plane3d() const>( &Plane3d::operator- ) )
        .function( "positive", select_overload<const Plane3d & ( ) const>( &Plane3d::operator+ ) )

        .function( "distance", &Plane3d::distance )
        .function( "normalized", &Plane3d::normalized )
        .function( "project", &Plane3d::project );
}
