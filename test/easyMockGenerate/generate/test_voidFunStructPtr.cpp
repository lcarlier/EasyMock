#include <gtest/gtest.h> // googletest header file

#include <VoidFunStructPtrFactory.h>
#include <StructCommonHelper.h>
#include <stddef.h>

#include "genGenerate_testCase.h"

typedef void (*funPtr)(struct s2*);
typedef void (*funExpect)(struct s2*, EasyMock_Matcher match_a);
typedef void (*funExpectOutputPtr)(struct s2*, EasyMock_Matcher match_a, struct s2*);

class voidFunStructPtr_testCase : public genGenerate_testCase<VoidFunStructPtrFactory>
{
public:
  voidFunStructPtr_testCase() : genGenerate_testCase<VoidFunStructPtrFactory>()
  {
    setStructTypeToMatch("s2");
  }
};

TEST_F(voidFunStructPtr_testCase, OnePtrOut)
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
  s2ExpectOut.c = 1;
  s2ExpectOut.d = 2;
  s2ExpectOut.s.a = 3;
  s2ExpectOut.s.b = 4;

  funExpectOutput(&sOut, cmp_pointer, &s2ExpectOut);

  fun(&sOut);

  ASSERT_EQ(sOut, s2ExpectOut);

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;
}

TEST_F(voidFunStructPtr_testCase, TwoPtrOut)
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
  s2ExpectOut[0].c = 1;
  s2ExpectOut[0].d = 2;
  s2ExpectOut[0].s.a = 3;
  s2ExpectOut[0].s.b = 4;
  s2ExpectOut[1].c = 5;
  s2ExpectOut[1].d = 6;
  s2ExpectOut[1].s.a = 7;
  s2ExpectOut[1].s.b = 8;

  funExpectOutput(&sOut, cmp_pointer, &s2ExpectOut[0]);
  funExpectOutput(&sOut, cmp_pointer, &s2ExpectOut[1]);

  fun(&sOut);
  ASSERT_EQ(sOut, s2ExpectOut[0]);
  fun(&sOut);
  ASSERT_EQ(sOut, s2ExpectOut[1]);

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;
}

TEST_F(voidFunStructPtr_testCase, TwoPtrOutInterleavedWithNotOut)
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
  s2ExpectOut[0].c = 1;
  s2ExpectOut[0].d = 2;
  s2ExpectOut[0].s.a = 3;
  s2ExpectOut[0].s.b = 4;
  s2ExpectOut[1].c = 5;
  s2ExpectOut[1].d = 6;
  s2ExpectOut[1].s.a = 7;
  s2ExpectOut[1].s.b = 8;

  funExpectOutput(&sOut, cmp_pointer, &s2ExpectOut[0]);
  funExpect(&sOut, cmp_pointer);
  funExpectOutput(&sOut, cmp_pointer, &s2ExpectOut[1]);

  fun(&sOut);
  ASSERT_EQ(sOut, s2ExpectOut[0]);
  fun(&sOut);
  ASSERT_EQ(sOut, s2ExpectOut[0]); //Data didn't change
  fun(&sOut);
  ASSERT_EQ(sOut, s2ExpectOut[1]);

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;
}
