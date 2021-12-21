#!/bin/bash

set -e
set -a
set -u
set -x

EASYMOCK_GENERATE=$1
BINARY_DIR=$2
SOURCE_DIR=$3

TEST_DIR="${BINARY_DIR}/test/generateStructComparator"

declare -a TestTypeList=("usedType" "generatedType")

generateTypeRun=0
usedType=0
for testType in "${TestTypeList[@]}"; do

  mkdir -p "${TEST_DIR}/${testType}"

  if [ "${testType}" = "generatedType" ]; then
    ${EASYMOCK_GENERATE} \
    -i test/easyMockGenerate/include/structFunStruct.h \
    -o "${TEST_DIR}/${testType}" \
    --generate-types \
    --generate-comparator-of s2

    generateTypeRun=1
  elif [ "${testType}" = "usedType" ]; then
    ${EASYMOCK_GENERATE} \
    -i test/easyMockGenerate/include/structFunStruct.h \
    -o "${TEST_DIR}/${testType}" \
    --generate-comparator-of s2

    usedTypeRun=1
  else
    error "Wrong test type: ${testType}"
  fi

  ret=0
  gcc \
    -Wall \
    -Werror \
    -c "${SOURCE_DIR}/test/generateStructComparator/generateStructComparator.c" \
    -I "${TEST_DIR}/${testType}" \
    -I "${SOURCE_DIR}/src/easyMockFramework/include" \
    -I "${SOURCE_DIR}/test/easyMockGenerate/include" \
    -o "${TEST_DIR}/${testType}/generateStructComparator.o" 2> "${TEST_DIR}/${testType}/error.txt" || ret=$?

  echo "Compilation finished with status ${ret}"
  err_msg=$(cat "${TEST_DIR}/${testType}/error.txt")
  echo -e "Error message is\n${err_msg}"
  #Expect a compilation error because the format string doesn't match the arguments
  test "${ret}" -eq "1"

  # Check that the expected error is generated
  grep "error.*undeclared " "${TEST_DIR}/${testType}/error.txt" | grep "cmp_struct_onelineStruct"

  # Check that this error isn't generated
  ret=$(grep "error.*undeclared " "${TEST_DIR}/${testType}/error.txt" | grep -c "cmp_struct_s2" || ret=0)

  test "${ret}" -eq "0"

done

test "${generateTypeRun}" -eq "1"
test "${usedTypeRun}" -eq "1"
