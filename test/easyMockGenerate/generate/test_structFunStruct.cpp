#include <gtest/gtest.h> // googletest header file

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include <boost/algorithm/string.hpp>

#include "test_common.h"

#include "structFunStruct.h"
#include "CType.h"
#include "Function.h"
#include "StructType.h"

typedef struct s1 (*funPtr)(struct s2);
typedef void (*funExpectPtr)(struct s2 a, struct s1 rv, EasyMock_Matcher match_a);
typedef int (*funMatcherPtr)(EASYMOCK_MATCHER_PARAM);

class structFunStruct_testCase : public easyMockGenerate_baseTestCase
{
public:
  structFunStruct_testCase() : easyMockGenerate_baseTestCase("structFunStruct", "include/structFunStruct.h", "mockStructFunStruct")
  {
    StructField *s1 = new StructField(new StructType("s1",{new StructField(CTYPE_INT, "a"), new StructField(CTYPE_FLOAT, "b")}), "s");
    Parameter* p = StructParameter("s2", "a", { new StructField(CTYPE_INT, "c"), new StructField(CTYPE_FLOAT, "d"), s1});
    Parameter::Vector funParameter = {p};
    ElementToMock *f = new Function("structFunStruct", StructReturnValue("s1"),funParameter);
    setParamToMatch("s2");
    m_elem.push_back(f);
  }
};

