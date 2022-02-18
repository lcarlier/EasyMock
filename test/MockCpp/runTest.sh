#!/bin/bash

set -e
set -a
set -u
set -x

EASYMOCK_GENERATE=$1
BINARY_DIR=$2
SOURCE_DIR=$3

TEST_DIR="${BINARY_DIR}/test/MockCpp"

declare -a TestTypeList=("usedType" "generatedType")

generateTypeRun=0
usedType=0
for testType in "${TestTypeList[@]}"; do

  mkdir -p "${TEST_DIR}/${testType}"

  if [ "${testType}" = "generatedType" ]; then
    ${EASYMOCK_GENERATE} \
    -i test/easyMockGenerate/include/cppVoidFunVoid.h \
    -o "${TEST_DIR}/${testType}" \
    --generate-types \
    --mock-cpp

    generateTypeRun=1
  elif [ "${testType}" = "usedType" ]; then
    ${EASYMOCK_GENERATE} \
    -i test/easyMockGenerate/include/cppVoidFunVoid.h \
    -o "${TEST_DIR}/${testType}" \
    --mock-cpp

    usedTypeRun=1
  else
    error "Wrong test type: ${testType}"
  fi

  ret=0
  g++ \
    -Wall \
    -Werror \
    -c "${TEST_DIR}/${testType}/easyMock_cppVoidFunVoid.cpp"  \
    -I "${SOURCE_DIR}/src/easyMockFramework/include" \
    -I "${SOURCE_DIR}/test/easyMockGenerate/include" \
    -o "${TEST_DIR}/${testType}/easyMock_cppVoidFunVoid.o" 2> "${TEST_DIR}/${testType}/error.txt" || ret=$?

  err_msg=$(cat "${TEST_DIR}/${testType}/error.txt")
  echo "Compilation finished with status ${ret}"
  echo -e "Error message is\n${err_msg}"
  #Expect a compilation error because the function doesn't exists
  test "${ret}" -eq "0"


done

test "${generateTypeRun}" -eq "1"
test "${usedTypeRun}" -eq "1"
