#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRExpected.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMesh.h>
#include <MRMesh/MRId.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( ExpectedModule )
{
    // class_<tl::expected<EdgeLoop, std::string>>( "ExpectedEdgeLoop" )
    //     .function( "has_value", &tl::expected<EdgeLoop, std::string>::has_value )
    //     // .function("value", &tl::expected<EdgeLoop, std::string>::value, return_value_policy::reference())
    //     // .function("error", &tl::expected<EdgeLoop, std::string>::error, return_value_policy::reference())
    //     .function( "operatorBool", [] ( const tl::expected<EdgeLoop, std::string>& exp )
    //     {
    //         return exp.has_value();
    //     } );

    
    // class_<Expected<Mesh>>( "ExpectedMesh" )
    //     .function( "has_value", &Expected<Mesh>::has_value )
    //     // .function( "value", &Expected<Mesh>::value, return_value_policy::reference() )
    //     ;
}
