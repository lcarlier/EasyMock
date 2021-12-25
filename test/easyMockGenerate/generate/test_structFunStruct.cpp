#include <gtest/gtest.h> // googletest header file

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include <boost/algorithm/string.hpp>

#include "test_common.h"

#include "structFunStruct.h"
#include "EasyMock_CType.h"
#include "Function.h"
#include "ComposableType.h"
#include <StructFunStructFactory.h>

typedef struct s1 (*structFunStruct_funPtr)(struct s2);
typedef void (*structFunStruct_funExpectPtr)(struct s2 a, struct onelineStruct b, struct s1 rv, EasyMock_Matcher match_a, EasyMock_Matcher match_b);
typedef int (*structFunStruct_funMatcherPtr)(EASYMOCK_MATCHER_PARAM);

class structFunStruct_testCase : public easyMockGenerate_baseTestCase
{
public:
  structFunStruct_testCase() : easyMockGenerate_baseTestCase("structFunStruct", "include/structFunStruct.h", "mockStructFunStruct", false, true)
  {
    StructFunStructFactory factory;
    FunctionDeclaration f = factory.functionFactory();
    setComparatorToMatch("cmp_struct_s2");
    f.cacheHash();
    m_ctxt.addElementToMock(std::move(f));
  }
};

/*
 * Same as generic test case but test the matcher for positive case
 */
