#!/bin/bash

set -e
set -a
set -u
set -x

EASYMOCK_GENERATE=${1}
GTEST_SOURCE_DIR=${2}
GTEST_BINARY_DIR=${3}
SOURCE_DIR=${4}
BINARY_DIR=${5}
DEBUG=${6}
CXX_COMPILER=${7}
CXX_STANDARD=${8}

TEST_DIR="${BINARY_DIR}/test/end2end/database_cpp_example"

mkdir -p "${TEST_DIR}"

#from: https://stackoverflow.com/questions/45181115/portable-way-to-find-the-number-of-processors-cpus-in-a-shell-script
OS="$(uname -s)"
PLATFORM_DEP_PARAM=""
if [ "$OS" = "Darwin" ]; then
  PLATFORM_DEP_PARAM="-DTARGET_OS_IPHONE=0"
fi

FILE_TO_MOCK="${SOURCE_DIR}/test/end2end/database_cpp_example/Database.hpp"

TEST_BINARY="${TEST_DIR}/test_database_example_cpp"

${EASYMOCK_GENERATE} -i "${FILE_TO_MOCK}" -o "${TEST_DIR}" --mock-cpp ${PLATFORM_DEP_PARAM}

${CXX_COMPILER} \
  -c "${TEST_DIR}/easyMock_Database.cpp" \
  -I "${SOURCE_DIR}/src/easyMockFramework/include" \
  -I "${SOURCE_DIR}/test/easyMockGenerate/include" \
  -I "${SOURCE_DIR}/test/end2end/database_cpp_example" \
  -I "${TEST_DIR}" \
  -I "${GTEST_SOURCE_DIR}/include" \
  -o "${TEST_DIR}/easyMock_Database.o" -g -O0

${CXX_COMPILER} \
  -c "${SOURCE_DIR}/test/end2end/database_cpp_example/test.cpp" \
  -std="c++${CXX_STANDARD}" \
  -I "${SOURCE_DIR}/src/easyMockFramework/include" \
  -I "${SOURCE_DIR}/test/easyMockGenerate/include" \
  -I "${SOURCE_DIR}/test/end2end/database_cpp_example" \
  -I "${TEST_DIR}" \
  -I "${GTEST_SOURCE_DIR}/include" \
  -o "${TEST_DIR}/test.o"  -g -O0

${CXX_COMPILER} \
  "-Wl,-rpath,${BINARY_DIR}/src/easyMockFramework/src" \
  "-L${BINARY_DIR}/src/easyMockFramework/src" \
  -std="c++${CXX_STANDARD}" \
  "${TEST_DIR}/easyMock_Database.o" \
  "${TEST_DIR}/test.o" \
  "${GTEST_BINARY_DIR}/libgtest_main.a" \
  "${GTEST_BINARY_DIR}/libgtest.a" \
  -lEasyMockFramework \
  -lpthread \
  -o "${TEST_BINARY}"  -g -O0

cd ${TEST_DIR}

${TEST_BINARY}