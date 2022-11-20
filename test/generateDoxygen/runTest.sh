#!/bin/bash

set -e
set -a
set -u
set -x

echo $PWD
echo $BASH
# In a perfect world, WARN_AS_ERROR should be set in the Doxyfile and this script shouldn't never exists.
# However, there is a bug in doxygen in which linking variables located inside an anonymous namespace via a \copydoc
# command in the documentation of another variable fails. There are some workaround to make doxygen happy however
# it implies modifying the code inside CodeGeneratorCTemplate.cpp which is not right.
# Hence we are just counting the expected number of generated warning to make sure no new one are introduced.
# The same goes for ComposableType::ComposableFieldTypeVector

# List of current errors:
# /EasyMockToTest/src/easyMockGenerate/include/CodeGeneratorCTemplate.h:27: warning: @copybrief or @copydoc target 'anonymous_namespace{CodeGeneratorCTemplate.cpp}::templateText' not found
# /EasyMockToTest/src/easyMockGenerate/include/CodeGeneratorCTemplate.h:27: warning: @copydetails or @copydoc target 'anonymous_namespace{CodeGeneratorCTemplate.cpp}::templateText' not found
# /EasyMockToTest/src/easyMockGenerate/include/CodeGeneratorCTemplate.h:27: warning: @copybrief or @copydoc target 'anonymous_namespace{CodeGeneratorCTemplate.cpp}::headerFileTemplate' not found
# /EasyMockToTest/src/easyMockGenerate/include/CodeGeneratorCTemplate.h:27: warning: @copydetails or @copydoc target 'anonymous_namespace{CodeGeneratorCTemplate.cpp}::headerFileTemplate' not found
# /EasyMockToTest/src/easyMockGenerate/include/ComposableType.h:34: warning: explicit link request to 'ComposableType::ComposableFieldTypeVector' could not be resolved
# /EasyMockToTest/src/easyMockGenerate/include/ComposableType.h:41: warning: explicit link request to 'ComposableType::ComposableFieldTypeVector' could not be resolved
# /EasyMockToTest/src/easyMockGenerate/include/FunctionDeclaration.h:33: warning: The following parameters of FunctionDeclaration::FunctionDeclaration(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters, std::shared_ptr< const Namespace > p_namespace, std::weak_ptr< const ComposableType > p_parentData={}) are not documented:
# /EasyMockToTest/src/easyMockGenerate/include/StructType.h:25: warning: explicit link request to 'ComposableType::ComposableFieldTypeVector' could not be resolved
# /EasyMockToTest/src/easyMockGenerate/include/UnionType.h:24: warning: explicit link request to 'ComposableType::ComposableFieldTypeVector' could not be resolved

EXPECTED_WARNING=9
doxygen --version
doxygen docs/doxygen/Doxyfile 2>&1 | tee out.log
set +e
NB_WARNING=$(grep -c ":.*warning" out.log)
set -e

# NB_WARNING can be 0 or 4 depending on the doxygen's version
if [ $((NB_WARNING)) -gt $((EXPECTED_WARNING)) ];
then
  #grep ":.*warning" out.log
  echo "${NB_WARNING} warnings were found. ${EXPECTED_WARNING} expected"
  exit 1
else
  echo "No warning were found."
  exit 0
fi