TEST_F(structFunStruct_testCase, OneExpect)
{
  structFunStruct_funPtr fptr;
  structFunStruct_funExpectPtr fptr_expect;
  structFunStruct_funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aToExpect;
  float fToExpect = 4.5;
  aToExpect.s.a = 6;
  aToExpect.s.b = 3.5;
  aToExpect.c = 9;
  aToExpect.d = &fToExpect;

  struct s1 returnValue;
  returnValue.a = 5;
  returnValue.b = 2.5;

  struct onelineStruct onelineStruct = {0};

  fptr_expect(aToExpect, onelineStruct, returnValue, fptr_matcher, nullptr);
  struct s1 rv = fptr(aToExpect);

  EXPECT_EQ(rv.a, returnValue.a);
  EXPECT_EQ(rv.b, returnValue.b);
  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(structFunStruct_testCase, OneExpectFirstElemtOfStructWrong)
{
  structFunStruct_funPtr fptr;
  structFunStruct_funExpectPtr fptr_expect;
  structFunStruct_funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aToExpect;
  float fToExpect = 4.5;
  aToExpect.s.a = 6;
  aToExpect.s.b = 3.5;
  aToExpect.c = 9;
  aToExpect.d = &fToExpect;

  struct s2 aWrongParam;
  aWrongParam.s.a = aToExpect.s.a;
  aWrongParam.s.b = aToExpect.s.b;
  aWrongParam.c = 8;
  aWrongParam.d = aToExpect.d;

  struct s1 returnValue;
  returnValue.a = 5;
  returnValue.b = 2.5;

  struct onelineStruct onelineStruct = {0};

  fptr_expect(aToExpect, onelineStruct, returnValue, fptr_matcher, nullptr);
  struct s1 rv = fptr(aWrongParam);

  EXPECT_EQ(rv.a, returnValue.a);
  EXPECT_EQ(rv.b, returnValue.b);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  std::string ERROR_EXPECT = "Error : at call 1 of 'struct s1 structFunStruct(struct s2 s, struct onelineStruct s2)': Parameter 's' which is a struct of type 's2' has field 'c' with value '8', was expecting '9'";
#if defined(BACKTRACE_SUPPORT)
  ERROR_EXPECT.append("\n\r\tat ");
#endif
  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, ERROR_EXPECT.c_str())) << "error: " << error << std::endl << "Expect: " << ERROR_EXPECT;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], ERROR_EXPECT.c_str())) << "errorArr[0]: " << errorArr[0] << std::endl << "Expect: " << ERROR_EXPECT;
  ASSERT_EQ(errorArr[1], nullptr) << "errorArr[1]: " << errorArr[1];

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(structFunStruct_testCase, OneExpectSecondElemtOfStructWrong)
{
  structFunStruct_funPtr fptr;
  structFunStruct_funExpectPtr fptr_expect;
  structFunStruct_funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aToExpect;
  float fToExpect = 4.5;
  aToExpect.s.a = 6;
  aToExpect.s.b = 3.5;
  aToExpect.c = 9;
  aToExpect.d = &fToExpect;

  struct s2 aWrongParam;
  float fToExpectWrongParam = 3.5;
  aWrongParam.s.a = aToExpect.s.a;
  aWrongParam.s.b = aToExpect.s.b;
  aWrongParam.c = aToExpect.c;
  aWrongParam.d = &fToExpectWrongParam;

  struct s1 returnValue;
  returnValue.a = 5;
  returnValue.b = 2.5;

  struct onelineStruct onelineStruct = {0};

  fptr_expect(aToExpect, onelineStruct, returnValue, fptr_matcher, nullptr);
  struct s1 rv = fptr(aWrongParam);

  EXPECT_EQ(rv.a, returnValue.a);
  EXPECT_EQ(rv.b, returnValue.b);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  //#define ERROR_EXPECT "Error : at call 1 of 'struct s1 structFunStruct(struct s2 s, struct onelineStruct s2)': Parameter 's' which is a struct of type 's2' has field 'd' with value '3.500000', was expecting '4.500000'\n\r\tat "
  std::stringstream ssToExpect;
  ssToExpect << static_cast<void *>(&fToExpect);
  std::stringstream ssToExpectWrongParam;
  ssToExpectWrongParam << static_cast<void *>(&fToExpectWrongParam);
  std::string errorToExpect("Error : at call 1 of 'struct s1 structFunStruct(struct s2 s, struct onelineStruct s2)': Parameter 's' which is a struct of type 's2' has field 'd' with value '");
  errorToExpect.append(ssToExpectWrongParam.str());
  errorToExpect.append("', was expecting '");
  errorToExpect.append(ssToExpect.str());
#if defined(BACKTRACE_SUPPORT)
  errorToExpect.append("'\n\r\tat ");
#else
  errorToExpect.append("'");
#endif
  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, errorToExpect.c_str())) << "error: " << error << std::endl << "errorToExpect: " << errorToExpect;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], errorToExpect.c_str())) << "errorArr[0]: " << errorArr[0] << std::endl << "errorToExpect: " << errorToExpect;
  ASSERT_EQ(errorArr[1], nullptr) << "errorArr[1]: " << errorArr[1];

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(structFunStruct_testCase, OneExpectSubStructWrong)
{
  structFunStruct_funPtr fptr;
  structFunStruct_funExpectPtr fptr_expect;
  structFunStruct_funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aToExpect;
  float fToExpect = 4.5;
  aToExpect.s.a = 6;
  aToExpect.s.b = 3.5;
  aToExpect.c = 9;
  aToExpect.d = &fToExpect;

  struct s2 aWrongParam;
  aWrongParam.s.a = aToExpect.s.a;
  aWrongParam.s.b = 2.5;
  aWrongParam.c = aToExpect.c;
  aWrongParam.d = aToExpect.d;

  struct s1 returnValue;
  returnValue.a = 5;
  returnValue.b = 2.5;

  struct onelineStruct onelineStruct = {0};

  fptr_expect(aToExpect, onelineStruct, returnValue, fptr_matcher, nullptr);
  struct s1 rv = fptr(aWrongParam);

  EXPECT_EQ(rv.a, returnValue.a);
  EXPECT_EQ(rv.b, returnValue.b);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  std::string ERROR_EXPECT = "Error : at call 1 of 'struct s1 structFunStruct(struct s2 s, struct onelineStruct s2)': Parameter 's.s' which is a struct of type 's1' has field 'b' with value '2.500000', was expecting '3.500000'";
#if defined(BACKTRACE_SUPPORT)
  ERROR_EXPECT.append("\n\r\tat ");
#endif
  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, ERROR_EXPECT.c_str())) << "error: " << error << std::endl << "Expect: " << ERROR_EXPECT;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], ERROR_EXPECT.c_str())) << "errorArr[0]: " << errorArr[0] << std::endl << "Expect: " << ERROR_EXPECT;
  ASSERT_EQ(errorArr[1], nullptr) << "errorArr[1]: " << errorArr[1];

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(structFunStruct_testCase, TwoExpectSecondCallArgBad)
{
  structFunStruct_funPtr fptr;
  structFunStruct_funExpectPtr fptr_expect;
  structFunStruct_funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aOneToExpect;
  float fOneToExpect = 4.5;
  aOneToExpect.s.a = 6;
  aOneToExpect.s.b = 3.5;
  aOneToExpect.c = 9;
  aOneToExpect.d = &fOneToExpect;
  struct s2 aTwoToExpect;
  float fTwoToExpect = 5.5;
  aTwoToExpect.s.a = 6;
  aTwoToExpect.s.b = 3.5;
  aTwoToExpect.c = 10;
  aTwoToExpect.d = &fTwoToExpect;
  struct s2 aTwoBadCall;
  float fTwoBadCall = 5.5;
  aTwoBadCall.s.a = aTwoToExpect.s.a;
  aTwoBadCall.s.b = aTwoToExpect.s.b;
  aTwoBadCall.c = 8;
  aTwoBadCall.d = &fTwoBadCall;
  struct s1 rvToExpect;
  rvToExpect.a = 42;
  rvToExpect.b = 6.5;

  struct onelineStruct onelineStruct = {0};

  fptr_expect(aOneToExpect, onelineStruct, rvToExpect, fptr_matcher, nullptr);
  fptr_expect(aTwoToExpect,onelineStruct, rvToExpect, fptr_matcher, nullptr);

  struct s1 rv = fptr(aOneToExpect);
  EXPECT_EQ(rv.a, rvToExpect.a);
  EXPECT_EQ(rv.b, rvToExpect.b);

  rv = fptr(aTwoBadCall);
  EXPECT_EQ(rv.a, rvToExpect.a);
  EXPECT_EQ(rv.b, rvToExpect.b);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  std::string ERROR_EXPECT = "Error : at call 2 of 'struct s1 structFunStruct(struct s2 s, struct onelineStruct s2)': Parameter 's' which is a struct of type 's2' has field 'c' with value '8', was expecting '10'";
#if defined(BACKTRACE_SUPPORT)
  ERROR_EXPECT.append("\n\r\tat ");
#endif    
  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, ERROR_EXPECT.c_str())) << error << std::endl << "Expect: " << ERROR_EXPECT;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], ERROR_EXPECT.c_str())) << "errorArr[0]: " << errorArr[0] << std::endl << "Expect: " << ERROR_EXPECT;
  ASSERT_EQ(errorArr[1], nullptr) << "errorArr[1]: " << errorArr[1];

  ASSERT_TRUE(isFifoCallEmpty());
}
