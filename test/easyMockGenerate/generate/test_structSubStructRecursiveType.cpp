#include <gtest/gtest.h>

#include <StructSubStructRecursiveTypeFactory.h>

#include "genGenerate_testCase.h"

#include <string>
#include <boost/algorithm/string.hpp>

typedef int (*funPtr)(struct st1 s);
typedef void (*funExpectPtr)(struct st1 s, EasyMock_Matcher match_st1);

class StructSubStructRecursiveType_testCase : public genGenerate_testCase<StructSubStructRecursiveTypeFactory>
{
public:
  StructSubStructRecursiveType_testCase() : genGenerate_testCase<StructSubStructRecursiveTypeFactory>()
  {
    setComparatorToMatch("cmp_struct_st1");
  }
};

TEST_F(StructSubStructRecursiveType_testCase, OneCallOk)
{
  funPtr fun = nullptr;
  funExpectPtr funExpect = nullptr;
  EasyMock_Matcher cmpStruct = nullptr;
  getFunPtr((void **) &fun, (void **)&funExpect, (void **)&cmpStruct, nullptr);

  ASSERT_TRUE(fun);
  ASSERT_TRUE(funExpect);
  ASSERT_TRUE(cmpStruct);

  //Initialise with dummy pointer value because this is what we are checking
  struct st1 s;
  s.st1SubSt2.st2SubSt1 = (struct st1 *)0xcafebabe;
  s.st1SubSt2.st2SubSt2 = (struct st2 *)0xdeadbeef;

  funExpect(s, cmpStruct);

  fun(s);

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;
}

TEST_F(StructSubStructRecursiveType_testCase, FirstRecursBad)
{
  funPtr fun = nullptr;
  funExpectPtr funExpect = nullptr;
  EasyMock_Matcher cmpStruct = nullptr;
  getFunPtr((void **) &fun, (void **)&funExpect, (void **)&cmpStruct, nullptr);

  ASSERT_TRUE(fun);
  ASSERT_TRUE(funExpect);
  ASSERT_TRUE(cmpStruct);

  struct st1 sToExpect;
  sToExpect.st1SubSt2.st2SubSt1 = (struct st1*)0xf00;
  sToExpect.st1SubSt2.st2SubSt2 = (struct st2*)0xba3;

  struct st1 sGiven = sToExpect;
  sGiven.st1SubSt2.st2SubSt1 = (struct st1*)0xfff;

  funExpect(sToExpect, cmpStruct);

  fun(sGiven);

  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  std::string errorToExpect("Error : at call 1 of 'void structSubStructRecursiveType(struct st1 st1Val)': Parameter 'st1Val.st1SubSt2' which is a struct of type 'st2' has field 'st2SubSt1' with value '0xfff', was expecting '0xf00'");
#if defined(BACKTRACE_SUPPORT)
  errorToExpect.append("\n\r\tat");
#endif
  const char *err = easyMock_getErrorStr();
  ASSERT_TRUE(err);
  ASSERT_TRUE(boost::algorithm::starts_with(err, errorToExpect)) << "err: " << err << std::endl << "errorMessageToExpect: " << errorToExpect;
}

TEST_F(StructSubStructRecursiveType_testCase, SecondRecursBad)
{
  funPtr fun = nullptr;
  funExpectPtr funExpect = nullptr;
  EasyMock_Matcher cmpStruct = nullptr;
  getFunPtr((void **) &fun, (void **)&funExpect, (void **)&cmpStruct, nullptr);

  ASSERT_TRUE(fun);
  ASSERT_TRUE(funExpect);
  ASSERT_TRUE(cmpStruct);

  struct st1 sToExpect;
  sToExpect.st1SubSt2.st2SubSt1 = (struct st1*)0xf00;
  sToExpect.st1SubSt2.st2SubSt2 = (struct st2*)0xba3;

  struct st1 sGiven = sToExpect;
  sGiven.st1SubSt2.st2SubSt2 = (struct st2*)0xba2;

  funExpect(sToExpect, cmpStruct);

  fun(sGiven);

  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  std::string errorToExpect("Error : at call 1 of 'void structSubStructRecursiveType(struct st1 st1Val)': Parameter 'st1Val.st1SubSt2' which is a struct of type 'st2' has field 'st2SubSt2' with value '0xba2', was expecting '0xba3'");
#if defined(BACKTRACE_SUPPORT)
  errorToExpect.append("\n\r\tat");
#endif
  const char *err = easyMock_getErrorStr();
  ASSERT_TRUE(err);
  ASSERT_TRUE(boost::algorithm::starts_with(err, errorToExpect)) << "err: " << err << std::endl << "errorMessageToExpect: " << errorToExpect;
}
