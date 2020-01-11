#include <gtest/gtest.h> // googletest header file

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include <boost/algorithm/string.hpp>

#include "test_common.h"
#include "EasyMockGenerateTypes.h"
#include "Function.h"
#include <IntFunIntIntFactory.h>

typedef int (*funPtr)(int a, int b);
typedef void (*funExpectPtr)(int a, int b, int rv, EasyMock_Matcher match_a, EasyMock_Matcher match_b);

class intFunIntInt_testCase : public easyMockGenerate_baseTestCase
{
public:
  intFunIntInt_testCase() : easyMockGenerate_baseTestCase("intFunIntInt", "include/intFunIntInt.h", "mockIntFunIntInt")
  {
    IntFunIntIntFactory factory;
    ElementToMock *f = factory.newFunctionFactory();
    m_elem.push_back(f);
  }
};

TEST_F(intFunIntInt_testCase, OneExpectSecondArgBad)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);

  int aOneToExpect = 5;
  int aTwoToExpect = 6;
  int aTwoBadCall = 255;
  int rvToExpect = 7;
  fptr_expect(aOneToExpect, aTwoToExpect, rvToExpect, cmp_int, cmp_int);
  int rv = fptr(aOneToExpect, aTwoBadCall);

  EXPECT_EQ(rv, rvToExpect);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

#define ERROR_EXPECT "Error : at call 1 of 'int intFunIntInt(int a, int b)': Parameter 'b' has value '255', was expecting '6'\n\r\tat EasyMock::addError"
  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, ERROR_EXPECT)) << error;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], ERROR_EXPECT)) << "errorArr[0]: " << errorArr[0];
  ASSERT_EQ(errorArr[1], nullptr) << "errorArr[1]: " << errorArr[1];
#undef ERROR_EXPECT

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(intFunIntInt_testCase, TwoExpectSecondCallArgBad)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);

  int aOneToExpect = 5;
  int aTwoToExpect = 6;
  int aTwoBadCall = 255;
  int rvToExpect = 7;

  fptr_expect(aOneToExpect, aTwoToExpect, rvToExpect, cmp_int, cmp_int);
  fptr_expect(aOneToExpect, aTwoToExpect, rvToExpect, cmp_int, cmp_int);

  int rv = fptr(aOneToExpect, aTwoToExpect);
  EXPECT_EQ(rv, rvToExpect);

  rv = fptr(aOneToExpect, aTwoBadCall);
  EXPECT_EQ(rv, rvToExpect);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

#define ERROR_EXPECT "Error : at call 2 of 'int intFunIntInt(int a, int b)': Parameter 'b' has value '255', was expecting '6'\n\r\tat EasyMock::addError"
  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, ERROR_EXPECT)) << error;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], ERROR_EXPECT)) << "errorArr[0]: " << errorArr[0];
  ASSERT_EQ(errorArr[1], nullptr) << "errorArr[1]: " << errorArr[1];
#undef ERROR_EXPECT

  ASSERT_TRUE(isFifoCallEmpty());
}
