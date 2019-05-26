#include <gtest/gtest.h> // googletest header file

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include <boost/algorithm/string.hpp>

#include "test_common.h"

typedef void (*funPtr)();
typedef void (*funExpectPtr)();

class voidFunVoid_testCase : public easyMockGenerate_baseTestCase
{
public:
  voidFunVoid_testCase() : easyMockGenerate_baseTestCase("include/voidFunVoid.h", "mockVoidFunVoid")
  {
    Function *f = new Function("voidFunVoid", "void",{});
    m_elem.push_back(f);
  }
};

TEST_F(voidFunVoid_testCase, OneExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);
  fptr_expect();
  fptr();
  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  const char *error = easyMock_getErrorStr();
  ASSERT_EQ(error, nullptr) << error;
}

TEST_F(voidFunVoid_testCase, NoExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);
  fptr();
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, "Error : unexpected call of 'void voidFunVoid()'\n\r\tat EasyMock::addError")) << error;
}

TEST_F(voidFunVoid_testCase, NotEnoughCall)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);
  fptr_expect();
  fptr_expect();
  fptr_expect();
  fptr();
  fptr();
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, "Error: For function 'void voidFunVoid()' bad number of call. Expected 3, got 2\n\r")) << error;
}
