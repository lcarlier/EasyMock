#!/bin/bash

set -e
set -a
set -u
set -x

EASYMOCK_GENERATE=$1
BINARY_DIR=$2
SOURCE_DIR=$3

TEST_DIR="${BINARY_DIR}/test/IgnoreTypeField"

declare -a TestTypeList=("generatedType")

generateTypeRun=0
for testType in "${TestTypeList[@]}"; do

  mkdir -p "${TEST_DIR}/${testType}"

  if [ "${testType}" = "generatedType" ]; then
    ${EASYMOCK_GENERATE} \
    -i test/easyMockGenerate/include/ignoreTypeField.h \
    -o "${TEST_DIR}/${testType}" \
    --generate-types \
    --ignore-field-generation-of type_to_ignore
    generateTypeRun=1
  else
    error "Wrong test type: ${testType}"
  fi

  ret=0
  gcc \
    -Wall \
    -Werror \
    -c "${SOURCE_DIR}/test/IgnoreTypeField/ignoreTypeField.c" \
    -I "${TEST_DIR}/${testType}" \
    -I "${SOURCE_DIR}/src/easyMockFramework/include" \
    -I "${SOURCE_DIR}/test/easyMockGenerate/include" \
    -o "${TEST_DIR}/${testType}/ignoreTypeField.o" 2> "${TEST_DIR}/${testType}/error.txt" || ret=$?

  err_msg=$(cat "${TEST_DIR}/${testType}/error.txt")
  echo "Compilation finished with status ${ret}"
  echo -e "Error message is\n${err_msg}"

  # Check that the expected error is generated
  grep "error.*no member named.*a" "${TEST_DIR}/${testType}/error.txt" | grep "struct type_to_ignore"

  #Expect a compilation error because the format string doesn't match the arguments
  test "${ret}" -eq "1"

done

test "${generateTypeRun}" -eq "1"
