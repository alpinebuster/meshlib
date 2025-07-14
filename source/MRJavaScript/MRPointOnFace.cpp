#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRPointOnFace.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( PointOnFaceModule )
{
    class_<PointOnFace>( "PointOnFace" )
        .property( "face", &PointOnFace::face )      // FaceId
        .property( "point", &PointOnFace::point )     // Vector3f
        .function( "valid", &PointOnFace::valid )
        .function( "opbool", select_overload<bool() const>( &PointOnFace::operator bool ) );
}
