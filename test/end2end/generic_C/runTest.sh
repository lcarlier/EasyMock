#!/bin/bash

set -e
set -a
set -u
set -x

EASYMOCK_GENERATE=${1}
FILE_TO_MOCK=${2}
TEST_FILE_TO_COMPILE=${3}
EASYMOCK_EXTRA_PARAMS=${4}
GTEST_SOURCE_DIR=${5}
GTEST_BINARY_DIR=${6}
SOURCE_DIR=${7}
BINARY_DIR=${8}
DEBUG=${9}
C_COMPILER=${10}
CXX_COMPILER=${11}
CXX_STANDARD=${12}

FILE_TO_MOCK_BASE_NAME=$(basename "${FILE_TO_MOCK}")
FILE_TO_MOCK_BASE_NAME=${FILE_TO_MOCK_BASE_NAME%.*}

FILE_TO_COMPILE_BASE_NAME=$(basename "${TEST_FILE_TO_COMPILE}")
FILE_TO_COMPILE_BASE_NAME=${FILE_TO_COMPILE_BASE_NAME%.*}

TEST_DIR="${BINARY_DIR}/test/end2end/generic_C/${FILE_TO_MOCK_BASE_NAME}"

TEST_BINARY="${TEST_DIR}/test_${FILE_TO_MOCK_BASE_NAME}"

#from: https://stackoverflow.com/questions/45181115/portable-way-to-find-the-number-of-processors-cpus-in-a-shell-script
OS="$(uname -s)"
PLATFORM_DEP_PARAM=""
if [ "$OS" = "Darwin" ]; then
  PLATFORM_DEP_PARAM="-DTARGET_OS_IPHONE=0"
fi

mkdir -p "${TEST_DIR}"

${EASYMOCK_GENERATE} -i "${FILE_TO_MOCK}" -o "${TEST_DIR}" ${EASYMOCK_EXTRA_PARAMS[*]} ${PLATFORM_DEP_PARAM}

${C_COMPILER} \
  -c "${TEST_DIR}/easyMock_${FILE_TO_MOCK_BASE_NAME}.c" \
  -I "${SOURCE_DIR}/src/easyMockFramework/include" \
  -I "${SOURCE_DIR}/test/easyMockGenerate/include" \
  -I "${SOURCE_DIR}/test/end2end/generic_C" \
  -I "${TEST_DIR}" \
  -I "${GTEST_SOURCE_DIR}/include" \
  -o "${TEST_DIR}/easyMock_${FILE_TO_MOCK_BASE_NAME}.o"

${CXX_COMPILER} \
  -c "${TEST_FILE_TO_COMPILE}" \
  -std="c++${CXX_STANDARD}" \
  -I "${SOURCE_DIR}/src/easyMockFramework/include" \
  -I "${SOURCE_DIR}/test/easyMockGenerate/include" \
  -I "${SOURCE_DIR}/test/end2end/generic_C" \
  -I "${TEST_DIR}" \
  -I "${GTEST_SOURCE_DIR}/include" \
  -o "${TEST_DIR}/${FILE_TO_COMPILE_BASE_NAME}.o"

${CXX_COMPILER} \
  "-Wl,-rpath,${BINARY_DIR}/src/easyMockFramework/src" \
  "-L${BINARY_DIR}/src/easyMockFramework/src" \
  -std="c++${CXX_STANDARD}" \
  "${TEST_DIR}/easyMock_${FILE_TO_MOCK_BASE_NAME}.o" \
  "${TEST_DIR}/${FILE_TO_COMPILE_BASE_NAME}.o" \
  "${GTEST_BINARY_DIR}/libgtest_main.a" \
  "${GTEST_BINARY_DIR}/libgtest.a" \
  -lEasyMockFramework \
  -lpthread \
  -o "${TEST_BINARY}"

cd ${TEST_DIR}

${TEST_BINARY}
