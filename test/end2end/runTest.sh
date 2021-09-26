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

FILE_TO_MOCK_BASE_NAME=$(basename "${FILE_TO_MOCK}")
FILE_TO_MOCK_BASE_NAME=${FILE_TO_MOCK_BASE_NAME%.*}

FILE_TO_COMPILE_BASE_NAME=$(basename "${TEST_FILE_TO_COMPILE}")
FILE_TO_COMPILE_BASE_NAME=${FILE_TO_COMPILE_BASE_NAME%.*}

TEST_DIR="${BINARY_DIR}/test/end2end/${FILE_TO_MOCK_BASE_NAME}"

TEST_BINARY="${TEST_DIR}/test_${FILE_TO_MOCK_BASE_NAME}"

GTEST_LIB_POSTFIX=""

if [ $((DEBUG)) -eq 1 ];
then
  GTEST_LIB_POSTFIX="d"
fi

mkdir -p "${TEST_DIR}"

${EASYMOCK_GENERATE} -i "${FILE_TO_MOCK}" -o "${TEST_DIR}" ${EASYMOCK_EXTRA_PARAMS[*]}

${C_COMPILER} \
  -c "${TEST_DIR}/easyMock_${FILE_TO_MOCK_BASE_NAME}.c" \
  -I "${SOURCE_DIR}/src/easyMockFramework/include" \
  -I "${SOURCE_DIR}/test/easyMockGenerate/include" \
  -I "${SOURCE_DIR}/test/end2end" \
  -I "${TEST_DIR}" \
  -I "${GTEST_SOURCE_DIR}/include" \
  -o "${TEST_DIR}/easyMock_${FILE_TO_MOCK_BASE_NAME}.o"

${CXX_COMPILER} \
  -c "${TEST_FILE_TO_COMPILE}" \
  -I "${SOURCE_DIR}/src/easyMockFramework/include" \
  -I "${SOURCE_DIR}/test/easyMockGenerate/include" \
  -I "${SOURCE_DIR}/test/end2end" \
  -I "${TEST_DIR}" \
  -I "${GTEST_SOURCE_DIR}/include" \
  -o "${TEST_DIR}/${FILE_TO_COMPILE_BASE_NAME}.o"

${CXX_COMPILER} \
  "-Wl,-rpath,${BINARY_DIR}/src/easyMockFramework/src" \
  "-L${BINARY_DIR}/src/easyMockFramework/src" \
  "${TEST_DIR}/easyMock_${FILE_TO_MOCK_BASE_NAME}.o" \
  "${TEST_DIR}/${FILE_TO_COMPILE_BASE_NAME}.o" \
  "${GTEST_BINARY_DIR}/libgtest_main${GTEST_LIB_POSTFIX}.a" \
  "${GTEST_BINARY_DIR}/libgtest${GTEST_LIB_POSTFIX}.a" \
  -lEasyMockFramework \
  -lpthread \
  -o "${TEST_BINARY}"

cd ${TEST_DIR}

${TEST_BINARY}