TEST_F(structFunStruct_testCase, OneExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aToExpect;
  aToExpect.s.a = 6;
  aToExpect.s.b = 3.5;
  aToExpect.c = 9;
  aToExpect.d = 4.5;

  struct s1 returnValue;
  returnValue.a = 5;
  returnValue.b = 2.5;

  fptr_expect(aToExpect, returnValue, fptr_matcher);
  struct s1 rv = fptr(aToExpect);

  EXPECT_EQ(rv.a, returnValue.a);
  EXPECT_EQ(rv.b, returnValue.b);
  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  ASSERT_NO_ERROR;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(structFunStruct_testCase, OneExpectFirstElemtOfStructWrong)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aToExpect;
  aToExpect.s.a = 6;
  aToExpect.s.b = 3.5;
  aToExpect.c = 9;
  aToExpect.d = 4.5;

  struct s2 aWrongParam;
  aWrongParam.s.a = aToExpect.s.a;
  aWrongParam.s.b = aToExpect.s.b;
  aWrongParam.c = 8;
  aWrongParam.d = aToExpect.d;

  struct s1 returnValue;
  returnValue.a = 5;
  returnValue.b = 2.5;

  fptr_expect(aToExpect, returnValue, fptr_matcher);
  struct s1 rv = fptr(aWrongParam);

  EXPECT_EQ(rv.a, returnValue.a);
  EXPECT_EQ(rv.b, returnValue.b);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  #define ERROR_EXPECT "Error : at call 1 of 'struct s1 structFunStruct(struct s2 a)': Parameter 'a' which is a struct of type 's2' has field 'c' with value '8', was expecting '9'\n\r\tat EasyMock::addError"
  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, ERROR_EXPECT)) << "error: " << error;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], ERROR_EXPECT)) << "errorArr[0]: " << errorArr[0];
  ASSERT_EQ(errorArr[1], nullptr) << "errorArr[1]: " << errorArr[1];
  #undef ERROR_EXPECT

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(structFunStruct_testCase, OneExpectSecondElemtOfStructWrong)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aToExpect;
  aToExpect.s.a = 6;
  aToExpect.s.b = 3.5;
  aToExpect.c = 9;
  aToExpect.d = 4.5;

  struct s2 aWrongParam;
  aWrongParam.s.a = aToExpect.s.a;
  aWrongParam.s.b = aToExpect.s.b;
  aWrongParam.c = aToExpect.c;
  aWrongParam.d = 3.5;

  struct s1 returnValue;
  returnValue.a = 5;
  returnValue.b = 2.5;

  fptr_expect(aToExpect, returnValue, fptr_matcher);
  struct s1 rv = fptr(aWrongParam);

  EXPECT_EQ(rv.a, returnValue.a);
  EXPECT_EQ(rv.b, returnValue.b);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  #define ERROR_EXPECT "Error : at call 1 of 'struct s1 structFunStruct(struct s2 a)': Parameter 'a' which is a struct of type 's2' has field 'd' with value '3.500000', was expecting '4.500000'\n\r\tat EasyMock::addError"
  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, ERROR_EXPECT)) << "error: " << error;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], ERROR_EXPECT)) << "errorArr[0]: " << errorArr[0];
  ASSERT_EQ(errorArr[1], nullptr) << "errorArr[1]: " << errorArr[1];
  #undef ERROR_EXPECT

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(structFunStruct_testCase, OneExpectSubStructWrong)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aToExpect;
  aToExpect.s.a = 6;
  aToExpect.s.b = 3.5;
  aToExpect.c = 9;
  aToExpect.d = 4.5;

  struct s2 aWrongParam;
  aWrongParam.s.a = aToExpect.s.a;
  aWrongParam.s.b = 2.5;
  aWrongParam.c = aToExpect.c;
  aWrongParam.d = aToExpect.d;

  struct s1 returnValue;
  returnValue.a = 5;
  returnValue.b = 2.5;

  fptr_expect(aToExpect, returnValue, fptr_matcher);
  struct s1 rv = fptr(aWrongParam);

  EXPECT_EQ(rv.a, returnValue.a);
  EXPECT_EQ(rv.b, returnValue.b);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  #define ERROR_EXPECT "Error : at call 1 of 'struct s1 structFunStruct(struct s2 a)': Parameter 'a.s' which is a struct of type 's1' has field 'b' with value '2.500000', was expecting '3.500000'\n\r\tat EasyMock::addError"
  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, ERROR_EXPECT)) << "error: " << error;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], ERROR_EXPECT)) << "errorArr[0]: " << errorArr[0];
  ASSERT_EQ(errorArr[1], nullptr) << "errorArr[1]: " << errorArr[1];
  #undef ERROR_EXPECT

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(structFunStruct_testCase, TwoExpectSecondCallArgBad)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aOneToExpect;
  aOneToExpect.s.a = 6;
  aOneToExpect.s.b = 3.5;
  aOneToExpect.c = 9;
  aOneToExpect.d = 4.5;
  struct s2 aTwoToExpect;
  aTwoToExpect.s.a = 6;
  aTwoToExpect.s.b = 3.5;
  aTwoToExpect.c = 10;
  aTwoToExpect.d = 5.5;
  struct s2 aTwoBadCall;
  aTwoBadCall.s.a = aTwoToExpect.s.a;
  aTwoBadCall.s.b = aTwoToExpect.s.b;
  aTwoBadCall.c = 8;
  aTwoBadCall.d = 5.5;
  struct s1 rvToExpect;
  rvToExpect.a = 42;
  rvToExpect.b = 6.5;

  fptr_expect(aOneToExpect, rvToExpect, fptr_matcher);
  fptr_expect(aTwoToExpect, rvToExpect, fptr_matcher);

  struct s1 rv = fptr(aOneToExpect);
  EXPECT_EQ(rv.a, rvToExpect.a);
  EXPECT_EQ(rv.b, rvToExpect.b);

  rv = fptr(aTwoBadCall);
  EXPECT_EQ(rv.a, rvToExpect.a);
  EXPECT_EQ(rv.b, rvToExpect.b);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

#define ERROR_EXPECT "Error : at call 2 of 'struct s1 structFunStruct(struct s2 a)': Parameter 'a' which is a struct of type 's2' has field 'c' with value '8', was expecting '10'\n\r\tat EasyMock::addError"
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

