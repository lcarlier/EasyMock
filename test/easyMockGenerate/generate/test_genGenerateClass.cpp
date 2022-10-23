#include <gtest/gtest.h> // googletest header file

#include <sstream>

#include <TestTypes.h>

#include "test_genGenerateCommon.h"

#include "genGenerate_testCase.h"
#include <boost/algorithm/string.hpp>

template<typename T>
class genGenerate_testCaseClass : public genGenerate_testCase<T>
{
  genGenerate_testCaseClass() : genGenerate_testCase<T>(){}
};

using testing::Types;

typedef ::testing::Types
<
    CPP_CLASS_FACTORIES
> CppClassTypes;

TYPED_TEST_SUITE(genGenerate_testCaseClass, CppClassTypes);

TYPED_TEST(genGenerate_testCaseClass, OneExpectRightClassInstance)
{
  OneExpectTest<TypeParam>(*this, EasyMockTestCase::TestCaseClass::OneExpectRightClassInstance);
}

TYPED_TEST(genGenerate_testCaseClass, OneExpectWrongClassInstance)
{
  void *fptr;
  void *fptr_expect;
  auto f = genGenerate_testCase<TypeParam>::m_factory.functionFactory();
  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect);
  genGenerate_testCase<TypeParam>::m_factory.setupTestCase(EasyMockTestCase::TestCaseClass::OneExpectWrongClassInstance);

  /*
   * A lot of assumption here to be met partially by the setupTestCase function.
   * 1. The queue returns are types std::queue<std::tuple<Params...>>
   * 2. There is at least 1 element in the queue. The rest is ignored
   * 3. The first element of the tuple contains the parameter to be expected and actually given to the mock
   *    Those values differs because this test tests explicitly the error case
   *
   * We need to check the queues after setupTestCase and before the call_fptr_expect function has been called.
   */
  // We want to test the instance so we check the argument 0 of the function
  std::string givenParameter = getElementOfTupleInsideQueue<0>(0,
                               genGenerate_testCase<TypeParam>::m_factory.get_params_queue());
  std::string expectedParameter = getElementOfTupleInsideQueue<0>(0,
                               genGenerate_testCase<TypeParam>::m_factory.get_expects_queue());

  genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);
  auto expectedRv = genGenerate_testCase<TypeParam>::m_factory.get_expected_rv();
  auto rv = genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);
  EXPECT_EQ(rv, expectedRv);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);

  EXPECT_EQ(size, 1);

  std::string errorMessageToExpect{"Error : at call 1 of '"};
  errorMessageToExpect.append(f->getFunctionPrototype());
  errorMessageToExpect.push_back('\'');
  errorMessageToExpect.push_back(':');
  errorMessageToExpect.push_back(' ');
  errorMessageToExpect.append("Expecting this object being ");
  errorMessageToExpect.append(expectedParameter);
  errorMessageToExpect.append(", got this = ");
  errorMessageToExpect.append(givenParameter);

  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], errorMessageToExpect.c_str())) << "errorArr[0]: " << errorArr[0] << std::endl << "errorMessageToExpect: " << errorMessageToExpect;

  ASSERT_TRUE(isFifoCallEmpty());
}