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
EXPECTED_WARNING=8
doxygen --version
doxygen docs/doxygen/Doxyfile 2>&1 | tee out.log
grep ":.*warning" out.log
NB_WARNING=$(grep -c ":.*warning" out.log)

# NB_WARNING can be 0 or 4 depending on the doxygen's version
if [ $((NB_WARNING)) -gt $((EXPECTED_WARNING)) ];
then
  echo "${NB_WARNING} warnings were found. ${EXPECTED_WARNING} expected"
  exit 1
else
  exit 0
fi
