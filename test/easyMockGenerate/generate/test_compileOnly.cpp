#include <gtest/gtest.h> // googletest header file

#include <TestTypes.h>

#include "genGenerate_testCase.h"

template<class T>
class compileOnly_testCase : public genGenerate_testCase<T>
{
public:
  compileOnly_testCase() : genGenerate_testCase<T>()
  {
  }
};

TYPED_TEST_SUITE(compileOnly_testCase, CompileOnlyTypes);

TYPED_TEST(compileOnly_testCase, compileOnly)
{
  //Nothing to do. All the magic is in the setup and teardown
}
