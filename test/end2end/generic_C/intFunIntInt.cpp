#include <gtest/gtest.h>

#include <easyMock.h>

#include "easyMock_intFunIntInt.h"

TEST(intFunIntInt, testOk)
{
    easyMock_init();
    intFunIntInt_ExpectAndReturn(5, 3, 2, cmp_int, cmp_int);
    int rv = intFunIntInt(5, 3);
    ASSERT_EQ(rv, 2);
    ASSERT_EQ(easyMock_check(), 1);
    const char* errorMsg = easyMock_getErrorStr();
    ASSERT_FALSE(errorMsg) << errorMsg;
}

TEST(intFunIntInt, testNok)
{
    easyMock_init();
    intFunIntInt_ExpectAndReturn(5, 3, 2, cmp_int, cmp_int);
    int rv = intFunIntInt(5, 4);
    ASSERT_EQ(rv, 2);
    ASSERT_EQ(easyMock_check(), 0);
    ASSERT_TRUE(easyMock_getErrorStr());
}
