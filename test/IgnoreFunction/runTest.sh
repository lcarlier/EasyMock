#!/bin/bash

set -e
set -a
set -u
set -x

EASYMOCK_GENERATE=$1
BINARY_DIR=$2
SOURCE_DIR=$3

TEST_DIR="${BINARY_DIR}/test/IgnoreFunction"

declare -a TestTypeList=("generatedType")

generateTypeRun=0
for testType in "${TestTypeList[@]}"; do

  mkdir -p "${TEST_DIR}/${testType}"

  if [ "${testType}" = "generatedType" ]; then
    ${EASYMOCK_GENERATE} \
    -i test/easyMockGenerate/include/compileTwoFunctions.h \
    -o "${TEST_DIR}/${testType}" \
    --generate-types \
    --ignore-generation-of f2

    generateTypeRun=1
  else
    error "Wrong test type: ${testType}"
  fi

  ret=0
  gcc \
    -Wall \
    -Werror \
    -c "${SOURCE_DIR}/test/IgnoreFunction/ignoreFunction.c" \
    -I "${TEST_DIR}/${testType}" \
    -I "${SOURCE_DIR}/src/easyMockFramework/include" \
    -I "${SOURCE_DIR}/test/easyMockGenerate/include" \
    -o "${TEST_DIR}/${testType}/ignoreFunction.o" 2> "${TEST_DIR}/${testType}/error.txt" || ret=$?

  err_msg=$(cat "${TEST_DIR}/${testType}/error.txt")
  echo "Compilation finished with status ${ret}"
  echo -e "Error message is\n${err_msg}"

  # Check that the expected error is generated
  grep "error.*implicit declaration of function " "${TEST_DIR}/${testType}/error.txt" | grep "f2_ExpectAndReturn"

  #Expect a compilation error because the format string doesn't match the arguments
  test "${ret}" -eq "1"

done

test "${generateTypeRun}" -eq "1"
