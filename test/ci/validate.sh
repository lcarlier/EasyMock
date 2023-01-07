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
  sudo apt install -y lsb-release

  if [[ $(lsb_release -rs) == "20.04" ]]; then
    # "file" is for running the UTs as they use that tool
    sudo apt install -y \
      ${C_COMPILER} \
      g++ \
      clang \
      cmake \
      pkg-config \
      libunwind-dev \
      llvm-10-dev \
      libclang-10-dev \
      libclang-cpp10-dev \
      libncurses-dev \
      libboost-system-dev \
      libboost-filesystem-dev \
      libctemplate-dev \
      libdw-dev \
      doxygen \
      graphviz \
      file
  fi

  if [[ $(lsb_release -rs) == "22.04" ]]; then
    # "file" is for running the UTs as they use that tool
    sudo apt install -y \
      ${C_COMPILER} \
      g++ \
      clang \
      cmake \
      pkg-config \
      libunwind-dev \
      llvm-dev \
      libclang-dev \
      libclang-cpp-dev \
      libncurses-dev \
      libboost-system-dev \
      libboost-filesystem-dev \
      libctemplate-dev \
      libdw-dev \
      doxygen \
      graphviz \
      file
  fi

elif [ "$OS" = "Darwin" ]; then
  # Latest version of doxygen (1.9.3)has a regression
  # so version 1.8.13 is installed instead
  brew tap-new $USER/local-doxygen
  brew extract --version=1.8.13 doxygen $USER/local-doxygen
  brew install \
    cmake \
    pkgconfig \
    ncurses \
    gcc \
    llvm \
    ctemplate \
    doxygen@1.8.13 \
    boost \
    graphviz
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
