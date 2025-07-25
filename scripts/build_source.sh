#!/bin/bash

#This script builds project by CMakeLists.txt
#Assumption: thirdparty packages are already installed by `apt` or built into `./lib`

dt=$(date '+%d-%m-%Y_%H:%M:%S');
logfile="`pwd`/build_source_${dt}.log"
echo "Project build script started."
echo "You could find output in ${logfile}"

MR_EMSCRIPTEN_SINGLETHREAD=0
MR_EMSCRIPTEN_WASM64=0
if [[ $OSTYPE == "linux"* ]]; then
  if [ ! -n "$MR_EMSCRIPTEN" ]; then
    read -t 5 -p "Build with emscripten? Press (y) in 5 seconds to build (y/s/l/N) (s - singlethreaded, l - 64-bit)" -rsn 1
    echo;
    case $REPLY in
      Y|y)
        MR_EMSCRIPTEN="ON";;
      S|s)
        MR_EMSCRIPTEN="ON"
        MR_EMSCRIPTEN_SINGLETHREAD=1;;
      L|l)
        MR_EMSCRIPTEN="ON"
        MR_EMSCRIPTEN_WASM64=1;;
      *)
        MR_EMSCRIPTEN="OFF";;
    esac

    if [ $MR_EMSCRIPTEN == "ON" ]; then
      read -t 5 -p "Build with SDK only? Press (y) in 5 seconds to build (y/N)" -rsn 1
      echo;
      case $REPLY in
        Y|y)
          MR_EMSCRIPTEN_SDK="ON";;
        *)
          MR_EMSCRIPTEN_SDK="OFF";;
      esac
    fi
  fi
else
  if [ ! -n "$MR_EMSCRIPTEN" ]; then
    MR_EMSCRIPTEN="OFF"
  fi
fi

if [ $MR_EMSCRIPTEN == "ON" ]; then
  if [[ $MR_EMSCRIPTEN_SINGLE == "ON" ]]; then
    MR_EMSCRIPTEN_SINGLETHREAD=1
  fi
  if [[ $MR_EMSCRIPTEN_W64 == "ON" ]]; then
    MR_EMSCRIPTEN_WASM64=1
  fi
fi

if [ ! -n "$MESHLIB_BUILD_RELEASE" ]; then
  read -t 5 -p "Build MeshSDK Release? Press (n) in 5 seconds to cancel (Y/n)" -rsn 1
  echo;
  if [[ $REPLY =~ ^[Nn]$ ]]; then
    MESHLIB_BUILD_RELEASE="OFF"
  else
    MESHLIB_BUILD_RELEASE="ON"
  fi
  echo "Release ${MESHLIB_BUILD_RELEASE}"
fi

if [ ! -n "$MESHLIB_BUILD_DEBUG" ]; then
  read -t 5 -p "Build MeshSDK Debug? Press (y) in 5 seconds to build (y/N)" -rsn 1
  echo;
  if [[ $REPLY =~ ^[Yy]$ ]]; then
    MESHLIB_BUILD_DEBUG="ON"
  else
    MESHLIB_BUILD_DEBUG="OFF"
  fi
  echo "Debug ${MESHLIB_BUILD_DEBUG}"
fi

echo "Emscripten ${MR_EMSCRIPTEN:-OFF}, singlethread ${MR_EMSCRIPTEN_SINGLE:-OFF}, 64-bit ${MR_EMSCRIPTEN_W64:-OFF}, SDK only ${MR_EMSCRIPTEN_SDK:-OFF}, Release ${MESHLIB_BUILD_RELEASE:-OFF}, Debug ${MESHLIB_BUILD_DEBUG:-OFF}"

# add env options to cmake
MR_CMAKE_OPTIONS="${MR_CMAKE_OPTIONS:-}"

if command -v ninja >/dev/null 2>&1 ; then
  MR_CMAKE_OPTIONS="${MR_CMAKE_OPTIONS} -G Ninja"
fi

if [ "${MESHLIB_USE_VCPKG}" == "ON" ]; then
  MR_CMAKE_OPTIONS="${MR_CMAKE_OPTIONS} \
    -D MESHLIB_USE_VCPKG=ON \
    -D VCPKG_TARGET_TRIPLET=${VCPKG_TRIPLET:?VCPKG_TRIPLET must be set} \
  "
fi

if [ "${MR_EMSCRIPTEN}" != "ON" ] ; then
  if [ -n "${CMAKE_C_COMPILER}" ] ; then
    MR_CMAKE_OPTIONS="${MR_CMAKE_OPTIONS} -D CMAKE_C_COMPILER=${CMAKE_C_COMPILER}"
  fi
  if [ -n "${CMAKE_CXX_COMPILER}" ] ; then
    MR_CMAKE_OPTIONS="${MR_CMAKE_OPTIONS} -D CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
  fi
  if [ -n "${CMAKE_LINKER_TYPE}" ] ; then
    MR_CMAKE_OPTIONS="${MR_CMAKE_OPTIONS} -D CMAKE_LINKER_TYPE=${CMAKE_LINKER_TYPE}"
  fi
