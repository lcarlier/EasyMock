#!/bin/bash

set -e
set -u
set -o pipefail
set -x

C_COMPILER=$1
CXX_COMPILER=$2
BUILD_TYPE=$3

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
  sudo apt install gcc -y
  sudo apt install g++ -y
  sudo apt install cmake -y
  sudo apt install pkg-config -y
  sudo apt install libunwind-dev -y
  sudo apt install llvm-10-dev -y
  sudo apt install libclang-10-dev -y
  sudo apt install libncurses-dev -y
  sudo apt install libboost-system-dev libboost-filesystem-dev -y
  sudo apt install libctemplate-dev -y
  sudo apt install libdw-dev -y
  sudo apt install doxygen
  sudo apt install graphviz
elif [ "$OS" = "Darwin" ]; then
  brew install gcc
  brew install llvm
  brew install ctemplate
fi

mkdir -p "build_${BUILD_TYPE}"
cd build_${BUILD_TYPE}
cmake -DCMAKE_C_COMPILER=${C_COMPILER} -DCMAKE_CXX_COMPILER=${CXX_COMPILER} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ../
make all check -j ${NPROCS}
