#include <gtest/gtest.h> // googletest header file

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include <boost/algorithm/string.hpp>

#include "test_common.h"
#include <IntFunVoidFactory.h>
#include "Function.h"

typedef int (*funPtr)();
typedef void (*funExpectPtr)(int rv);

class intFunVoid_testCase : public easyMockGenerate_baseTestCase
{
public:

  intFunVoid_testCase() : easyMockGenerate_baseTestCase("intFunVoid", "include/intFunVoid.h", "mockIntFunVoid", false, true, false)
  {
    IntFunVoidFactory factory;
    auto f = factory.functionFactory();
    f->cacheHash();
    m_ctxt.addElementToMock(std::move(f));
  }
};

TEST_F(intFunVoid_testCase, OneExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **) &fptr, (void **) &fptr_expect);

  int valueToExpect = 5;
  fptr_expect(5);
  int rv = fptr();

  EXPECT_EQ(rv, valueToExpect);
  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(intFunVoid_testCase, ThreeExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **) &fptr, (void **) &fptr_expect);

  const unsigned int NB_EXPECT = 3;

  for (unsigned int expect_nr = 0; expect_nr < NB_EXPECT; expect_nr++)
  {
    fptr_expect(expect_nr);
  }

  for (unsigned int expect_nr = 0; expect_nr < NB_EXPECT; expect_nr++)
  {
    int rv = fptr();
    EXPECT_EQ(rv, expect_nr) << "with expect_nr == " << expect_nr;
  }

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(intFunVoid_testCase, NoExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **) &fptr, (void **) &fptr_expect);
  fptr();
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 2) << EasyMock_ErrorArrayPrinter(errorArr);
  std::string ERROR_EXPECT = "Error : unexpected call of 'int intFunVoid()'. intFunVoid is returning a random value.";
#if defined(BACKTRACE_SUPPORT)
  ERROR_EXPECT.append("\n\r\tat ");
#endif
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], ERROR_EXPECT.c_str())) << "errorArr[0]: " << errorArr[0];
  ASSERT_STREQ(errorArr[1], "Error: For function 'int intFunVoid()' bad number of call. Expected 0, got 1") << "errorArr[1]: " << errorArr[1];
  ASSERT_EQ(errorArr[2], nullptr);

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(intFunVoid_testCase, NotEnoughCall)
{
  int rv;
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **) &fptr, (void **) &fptr_expect);
  fptr_expect(4);
  fptr_expect(5);
  fptr_expect(6);
  rv = fptr();
  EXPECT_EQ(rv, 4);
  rv = fptr();
  EXPECT_EQ(rv, 5);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);
#define ERROR_TO_EXPECT "Error: For function 'int intFunVoid()' bad number of call. Expected 3, got 2"
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
  const std::string& curCall = getCurrentFifoCall();
  ASSERT_STREQ(curCall.c_str(), "int intFunVoid()");
}
