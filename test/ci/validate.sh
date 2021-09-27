#!/bin/bash

set -e
set -u
set -o pipefail
set -x

C_COMPILER=$1
CXX_COMPILER=$2
BUILD_TYPE=$3
if [ "$#" -eq "4" ]; then
  EXTRA_CMAKE_PARAM=$4
else
  EXTRA_CMAKE_PARAM=""
fi

#from: https://stackoverflow.com/questions/45181115/portable-way-to-find-the-number-of-processors-cpus-in-a-shell-script
OS="$(uname -s)"
if [ "$OS" = "Linux" ]; then
  NPROCS="$(nproc --all)"
elif [ "$OS" = "Darwin" ]; then
  NPROCS="$(sysctl -n hw.ncpu)"
else
  error "OS $OS not supported"
fi

if [ "$OS" = "Linux" ]; then
  sudo apt update -y
  sudo apt install -y \
    gcc \
    g++ \
    clang \
    cmake \
    pkg-config \
    libunwind-dev \
    llvm-10-dev \
    libclang-10-dev \
    libncurses-dev \
    libboost-system-dev \
    libboost-filesystem-dev \
    libctemplate-dev \
    libdw-dev \
    doxygen \
    graphviz
elif [ "$OS" = "Darwin" ]; then
  brew install gcc
  brew install llvm
  brew install ctemplate
fi

export LSAN_OPTIONS=verbosity=1:log_threads=1
${C_COMPILER} --version
mkdir -p "build_${BUILD_TYPE}"
cd build_${BUILD_TYPE}
cmake -DCMAKE_C_COMPILER=${C_COMPILER} -DCMAKE_CXX_COMPILER=${CXX_COMPILER} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} "${EXTRA_CMAKE_PARAM}" ../
make all check -j ${NPROCS}
