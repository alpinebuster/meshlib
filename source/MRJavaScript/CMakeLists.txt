cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(CMAKE_CXX_STANDARD ${MR_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MRJavaScript CXX)

option(MRJS_NO_VOXELS "Disable voxels support" OFF)
IF(NOT MESHLIB_BUILD_VOXELS)
  set(MRJS_NO_VOXELS ON)
ENDIF()
set(MRJS_OPTIONAL_DEPENDENCIES "")
IF(NOT MRJS_NO_VOXELS)
  list(APPEND MRJS_OPTIONAL_DEPENDENCIES MRVoxels)
  list(APPEND MRJS_OPTIONAL_DEPENDENCIES openvdb)
ENDIF()

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config_cmake.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config_cmake.h)

IF(MR_EMSCRIPTEN)
  add_executable(${PROJECT_NAME} ${SOURCES})

  IF(MR_EMSCRIPTEN_BUILD_DEBUG)
    # REF: `https://emscripten.org/docs/porting/Debugging.html`
    string(JOIN " " CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS}"

      ###
      # NOTE
      "-g"                          # DWARF
      "-gsource-map"                # Source‑map
      "-gseparate-dwarf"            # Separate DWARF files
      # Compared to `-O0` will do some basic code optimization
      # (such as simple constant folding, dead code removal, etc.), 
      # but won't do deep inlining or loop unrolling like `-O2/O3`, 
      # so the compilation speed and debugging experience is still relatively balanced.
      "-O1"
      ###

      "-sASSERTIONS=2"              # More runtime assertions
      "-sSTACK_OVERFLOW_CHECK=2"    # Stack overflow check
    )
  ENDIF()

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_BOOST_HEADERS=1")
  # REF: 
  #   1. `https://emscripten.org/docs/tools_reference/settings_reference.html#exported-runtime-methods`
  #   2. `https://emscripten.org/docs/tools_reference/settings_reference.html#exported-functions`
  #
  # Set target env: `-s ENVIRONMENT=web,worker,node` (see `../../cmake/Modules/CompilerOptions.cmake`)
  #
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lembind -s EXPORT_ES6=1 -s MODULARIZE=1 -s EXPORT_NAME=createMeshSDK -s SINGLE_FILE=0 -s 'EXPORTED_FUNCTIONS=[\"_main\", \"_malloc\", \"_free\"]' -s 'EXPORTED_RUNTIME_METHODS=[\"ccall\", \"HEAPU8\", \"HEAP32\", \"HEAPF32\", \"HEAPU32\", \"FS\"]'")

  string(JOIN " " CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS}"
    "-v" # Display more detailed compilation process information (verbose output)

    # REF: Uncaught RuntimeError: null function or function signature mismatch
    # 
    # `https://github.com/emscripten-core/emscripten/issues/16126#issuecomment-1023067658` & 
    # `https://github.com/emscripten-core/emscripten/issues/16305`
    # 
    # "-fsanitize=undefined"
    # "-Wbad-function-cast -Wcast-function-type"
    # "-sEMULATE_FUNCTION_POINTER_CASTS"
  )
 
  # FIXME:
  # REF: `https://github.com/emscripten-core/emscripten/issues/24620`
  #
  # /tmp/emscripten_temp_9x4nuxmx/tsgen.js:500
  #     wasmMemory = new WebAssembly.Memory({
  #                  ^
  # TypeError: Cannot convert a BigInt value to a number
  #
  IF(NOT MR_EMSCRIPTEN_WASM64)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --emit-tsd ${PROJECT_NAME}.d.ts")
  ENDIF()

  ###
  IF(MR_EMSCRIPTEN_BUILD_DEBUG)
    # 1. Gather all files under `wasm/assets` and `wasm/css`.
    file(GLOB_RECURSE LOCAL_WASM_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/../../wasm/assets/*"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../wasm/css/*"
    )
    # 2. Add the source files used for debug in the `wasm` root directory to the list
    set(WASM_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../wasm")
    list(APPEND LOCAL_WASM_FILES
        "${WASM_ROOT_DIR}/index_mrjs.html"
        "${WASM_ROOT_DIR}/main.js"
        "${WASM_ROOT_DIR}/server.py"
        "${WASM_ROOT_DIR}/post_load_mrjs.js"
        "${WASM_ROOT_DIR}/wasm_loader_mrjs.js"
    )
    # 3. Exclude all files in the `meshsdk` directory
    list(FILTER LOCAL_WASM_FILES EXCLUDE REGEX ".*[/\\]wasm[/\\]meshsdk[/\\].*")

    message(STATUS "Will copy these wasm-debug related files: ${LOCAL_WASM_FILES}")
    file(COPY ${LOCAL_WASM_FILES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
  ENDIF()
  ###

  target_link_libraries(${PROJECT_NAME} PRIVATE
    MRMesh
    MRIOExtras
    MRSymbolMesh
    tbb
    jsoncpp
    ${MRJS_OPTIONAL_DEPENDENCIES}
  )
ENDIF() # MR_EMSCRIPTEN

IF(MR_PCH)
  TARGET_PRECOMPILE_HEADERS(${PROJECT_NAME} REUSE_FROM MRPch)
ENDIF()

install(TARGETS ${PROJECT_NAME} DESTINATION "${MR_BIN_DIR}")
install(FILES ${LIB_LIST} DESTINATION "${MR_RESOURCES_DIR}")
