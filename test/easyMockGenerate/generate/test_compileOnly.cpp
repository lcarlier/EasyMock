#include <gtest/gtest.h> // googletest header file

#include <TestTypes.h>

#include "genGenerate_testCase.h"

template<class T>
class compileOnly_testCase_0_49 : public genGenerate_testCase<T>
{
public:
  compileOnly_testCase_0_49() : genGenerate_testCase<T>()
  {
  }
};

TYPED_TEST_CASE(compileOnly_testCase_0_49, CompileOnlyTypes_0_49);

TYPED_TEST(compileOnly_testCase_0_49, compileOnly)
{
  //Nothing to do. All the magic is in the setup and teardown
}

template<class T>
using compileOnly_testCase_50_99 = compileOnly_testCase_0_49<T>;

TYPED_TEST_CASE(compileOnly_testCase_50_99, CompileOnlyTypes_50_99);

TYPED_TEST(compileOnly_testCase_50_99, compileOnly)
{
  //Nothing to do. All the magic is in the setup and teardown
}
