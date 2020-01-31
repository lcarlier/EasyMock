#include <gtest/gtest.h> // googletest header file

#include <IntFunStructPtrIntCharPtrFactory.h>
#include <StructCommonHelper.h>
#include <stddef.h>

#include "test_common.h"

#include "genGenerate_testCase.h"

typedef int (*funPtr)(struct s2*, int a, char* c);
typedef void (*funExpect)(struct s2*, int a, char *c, int rv, EasyMock_Matcher match_s2, EasyMock_Matcher match_a, EasyMock_Matcher match_c);
typedef void (*funExpectOutputPtr)(struct s2*, int a, char *c, int rv, EasyMock_Matcher match_s2, EasyMock_Matcher match_a, EasyMock_Matcher match_c, struct s2* s2_out, char *c_out);

class intFunStructPtrIntCharPtr_testCase : public genGenerate_testCase<IntFunStructPtrIntCharPtrFactory>
{
public:
  intFunStructPtrIntCharPtr_testCase() : genGenerate_testCase<IntFunStructPtrIntCharPtrFactory>()
  {
    setStructTypeToMatch("s2");
  }
};

TEST_F(intFunStructPtrIntCharPtr_testCase, OnePtrOut)
{
  funPtr fun = nullptr;
  void *cmpStruct = nullptr;
  funExpectOutputPtr funExpectOutput = nullptr;
  getFunPtr((void **) &fun, nullptr, &cmpStruct, (void **) &funExpectOutput);

  ASSERT_TRUE(fun);
  ASSERT_TRUE(cmpStruct);
  ASSERT_TRUE(funExpectOutput);

  struct s2 sOut;
  struct s2 s2ExpectOut;
  float fToExpect = 2;
  s2ExpectOut.c = 1;
  s2ExpectOut.d = &fToExpect;
  s2ExpectOut.s.a = 3;
  s2ExpectOut.s.b = 4;

  int aToExpect = 5;

  char cOut;
  char cToExpectOut = 'c';

  int rvToExpect = 6;

  funExpectOutput(&sOut, aToExpect, &cOut, rvToExpect, cmp_pointer, cmp_int, cmp_pointer, &s2ExpectOut, &cToExpectOut);

  int rv = fun(&sOut, aToExpect, &cOut);

  ASSERT_EQ(rv, rvToExpect);
  ASSERT_EQ(sOut, s2ExpectOut);
  ASSERT_EQ(cOut, cToExpectOut);

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;
}

TEST_F(intFunStructPtrIntCharPtr_testCase, TwoPtrOut)
{
  funPtr fun = nullptr;
  void *cmpStruct = nullptr;
  funExpectOutputPtr funExpectOutput = nullptr;
  getFunPtr((void **) &fun, nullptr, &cmpStruct, (void **) &funExpectOutput);

  ASSERT_TRUE(fun);
  ASSERT_TRUE(cmpStruct);
  ASSERT_TRUE(funExpectOutput);

  struct s2 sOut;
  struct s2 s2ExpectOut[2];
  float fToExpect[2] = {2, 6};
  s2ExpectOut[0].c = 1;
  s2ExpectOut[0].d = &fToExpect[0];
  s2ExpectOut[0].s.a = 3;
  s2ExpectOut[0].s.b = 4;
  s2ExpectOut[1].c = 5;
  s2ExpectOut[1].d = &fToExpect[6];
  s2ExpectOut[1].s.a = 7;
  s2ExpectOut[1].s.b = 8;

  int aToExpect[2] = {5, 6};

  char cOut;
  char cToExpectOut[2] = {'c', 'd'};

  int rvToExpect[2] = {6, 7};

  funExpectOutput(&sOut, aToExpect[0], &cOut, rvToExpect[0], cmp_pointer, cmp_int, cmp_pointer, &s2ExpectOut[0], &cToExpectOut[0]);
  funExpectOutput(&sOut, aToExpect[1], &cOut, rvToExpect[1], cmp_pointer, cmp_int, cmp_pointer, &s2ExpectOut[1], &cToExpectOut[1]);

  int rv = fun(&sOut, aToExpect[0], &cOut);
  ASSERT_EQ(rv, rvToExpect[0]);
  ASSERT_EQ(sOut, s2ExpectOut[0]);
  ASSERT_EQ(cOut, cToExpectOut[0]);

  rv = fun(&sOut, aToExpect[1], &cOut);
  ASSERT_EQ(rv, rvToExpect[1]);
  ASSERT_EQ(sOut, s2ExpectOut[1]);
  ASSERT_EQ(cOut, cToExpectOut[1]);

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;
}

TEST_F(intFunStructPtrIntCharPtr_testCase, TwoPtrOutInterleavedWithNotOut)
{
  funPtr fun = nullptr;
  void *cmpStruct = nullptr;
  funExpect funExpect = nullptr;
  funExpectOutputPtr funExpectOutput = nullptr;
  getFunPtr((void **) &fun, (void **)&funExpect, &cmpStruct, (void **) &funExpectOutput);

  ASSERT_TRUE(fun);
  ASSERT_TRUE(funExpect);
  ASSERT_TRUE(cmpStruct);
  ASSERT_TRUE(funExpectOutput);

  struct s2 sOut;
  struct s2 s2ExpectOut[2];
  float fToExpect[2] = {2, 6};
  s2ExpectOut[0].c = 1;
  s2ExpectOut[0].d = &fToExpect[0];
  s2ExpectOut[0].s.a = 3;
  s2ExpectOut[0].s.b = 4;
  s2ExpectOut[1].c = 5;
  s2ExpectOut[1].d = &fToExpect[1];
  s2ExpectOut[1].s.a = 7;
  s2ExpectOut[1].s.b = 8;

  int aToExpect[2] = {5, 6};

  char cOut;
  char cToExpectOut[2] = {'c', 'd'};

  int rvToExpect[2] = {6, 7};

  funExpectOutput(&sOut, aToExpect[0], &cOut, rvToExpect[0], cmp_pointer, cmp_int, cmp_pointer, &s2ExpectOut[0], &cToExpectOut[0]);
  funExpect(&sOut, aToExpect[0], &cOut, rvToExpect[0], cmp_pointer, cmp_int, cmp_pointer);
  funExpectOutput(&sOut, aToExpect[1], &cOut, rvToExpect[1], cmp_pointer, cmp_int, cmp_pointer, &s2ExpectOut[1], &cToExpectOut[1]);

  int rv = fun(&sOut, aToExpect[0], &cOut);
  ASSERT_EQ(rv, rvToExpect[0]);
  ASSERT_EQ(sOut, s2ExpectOut[0]);
  ASSERT_EQ(cOut, cToExpectOut[0]);

  /* Data out didn't change */
  rv = fun(&sOut, aToExpect[0], &cOut);
  ASSERT_EQ(rv, rvToExpect[0]);
  ASSERT_EQ(sOut, s2ExpectOut[0]);
  ASSERT_EQ(cOut, cToExpectOut[0]);

  rv = fun(&sOut, aToExpect[1], &cOut);
  ASSERT_EQ(rv, rvToExpect[1]);
  ASSERT_EQ(sOut, s2ExpectOut[1]);
  ASSERT_EQ(cOut, cToExpectOut[1]);

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;
}
