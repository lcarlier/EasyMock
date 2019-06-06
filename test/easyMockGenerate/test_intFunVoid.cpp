#include <gtest/gtest.h> // googletest header file

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include <boost/algorithm/string.hpp>

#include "test_common.h"

typedef int (*funPtr)();
typedef void (*funExpectPtr)(int rv);

class intFunVoid_testCase : public easyMockGenerate_baseTestCase
{
public:
  intFunVoid_testCase() : easyMockGenerate_baseTestCase("intFunVoid", "include/intFunVoid.h", "mockIntFunVoid")
  {
    Function *f = new Function("intFunVoid", "int",{});
    m_elem.push_back(f);
  }
};

TEST_F(intFunVoid_testCase, OneExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);

  int valueToExpect = 5;
  fptr_expect(5);
  int rv = fptr();

  EXPECT_EQ(rv, valueToExpect);
  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  const char *error = easyMock_getErrorStr();
  ASSERT_EQ(error, nullptr) << error;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(intFunVoid_testCase, ThreeExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);

  const unsigned int NB_EXPECT = 3;

  for(unsigned int expect_nr = 0; expect_nr < NB_EXPECT; expect_nr++)
  {
    fptr_expect(expect_nr);
  }

  for(unsigned int expect_nr = 0; expect_nr < NB_EXPECT; expect_nr++)
  {
    int rv = fptr();
    EXPECT_EQ(rv, expect_nr) << "with expect_nr == " << expect_nr;
  }

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  const char *error = easyMock_getErrorStr();
  ASSERT_EQ(error, nullptr) << error;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(intFunVoid_testCase, NoExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);
  fptr();
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, "Error : unexpected call of 'int intFunVoid()'. intFunVoid is returning a random value.\n\r\tat EasyMock::addError")) << error;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(intFunVoid_testCase, NotEnoughCall)
{
  int rv;
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);
  fptr_expect(4);
  fptr_expect(5);
  fptr_expect(6);
  rv = fptr();
  EXPECT_EQ(rv, 4);
  rv = fptr();
  EXPECT_EQ(rv, 5);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, "Error: For function 'int intFunVoid()' bad number of call. Expected 3, got 2\n\r")) << error;

  ASSERT_FALSE(isFifoCallEmpty());
  ASSERT_EQ(fifoCallSize(), 1);
  std::string curCall = getCurrentFifoCall();
  ASSERT_STREQ(curCall.c_str(), "int intFunVoid()");
}
