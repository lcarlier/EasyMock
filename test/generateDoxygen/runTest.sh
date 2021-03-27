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
#
# Some older version of doxygen parses the file correctly (i.e. doesn't have the bug) and as such grep doesn't return
# any match. We use the { cmd || true; } trick to make the script pass in case grep is not getting any match.
# Remember that grep returns an error code if it doesn't match anything.
EXPECTED_WARNING=4
doxygen --version
NB_WARNING=$(doxygen docs/doxygen/Doxyfile 2>&1 | { grep -c "CodeGeneratorCTemplate\.h:.*warning" || true; })

# NB_WARNING can be 0 or 4 depending on the doxygen's version
if [ $((NB_WARNING)) -gt $((EXPECTED_WARNING)) ];
then
  echo "${NB_WARNING} warnings were found. ${EXPECTED_WARNING} expected"
  exit 1
else
  exit 0
fi
