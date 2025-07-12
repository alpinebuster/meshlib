#include <vector>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRImage.h>
#include <MRMesh/MRVector4.h>
#include <MRMesh/MRMeshTexture.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshTextureModule )
{
    // class_<MR::MeshTexture, base<Image>>( "MeshTexture" )
    class_<MR::MeshTexture>( "MeshTexture" )
        .constructor<>()
        .property( "filter", &MR::MeshTexture::filter )
        .property( "wrap", &MR::MeshTexture::wrap );
}
