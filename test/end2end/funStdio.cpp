#include <gtest/gtest.h>

#include <easyMock.h>

#include <cstring>

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
    ASSERT_EQ(byteWritten, dataToReturnSize);

    const char* errorMsg = easyMock_getErrorStr();
    ASSERT_FALSE(errorMsg) << errorMsg;

    ASSERT_EQ(easyMock_check(), 1);
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

