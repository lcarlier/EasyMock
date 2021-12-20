#include <gtest/gtest.h> // googletest header file

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include <boost/algorithm/string.hpp>

#include <VoidFunVoidFactory.h>

#include "test_common.h"
#include "Function.h"

typedef void (*funPtr)();
typedef void (*funExpectPtr)();

class voidFunVoid_testCase : public easyMockGenerate_baseTestCase
{
public:
  voidFunVoid_testCase() : easyMockGenerate_baseTestCase("voidFunVoid", "include/voidFunVoid.h", "mockVoidFunVoid", false, true)
  {
    VoidFunVoidFactory factory;
    FunctionDeclaration f = factory.functionFactory();
    m_ctxt.addElementToMock(std::move(f));
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

  EASYMOCK_ASSERT_NO_ERROR;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(voidFunVoid_testCase, NoExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);
  fptr();
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 2) << EasyMock_ErrorArrayPrinter(errorArr);
  std::string ERROR_EXPECT = "Error : unexpected call of 'void voidFunVoid()'.";
#if defined(BACKTRACE_SUPPORT)
  ERROR_EXPECT.append("\n\r\tat ");
#endif
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], ERROR_EXPECT.c_str())) << "errorArr[0]: " << errorArr[0];
  ASSERT_STREQ(errorArr[1], "Error: For function 'void voidFunVoid()' bad number of call. Expected 0, got 1") << "errorArr[1]: " << errorArr[1];
  ASSERT_EQ(errorArr[2], nullptr);

  ASSERT_TRUE(isFifoCallEmpty());
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

#define ERROR_TO_EXPECT "Error: For function 'void voidFunVoid()' bad number of call. Expected 3, got 2"
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
  ASSERT_STREQ(curCall.c_str(), "void voidFunVoid()");
}
