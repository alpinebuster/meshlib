cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(CMAKE_CXX_STANDARD ${MR_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MeshViewer CXX)

# We make this a `MACOSX_BUNDLE` even though we don't package it, solely to unify
#   the `MR_LOCAL_RESOURCES=1` search path between this and our other apps that actually need to be bundles.
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE MRViewerApp.cpp)

file(GLOB PNGS "*.png")
file(COPY ${PNGS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

IF(MR_EMSCRIPTEN)
  # file(GLOB LOCAL_WASM_FILES "../../wasm/*.*")
  file(GLOB_RECURSE LOCAL_WASM_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../../wasm/*.*")
  # file(GLOB_RECURSE LOCAL_WASM_FILES
  #   "${CMAKE_CURRENT_SOURCE_DIR}/../../wasm/*.css"
  #   "${CMAKE_CURRENT_SOURCE_DIR}/../../wasm/*.js"
  #   "${CMAKE_CURRENT_SOURCE_DIR}/../../wasm/*.py"
  #   "${CMAKE_CURRENT_SOURCE_DIR}/../../wasm/*.svg"
  #   "${CMAKE_CURRENT_SOURCE_DIR}/../../wasm/*.html"
  # )

  # NOTE: The parent dirs also have one that contains name `meshlib`
  # Handle both forward slashes (Unix) and backslashes (Windows)
  list(FILTER LOCAL_WASM_FILES EXCLUDE REGEX ".*[/\\]wasm[/\\]meshlib[/\\].*")

  # set(FILTERED_WASM_FILES "")
  # foreach(file ${LOCAL_WASM_FILES})
  #   if(file MATCHES ".*/wasm/meshlib/.*")
  #     message(STATUS "Excluding ${file}")
  #   else()
  #     list(APPEND FILTERED_WASM_FILES "${file}")
  #   endif()
  # endforeach()
  # set(LOCAL_WASM_FILES ${FILTERED_WASM_FILES})

  message(STATUS "Found local wasm files: ${LOCAL_WASM_FILES}")
  file(COPY ${LOCAL_WASM_FILES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

  target_link_libraries(${PROJECT_NAME} PRIVATE
    zip
    gtest
    -Wl,--whole-archive
    MRCommonPlugins
    MRMesh
    MRIOExtras
    MRViewer
    -Wl,--no-whole-archive
  )
ELSE() # NOT MR_EMSCRIPTEN
  IF(APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _GNU_SOURCE) #for Boost.Stacktrace
  ENDIF()
  target_link_libraries(${PROJECT_NAME} PRIVATE
    MRViewer
    MRMesh
  )
ENDIF() # MR_EMSCRIPTEN

install(TARGETS ${PROJECT_NAME} DESTINATION "${MR_BIN_DIR}")
install(FILES ${LIB_LIST} DESTINATION "${MR_RESOURCES_DIR}")
install(FILES ${PNGS} DESTINATION "${MR_RESOURCES_DIR}")

IF(MR_PCH)
  TARGET_PRECOMPILE_HEADERS(${PROJECT_NAME} REUSE_FROM MRPch)
ENDIF()
