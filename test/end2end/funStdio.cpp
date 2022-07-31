#include <gtest/gtest.h>

#include <easyMock.h>

#include <cstring>

#include "easyMock_stdio.h"

TEST(stdio, testOk)
{
    /*
     * Disable the call stack else it creates an infinite loop when trying to
     * dump it. Dumping the callstack requires the usage of a mocked function.
     *
     * Do it before easyMock_init so that if there is a build without BACKTRACE_SUPPORT,
     * then the test won't fail because the error message reporting will eventually use fwrite eventually to
     * print the error.
     */
    easyMock_setPrintCallStack(false);

    easyMock_init();

    FILE fr, fw;
    fopen_ExpectAndReturn("fileRead", "r+", &fr, cmp_str, cmp_str);
    fopen_ExpectAndReturn("fileWrite", "w+", &fw, cmp_str, cmp_str);
    FILE *frrv = fopen("fileRead", "r+");
    FILE *fwrv = fopen("fileWrite", "w+");
    ASSERT_EQ(frrv, &fr);
    ASSERT_EQ(fwrv, &fw);

    char dataReadToReturn[] = "myDataRead";
    size_t dataToReturnSize = std::strlen(dataReadToReturn) + 1;
    char dataRead[32];
    size_t sizeofDataRead = sizeof(dataRead);
    fread_ExpectReturnAndOutput(dataRead, 1, sizeofDataRead, frrv, dataToReturnSize, cmp_pointer, cmp_long, cmp_long, cmp_pointer, &dataReadToReturn, dataToReturnSize, nullptr);
    size_t actualSizeRead = fread(dataRead, 1, sizeofDataRead, frrv);
    ASSERT_EQ(actualSizeRead, dataToReturnSize);
    ASSERT_STREQ(dataRead, dataReadToReturn);

    fwrite_ExpectAndReturn(dataRead, dataToReturnSize, 1, fwrv, dataToReturnSize, cmp_str, cmp_long, cmp_long, cmp_pointer);
    size_t byteWritten = fwrite(dataRead, dataToReturnSize, 1, fwrv);
    EXPECT_EQ(byteWritten, dataToReturnSize);

    const char* errorMsg = easyMock_getErrorStr();
    ASSERT_FALSE(errorMsg) << errorMsg;

    ASSERT_EQ(easyMock_check(), 1);
}

TEST(stdio, testNok)
{
    /*
     * Disable the call stack else it creates an infinite loop when trying to
     * dump it. Dumping the callstack requires the usage of a mocked function.
     *
     * Do it before easyMock_init so that if there is a build without BACKTRACE_SUPPORT,
     * then the test won't fail because the error message reporting will eventually use fwrite eventually to
     * print the error.
     */
    easyMock_setPrintCallStack(false);

    easyMock_init();
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

