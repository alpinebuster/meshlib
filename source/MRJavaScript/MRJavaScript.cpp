#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>

#include "MRJavaScript.h"

using namespace emscripten;
using namespace MR;

int main() {
    printf("Hello World From WASM!\n");
    return 0;
}