fi

if [ "${MR_EMSCRIPTEN}" == "ON" ]; then
  if [ -z "${EMSDK}" ] ; then
    echo "Emscripten SDK not found"
    exit 1
  fi
  EMSCRIPTEN_ROOT="${EMSDK}/upstream/emscripten"

  MR_CMAKE_OPTIONS="${MR_CMAKE_OPTIONS} \
    -D CMAKE_TOOLCHAIN_FILE=${EMSCRIPTEN_ROOT}/cmake/Modules/Platform/Emscripten.cmake \
    -D CMAKE_FIND_ROOT_PATH=${PWD} \
    -D MR_EMSCRIPTEN=1 \
    -D MR_EMSCRIPTEN_SINGLETHREAD=${MR_EMSCRIPTEN_SINGLETHREAD} \
    -D MR_EMSCRIPTEN_WASM64=${MR_EMSCRIPTEN_WASM64} \
  "

  if [ "${MR_EMSCRIPTEN_SDK}" == "ON" ]; then
    MR_CMAKE_OPTIONS="${MR_CMAKE_OPTIONS} -D MR_EMSCRIPTEN_SDK=1"
  fi
  
  if [ "${MESHLIB_BUILD_DEBUG}" == "ON" ]; then
    MR_CMAKE_OPTIONS="${MR_CMAKE_OPTIONS} -D MR_EMSCRIPTEN_BUILD_DEBUG=1"
  fi
fi

if [[ $OSTYPE == 'darwin'* ]]; then
  PYTHON_VERSION="3.10"
  if [ "${MESHLIB_PYTHON_VERSION}" != "" ]; then
    PYTHON_VERSION="${MESHLIB_PYTHON_VERSION}"
  fi
  PYTHON_PREFIX=$(python"${PYTHON_VERSION}"-config --prefix)
  echo "PYTHON_PREFIX=${PYTHON_PREFIX}"
  PYTHON_EXECUTABLE=$(which python"${PYTHON_VERSION}")
  PYTHON_LIBRARY=${PYTHON_PREFIX}/lib/libpython${PYTHON_VERSION}.dylib
  PYTHON_INCLUDE_DIR=${PYTHON_PREFIX}/include/python${PYTHON_VERSION}

  MR_CMAKE_OPTIONS="${MR_CMAKE_OPTIONS} \
    -D CMAKE_C_COMPILER=clang \
    -D CMAKE_CXX_COMPILER=clang++ \
    -D PYTHON_LIBRARY=${PYTHON_LIBRARY} \
    -D PYTHON_INCLUDE_DIR=${PYTHON_INCLUDE_DIR} \
    -D PYTHON_EXECUTABLE:FILEPATH=${PYTHON_EXECUTABLE} \
  "
fi

if [[ $OSTYPE == 'darwin'* ]]; then
  NPROC=$(sysctl -n hw.logicalcpu)
else
  NPROC=$(nproc)
fi

# exit if any command failed
set -eo pipefail

# build MeshSDK
if [ "${MESHLIB_KEEP_BUILD}" != "ON" ]; then
  # Use `rm -rf ./build/*` instead of `rm -rf ./build` to allow delete in docker volume
  rm -rf ./build/*
fi

# build Release
if [ "${MESHLIB_BUILD_RELEASE}" = "ON" ]; then
  if [ "${MESHLIB_KEEP_BUILD}" != "ON" ]; then
    mkdir -p build/Release
  fi
  cd build/Release
    cmake -S ../.. -B . -D CMAKE_BUILD_TYPE=Release ${MR_CMAKE_OPTIONS} | tee ${logfile}
    cmake --build . -j ${NPROC} | tee ${logfile}
  cd ../..
fi

# build Debug
if [ "${MESHLIB_BUILD_DEBUG}" = "ON" ]; then
  if [ "${MESHLIB_KEEP_BUILD}" != "ON" ]; then
    mkdir -p build/Debug
  fi
  cd build/Debug
    cmake -S ../.. -B . -D CMAKE_BUILD_TYPE=Debug ${MR_CMAKE_OPTIONS} | tee ${logfile}
    EMCC_DEBUG=1 cmake --build . -j ${NPROC} | tee ${logfile}
  cd ../..
fi

if [ "${MESHLIB_BUILD_RELEASE}" = "ON" ]; then
  printf "\rAutoinstall script successfully finished.\n\n"
else
  if [ "${MESHLIB_BUILD_DEBUG}" = "ON" ]; then
    printf "\rAutoinstall script successfully finished.\n\n"
  else
    printf "\rNothing was built.\n\n"
  fi
fi

if [ ! "${MR_EMSCRIPTEN_SDK}" = "ON" ]; then
  printf "\rYou could run ./build/Release/bin/MRTest next by serving MRTest.html.\n\n"
fi
