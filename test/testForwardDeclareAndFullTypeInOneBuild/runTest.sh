#!/bin/bash

set -e
set -a
set -u
set -x

EASYMOCK_GENERATE=$1
EASYMOCK_SRC_DIR=$2
CURRENT_BINARY_DIR=$3
CURRENT_SOURCE_DIR=$4

declare -a TestTypeList=("generatedType")

declare -a FileToGenerateList=("forwardDeclare" "fullDeclaration")

usedTypeRun=0
generateTypeRun=0
for testType in "${TestTypeList[@]}"; do

  type_current_binary_dir="${CURRENT_BINARY_DIR}/${testType}"
  mkdir -p "${type_current_binary_dir}"

  for fileToGenerate in "${FileToGenerateList[@]}"; do

    if [ "${testType}" = "usedType" ]; then
      ${EASYMOCK_GENERATE} \
        -i "${CURRENT_SOURCE_DIR}/${fileToGenerate}.h" \
        -o "${type_current_binary_dir}"
    elif [ "${testType}" = "generatedType" ]; then
      ${EASYMOCK_GENERATE} \
        -i "${CURRENT_SOURCE_DIR}/${fileToGenerate}.h" \
        -o "${type_current_binary_dir}" \
        --generate-types
    else
      error "Wrong test type: ${testType}"
    fi

    ret=0
    gcc \
      -Wall \
      -Werror \
      -I "${type_current_binary_dir}" \
      -c "${type_current_binary_dir}/easyMock_${fileToGenerate}.c" \
      -I "${CURRENT_SOURCE_DIR}" \
      -I "${EASYMOCK_SRC_DIR}/src/easyMockFramework/include" \
      -I "${EASYMOCK_SRC_DIR}/test/easyMockGenerate/include" \
      -o "${type_current_binary_dir}/easyMock_${fileToGenerate}.o" 2> "${type_current_binary_dir}/error.txt" || ret=$?

    err_msg=$(cat "${type_current_binary_dir}/error.txt")
    echo "Compilation finished with status ${ret}"
    echo -e "Error message is\n${err_msg}"
    test "${ret}" -eq "0"

  done

  ret=0
  gcc \
    -Wall \
    -Werror \
    -c "${CURRENT_SOURCE_DIR}/main.c" \
    -I "${type_current_binary_dir}" \
    -I "${EASYMOCK_SRC_DIR}/src/easyMockFramework/include" \
    -I "${EASYMOCK_SRC_DIR}/test/easyMockGenerate/include" \
    -o "${type_current_binary_dir}/main.o" 2> "${type_current_binary_dir}/error.txt" || ret=$?

  err_msg=$(cat "${type_current_binary_dir}/error.txt")
  echo "Compilation finished with status ${ret}"
  echo -e "Error message is\n${err_msg}"
  test "${ret}" -eq "0"

  gcc \
    -g \
    "${type_current_binary_dir}/easyMock_forwardDeclare.o" \
    "${type_current_binary_dir}/easyMock_fullDeclaration.o" \
    "${type_current_binary_dir}/main.o" \
    -o testForwardDeclareAndFullTypeInOneBuild \
    -Wl,-rpath,"${EASYMOCK_SRC_DIR}/src/easyMockFramework/src" \
    src/libEasyMockFramework.so

  ${type_current_binary_dir}/testForwardDeclareAndFullTypeInOneBuild

  #Expect a compilation error because the format string doesn't match the arguments
  test "${ret}" -eq "0"

  if [ "${testType}" = "usedType" ]; then
    usedTypeRun=1
  elif [ "${testType}" = "generatedType" ]; then
    generateTypeRun=1
  else
    error "Wrong test type: ${testType}"
  fi
done

test "${usedTypeRun}" -eq "1"
test "${generateTypeRun}" -eq "1"
