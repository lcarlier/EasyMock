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
  # The name of the C compiler is also the name of the package in Ubuntu
  # E.g. by giving clang-7 we install clang-7
  sudo apt install -y \
    ${C_COMPILER} \
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
  brew install \
    cmake \
    pkgconfig \
    ncurses \
    gcc \
    llvm \
    ctemplate \
    doxygen \
    boost
  echo 'export PATH="/usr/local/opt/llvm/bin:$PATH"' >> /Users/runner/.bash_profile
fi

export LSAN_OPTIONS=verbosity=1:log_threads=1
${C_COMPILER} --version
BUILD_DIR="build_${C_COMPILER}_${BUILD_TYPE}"
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
cmake -DCMAKE_C_COMPILER=${C_COMPILER} -DCMAKE_CXX_COMPILER=${CXX_COMPILER} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} "${EXTRA_CMAKE_PARAM}" ../ | tee cmake_stdout.txt

# Check cmake has configured in the correct mode
grep "\-\- Building for ${BUILD_TYPE}" cmake_stdout.txt
test "$?" -eq "0"

make all check -j ${NPROCS} VERBOSE=1
