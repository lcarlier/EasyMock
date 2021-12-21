#!/bin/bash

set -e
set -a
set -u
set -x

EASYMOCK_GENERATE=$1
BINARY_DIR=$2
SOURCE_DIR=$3

TEST_DIR="${BINARY_DIR}/test/generateStructComparatorTypeDef"

declare -a TestTypeList=("generatedType" "usedType")

generateTypeRun=0
usedType=0
for testType in "${TestTypeList[@]}"; do

  mkdir -p "${TEST_DIR}/${testType}"

  # WARNING: only TypedDefAnonymousStruct is generated.
  # TypedDefAnonymousStruct2 is not generated because it happens to be a typedef to the
  # exact same type as TypedDefAnonymousStruct and EasyMock doesn't deal yet with multiple typedef
  # to the same subtype as it is a corner case.
  if [ "${testType}" = "generatedType" ]; then
    ${EASYMOCK_GENERATE} \
    -i test/easyMockGenerate/include/structAnonymousTypedDefFunStructAnonymousTypedDef.h \
    -o "${TEST_DIR}/${testType}" \
    --generate-types \
    --generate-comparator-of TypedDefAnonymousStruct

    generateTypeRun=1
  elif [ "${testType}" = "usedType" ]; then
    ${EASYMOCK_GENERATE} \
    -i test/easyMockGenerate/include/structAnonymousTypedDefFunStructAnonymousTypedDef.h \
    -o "${TEST_DIR}/${testType}" \
    --generate-comparator-of TypedDefAnonymousStruct

    usedTypeRun=1
  else
    error "Wrong test type: ${testType}"
  fi

  ret=0
  gcc \
    -Wall \
    -Werror \
    -c "${SOURCE_DIR}/test/generateStructComparatorTypeDef/generateStructComparatorTypeDef.c" \
    -I "${TEST_DIR}/${testType}" \
    -I "${SOURCE_DIR}/src/easyMockFramework/include" \
    -I "${SOURCE_DIR}/test/easyMockGenerate/include" \
    -o "${TEST_DIR}/${testType}/generateStructComparatorTypeDef.o" 2> "${TEST_DIR}/${testType}/error.txt" || ret=$?

  echo "Compilation finished with status ${ret}"
  err_msg=$(cat "${TEST_DIR}/${testType}/error.txt")
  echo -e "Error message is\n${err_msg}"
  #No compilation error expected
  test "${ret}" -eq "0"

done

test "${generateTypeRun}" -eq "1"
test "${usedTypeRun}" -eq "1"
