#include <gtest/gtest.h> // googletest header file

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include <boost/algorithm/string.hpp>

#include "test_common.h"

typedef int (*funPtr)(int a, int b);
typedef void (*funExpectPtr)(int a, int b, int rv, EasyMock_Matcher match_a, EasyMock_Matcher match_b);

class intFunIntInt_testCase : public easyMockGenerate_baseTestCase
{
public:
  intFunIntInt_testCase() : easyMockGenerate_baseTestCase("intFunIntInt", "include/intFunIntInt.h", "mockIntFunIntInt")
  {
    Function *f = new Function("intFunIntInt", "int",{Parameter("int", "a"), Parameter("int", "b")});
    m_elem.push_back(f);
  }
};

TEST_F(intFunIntInt_testCase, OneExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);

  int aOneToExpect = 5;
  int aTwoToExpect = 6;
  int rvToExpect = 7;
  fptr_expect(aOneToExpect, aTwoToExpect, rvToExpect, cmp_int, cmp_int);
  int rv = fptr(aOneToExpect, aTwoToExpect);

  EXPECT_EQ(rv, rvToExpect);
  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  const char *error = easyMock_getErrorStr();
  ASSERT_EQ(error, nullptr) << error;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(intFunIntInt_testCase, OneExpectFirstArgBad)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);

  int aOneToExpect = 5;
  int aOneBadCall = 255;
  int aTwoToExpect = 6;
  int rvToExpect = 7;
  fptr_expect(aOneToExpect, aTwoToExpect, rvToExpect, cmp_int, cmp_int);
  int rv = fptr(aOneBadCall, aTwoToExpect);

  EXPECT_EQ(rv, rvToExpect);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, "Error : at call 1 of 'int intFunIntInt(int a, int b)': Parameter 'a' has value '255', was expecting '5'")) << error;

  ASSERT_TRUE(isFifoCallEmpty());
}

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

  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, "Error : at call 1 of 'int intFunIntInt(int a, int b)': Parameter 'b' has value '255', was expecting '6'")) << error;

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

  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, "Error : at call 2 of 'int intFunIntInt(int a, int b)': Parameter 'b' has value '255', was expecting '6'")) << error;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(intFunIntInt_testCase, ThreeExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);

  int aOneToExpect = 5;
  int aTwoToExpect = 6;
  int rvToExpect = 7;

  const unsigned int NB_EXPECT = 3;

  for(unsigned int expect_nr = 0; expect_nr < NB_EXPECT; expect_nr++)
  {
    fptr_expect(aOneToExpect + expect_nr, aTwoToExpect + expect_nr, rvToExpect + expect_nr, cmp_int, cmp_int);
  }

  for(unsigned int expect_nr = 0; expect_nr < NB_EXPECT; expect_nr++)
  {
    int rv = fptr(aOneToExpect + expect_nr, aTwoToExpect + expect_nr);
    EXPECT_EQ(rv, rvToExpect + expect_nr) << "with expect_nr == " << rvToExpect + expect_nr;
  }

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  const char *error = easyMock_getErrorStr();
  ASSERT_EQ(error, nullptr) << error;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(intFunIntInt_testCase, NoExpect)
{
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);

  int aOneToExpect = 5;
  int aTwoToExpect = 6;
  int rvToExpect = 7;

  int rv = fptr(aOneToExpect, aTwoToExpect);
  EXPECT_NE(rv, rvToExpect);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, "Error : unexpected call of 'int intFunIntInt(int a, int b)'. intFunIntInt is returning a random value.\n\r\tat EasyMock::addError")) << error;

  ASSERT_TRUE(isFifoCallEmpty());
}

TEST_F(intFunIntInt_testCase, NotEnoughCall)
{
  int rv;
  funPtr fptr;
  funExpectPtr fptr_expect;
  getFunPtr((void **)&fptr, (void **)&fptr_expect);

  int aOneToExpect = 5;
  int aTwoToExpect = 6;
  int rvToExpect = 7;

  fptr_expect(aOneToExpect + 0, aTwoToExpect + 0, rvToExpect + 0, cmp_int, cmp_int);
  fptr_expect(aOneToExpect + 1, aTwoToExpect + 1, rvToExpect + 1, cmp_int, cmp_int);
  fptr_expect(aOneToExpect + 2, aTwoToExpect + 2, rvToExpect + 2, cmp_int, cmp_int);

  rv = fptr(aOneToExpect + 0, aTwoToExpect + 0);
  EXPECT_EQ(rv, rvToExpect + 0);
  rv = fptr(aOneToExpect + 1, aTwoToExpect + 1);
  EXPECT_EQ(rv, rvToExpect + 1);

  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, "Error: For function 'int intFunIntInt(int a, int b)' bad number of call. Expected 3, got 2\n\r")) << error;

  ASSERT_FALSE(isFifoCallEmpty());
  ASSERT_EQ(fifoCallSize(), 1);
  std::string curCall = getCurrentFifoCall();
  ASSERT_STREQ(curCall.c_str(), "int intFunIntInt(int a, int b)");
}
