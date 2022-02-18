#!/bin/bash

set -e
set -a
set -u
set -x

EASYMOCK_GENERATE=$1
BINARY_DIR=$2
SOURCE_DIR=$3

TEST_DIR="${BINARY_DIR}/test/IgnoreParserError"

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
    --ignore-parser-error

    generateTypeRun=1
  elif [ "${testType}" = "usedType" ]; then
    ${EASYMOCK_GENERATE} \
    -i test/easyMockGenerate/include/cppVoidFunVoid.h \
    -o "${TEST_DIR}/${testType}" \
    --ignore-parser-error

    usedTypeRun=1
  else
    error "Wrong test type: ${testType}"
  fi

done

test "${generateTypeRun}" -eq "1"
test "${usedTypeRun}" -eq "1"
