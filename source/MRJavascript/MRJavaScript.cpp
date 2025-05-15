// #include "MRJavascript.h"

#include <MRMesh/MRMesh.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void printtt()
    {
        std::cout << "Hello, World from meshlib wasm binding!" << std::endl;
    }
}
#endif