TEST_F(structFunStruct_testCase, ThreeExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aOneExpect;
  aOneExpect.c = 9;
  aOneExpect.d = 4.5;
  struct s1 rvToExpect;
  rvToExpect.a = 42;
  rvToExpect.b = 6.5;

  const unsigned int NB_EXPECT = 3;

  for(unsigned int expect_nr = 0; expect_nr < NB_EXPECT; expect_nr++)
  {
    struct s2 param = aOneExpect;
    param.c += expect_nr;
    param.d += expect_nr;
    struct s1 rvToExpectParam = rvToExpect;
    rvToExpectParam.a += expect_nr;
    rvToExpectParam.b += expect_nr;
    fptr_expect(param, rvToExpectParam, fptr_matcher);
  }

  for(unsigned int expect_nr = 0; expect_nr < NB_EXPECT; expect_nr++)
  {
    struct s2 param = aOneExpect;
    param.c += expect_nr;
    param.d += expect_nr;
    struct s1 rv = fptr(param);
    EXPECT_EQ(rv.a, rvToExpect.a + expect_nr) << "with expect_nr == " << expect_nr;
    EXPECT_EQ(rv.b, rvToExpect.b + expect_nr) << "with expect_nr == " << expect_nr;
  }

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  ASSERT_NO_ERROR;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(structFunStruct_testCase, NoExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aOneToExpect;
  aOneToExpect.c = 9;
  aOneToExpect.d = 4.5;
  struct s1 rvToExpect;
  rvToExpect.a = 42;
  rvToExpect.b = 6.5;

  struct s1 rv = fptr(aOneToExpect);
  EXPECT_NE(rv.a, rvToExpect.a);
  EXPECT_NE(rv.b, rvToExpect.b);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 2) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], "Error : unexpected call of 'struct s1 structFunStruct(struct s2 a)'. structFunStruct is returning a random value.\n\r\tat EasyMock::addError")) << "errorArr[0]: " << errorArr[0];
  ASSERT_STREQ(errorArr[1], "Error: For function 'struct s1 structFunStruct(struct s2 a)' bad number of call. Expected 0, got 1") << "errorArr[1]: " << errorArr[1];
  ASSERT_EQ(errorArr[2], nullptr);

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(structFunStruct_testCase, NotEnoughCall)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  funMatcherPtr fptr_matcher;
  getFunPtr((void **)&fptr, (void **)&fptr_expect, (void **)&fptr_matcher);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  ASSERT_NE(fptr_matcher, nullptr);

  struct s2 aOneExpect;
  aOneExpect.c = 9;
  aOneExpect.d = 4.5;
  struct s1 rvToExpect;
  rvToExpect.a = 42;
  rvToExpect.b = 6.5;

  const unsigned int NB_EXPECT = 3;

  for(unsigned int expect_nr = 0; expect_nr < NB_EXPECT; expect_nr++)
  {
    struct s2 param = aOneExpect;
    param.c += expect_nr;
    param.d += expect_nr;
    struct s1 rvToExpectParam = rvToExpect;
    rvToExpectParam.a += expect_nr;
    rvToExpectParam.b += expect_nr;
    fptr_expect(param, rvToExpectParam, fptr_matcher);
  }

  for(unsigned int expect_nr = 0; expect_nr < NB_EXPECT - 1; expect_nr++)
  {
    struct s2 param = aOneExpect;
    param.c += expect_nr;
    param.d += expect_nr;
    struct s1 rv = fptr(param);
    EXPECT_EQ(rv.a, rvToExpect.a + expect_nr) << "with expect_nr == " << expect_nr;
    EXPECT_EQ(rv.b, rvToExpect.b + expect_nr) << "with expect_nr == " << expect_nr;
  }

  int check = easyMock_check();
  EXPECT_EQ(check, 0);

#define ERROR_TO_EXPECT "Error: For function 'struct s1 structFunStruct(struct s2 a)' bad number of call. Expected 3, got 2"
  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_STREQ(error, ERROR_TO_EXPECT "\n\r") << "error: " << error;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1);
  ASSERT_STREQ(errorArr[0], ERROR_TO_EXPECT) << "errorArr[0]: " << errorArr[0];
  ASSERT_EQ(errorArr[1], nullptr);
#undef ERROR_TO_EXPECT

  ASSERT_FALSE(isFifoCallEmpty());
  ASSERT_EQ(fifoCallSize(), 1);
  std::string curCall = getCurrentFifoCall();
  ASSERT_STREQ(curCall.c_str(), "struct s1 structFunStruct(struct s2 a)");
}
