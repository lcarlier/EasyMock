#include <gtest/gtest.h> // googletest header file

#include <VoidFunStructWithArrayFactory.h>
#include <stddef.h>
#include <boost/algorithm/string.hpp>

#include "genGenerate_testCase.h"

typedef void (*funPtr)(struct structWithArray);
typedef void (*funExpect)(struct structWithArray, EasyMock_Matcher match_param);
typedef void (*funExpectPtr)(struct structWithArray, EasyMock_Matcher match_param);

class voidFunStrucWithArray_testCase : public genGenerate_testCase<VoidFunStructWithArrayFactory>
{
public:
  voidFunStrucWithArray_testCase() : genGenerate_testCase<VoidFunStructWithArrayFactory>()
  {
    setComparatorToMatch("cmp_struct_structWithArray");
  }
};

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

TEST_F(voidFunStrucWithArray_testCase, OneCallOk)
{
  funPtr fun = nullptr;
  EasyMock_Matcher cmpStruct = nullptr;
  funExpectPtr funExpect = nullptr;
  getFunPtr((void **) &fun, (void **) &funExpect, (void **)&cmpStruct, nullptr);

  ASSERT_TRUE(fun);
  ASSERT_TRUE(cmpStruct);
  ASSERT_TRUE(funExpect);

  struct structWithArray toExpect;
  toExpect.f = 6.;
  for(unsigned int arrayIdx = 0; arrayIdx < ARRAY_SIZE(toExpect.a); arrayIdx++)
  {
    toExpect.a[arrayIdx] = arrayIdx;
  }
  //Do not use b field because cmpStruct doesn't support it

  funExpect(toExpect, cmpStruct);

  fun(toExpect);

  int check = easyMock_check();
  ASSERT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;
}

TEST_F(voidFunStrucWithArray_testCase, OneCallArrayNOk)
{
  funPtr fun = nullptr;
  EasyMock_Matcher cmpStruct = nullptr;
  funExpectPtr funExpect = nullptr;
  getFunPtr((void **) &fun, (void **) &funExpect, (void **)&cmpStruct, nullptr);

  ASSERT_TRUE(fun);
  ASSERT_TRUE(cmpStruct);
  ASSERT_TRUE(funExpect);

  struct structWithArray toExpect;
  struct structWithArray actual;
  toExpect.f = 6.;
  actual.f = 6.;
  for(unsigned int arrayIdx = 0; arrayIdx < ARRAY_SIZE(toExpect.a); arrayIdx++)
  {
    toExpect.a[arrayIdx] = arrayIdx;
    actual.a[arrayIdx] = arrayIdx;
  }
  //Do not use b field because cmpStruct doesn't support it
  actual.a[2] = 42;

  funExpect(toExpect, cmpStruct);

  fun(actual);

  int check = easyMock_check();
  ASSERT_EQ(check, 0);

  const char *err = easyMock_getErrorStr();
  std::string errorMessageToExpect = ("Error : at call 1 of 'void voidFunStructWithArray(struct structWithArray param)': Parameter 'param' which is a struct of type 'structWithArray' has field array 'a[idx]' at idx == 2 with value '42', was expecting '2'");
#if defined(BACKTRACE_SUPPORT)
  errorMessageToExpect.append("\n\r\tat ");
#endif
  ASSERT_TRUE(boost::algorithm::starts_with(err, errorMessageToExpect)) << "err: " << err << std::endl << "errorMessageToExpect: " << errorMessageToExpect;
}

TEST_F(voidFunStrucWithArray_testCase, OneCallFieldNOk)
{
  funPtr fun = nullptr;
  EasyMock_Matcher cmpStruct = nullptr;
  funExpectPtr funExpect = nullptr;
  getFunPtr((void **) &fun, (void **) &funExpect, (void **)&cmpStruct, nullptr);

  ASSERT_TRUE(fun);
  ASSERT_TRUE(cmpStruct);
  ASSERT_TRUE(funExpect);

  struct structWithArray toExpect;
  struct structWithArray actual;
  toExpect.f = 6.;
  actual.f = 7.;
  for(unsigned int arrayIdx = 0; arrayIdx < ARRAY_SIZE(toExpect.a); arrayIdx++)
  {
    toExpect.a[arrayIdx] = arrayIdx;
    actual.a[arrayIdx] = arrayIdx;
  }
  //Do not use b field because cmpStruct doesn't support it

  funExpect(toExpect, cmpStruct);

  fun(actual);

  int check = easyMock_check();
  ASSERT_EQ(check, 0);

  const char *err = easyMock_getErrorStr();
  std::string errorMessageToExpect("Error : at call 1 of 'void voidFunStructWithArray(struct structWithArray param)': Parameter 'param' which is a struct of type 'structWithArray' has field 'f' with value '7.000000', was expecting '6.000000'");
#if defined(BACKTRACE_SUPPORT)
  errorMessageToExpect.append("\n\r\tat ");
#endif
  ASSERT_TRUE(boost::algorithm::starts_with(err, errorMessageToExpect)) << "err: " << err << std::endl << "errorMessageToExpect: " << errorMessageToExpect;
}
