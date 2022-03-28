#include <gtest/gtest.h> // googletest header file

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include <boost/algorithm/string.hpp>

#include "test_common.h"

#include "genGenerate_testCase.h"
#include "EasyMock_CType.h"
#include "Function.h"
#include "ComposableType.h"
#include "StructCommonHelper.h"
#include <StructWithUnionFunStructWithUnionFactory.h>

#include <TestTypes.h>

template<class T>
class voidFunComposableTypeWithComposableType_testCase : public genGenerate_testCase<T>
{
public:
  voidFunComposableTypeWithComposableType_testCase() : genGenerate_testCase<T>()
  {
    this->setComparatorToMatch(genGenerate_testCase<T>::m_factory.getMatcherFunctionName());
  }
};

TYPED_TEST_SUITE(voidFunComposableTypeWithComposableType_testCase, VoidFunComposableTypeWithComposableTypeTypes);

/*
 * Same as generic test case but test the matcher for positive case
 */
TYPED_TEST(voidFunComposableTypeWithComposableType_testCase, OneExpect)
{
  void *fptr;
  void *fptr_expect;
  EasyMock_Matcher fptr_matcher;
  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);
  genGenerate_testCase<TypeParam>::m_factory.setupTestCaseAndMatcher(EasyMockTestCase::OneExpect, fptr_matcher);

  genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);

  auto expectedRv = genGenerate_testCase<TypeParam>::m_factory.get_expected_rv();
  auto rv = genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);

  EXPECT_EQ(rv, expectedRv);

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;

  ASSERT_TRUE(isFifoCallEmpty());
}

TYPED_TEST(voidFunComposableTypeWithComposableType_testCase, OneExpectFieldOfSubComposableElementWrong)
{
  void *fptr;
  void *fptr_expect;
  EasyMock_Matcher fptr_matcher;
  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);
  genGenerate_testCase<TypeParam>::m_factory.setupTestCaseAndMatcher(EasyMockTestCase::OneExpectArgIsBad, fptr_matcher);

  genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);

  auto expectedRv = genGenerate_testCase<TypeParam>::m_factory.get_expected_rv();
  auto rv = genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);

  EXPECT_EQ(rv, expectedRv);

  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  Function curElem = genGenerate_testCase<TypeParam>::m_factory.functionFactory();
  std::string errorToExpect("Error : at call 1 of '");
  errorToExpect.append(curElem.getFunctionPrototype());
  errorToExpect.append("': Parameter '");
  errorToExpect.append(genGenerate_testCase<TypeParam>::m_factory.getFieldWrongName());
  errorToExpect.append("' which is a");
  errorToExpect.append(genGenerate_testCase<TypeParam>::m_factory.getSubComposableTypeType());
  errorToExpect.append(" of type '");
  errorToExpect.append(genGenerate_testCase<TypeParam>::m_factory.getSubFieldWrongTypeName());
  errorToExpect.append("' has field '");
  errorToExpect.append(genGenerate_testCase<TypeParam>::m_factory.getSubFieldWrongName());
  errorToExpect.append("' with value '");
  //#define ERROR_EXPECT "Error : at call 1 of 'sWithUnion structWithUnionFunStructWithUnion(sWithUnion st)': Parameter 'st' which is an union of type 'ut' has field 'a' with value '43', was expecting '42'\n\r\tat "
  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, errorToExpect.c_str())) << "error: " << error << std::endl << "Expect: " << errorToExpect;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], errorToExpect.c_str())) << "errorArr[0]: " << errorArr[0] << std::endl << "Expect: " << errorToExpect;
  ASSERT_EQ(errorArr[1], nullptr) << "errorArr[1]: " << errorArr[1];
  //#undef ERROR_EXPECT

  ASSERT_TRUE(isFifoCallEmpty());
}
//No other UT over second field bad because union shares the same memory region so if everything is wrong, the first test is going to trigger the error
