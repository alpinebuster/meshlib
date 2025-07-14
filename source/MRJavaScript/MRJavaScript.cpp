#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>

#include "MRJavaScript.h"

using namespace emscripten;
using namespace MR;


int main()
{
    printf( "C++ Std: Hello World From WASM!\n" );

    EM_ASM(
        console.log( "EM_ASM: Hello from C++ to JS!" );
    );

    greet( "MeshSDK" );

    return 0;
}
