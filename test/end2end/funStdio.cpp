#include <gtest/gtest.h>

#include <easyMock.h>

#include "easyMock_stdio.h"

TEST(stdio, testOk)
{
    easyMock_init();
    easyMock_printCallStack(false);
    FILE fr, fw;
    fopen_ExpectAndReturn("fileRead", "r+", &fr, cmp_str, cmp_str);
    fopen_ExpectAndReturn("fileWrite", "w+", &fw, cmp_str, cmp_str);
    FILE *frrv = fopen("fileRead", "r+");
    FILE *fwrv = fopen("fileWrite", "w+");
    ASSERT_EQ(frrv, &fr);
    ASSERT_EQ(fwrv, &fw);

    ASSERT_EQ(easyMock_check(), 1);
    const char* errorMsg = easyMock_getErrorStr();
    ASSERT_FALSE(errorMsg) << errorMsg;
}

TEST(stdio, testNok)
{
    easyMock_init();
    easyMock_printCallStack(false);
    FILE fr, fw;
    fopen_ExpectAndReturn("fileRead", "r+", &fr, cmp_str, cmp_str);
    fopen_ExpectAndReturn("fileWrite", "w+", &fw, cmp_str, cmp_str);
    FILE *frrv = fopen("fileRead1", "r+");
    FILE *fwrv = fopen("fileRead2", "w+");
    ASSERT_EQ(frrv, &fr);
    ASSERT_EQ(fwrv, &fw);

    ASSERT_EQ(easyMock_check(), 0);
    const char* errorMsg = easyMock_getErrorStr();
    ASSERT_TRUE(errorMsg);
}

