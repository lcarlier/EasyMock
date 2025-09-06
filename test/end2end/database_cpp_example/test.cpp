#include <gtest/gtest.h>

#include <easyMock.h>

#include "easyMock_Database.hpp"
#include "DataProcessor.hpp"

class DataProcessorTest : public ::testing::Test {
protected:
    void SetUp() override {
        easyMock_init();
    }

    void TearDown() override {
        ASSERT_EQ(easyMock_check(), 1);
        ASSERT_FALSE(easyMock_getErrorStr());
    }
};

TEST_F(DataProcessorTest, ProcessesCorrectly) {
    Database db;
    DataProcessor processor(db);

    // Expect the call to connect on our db instance --> return true
    EasyMock::Database::connect::ExpectAndReturn(&db, "db://test", true, &::EasyMock::cmp<::std::string>);

    // Expect the call to fetchData on our db instance.
    // Verify that the parameter is "Alice" and return 10.
    EasyMock::Database::fetchData::ExpectAndReturn(&db, "Alice", 10, &EasyMock::cmp<::std::string>);

    EXPECT_EQ(processor.process("Alice"), 20);
}

TEST_F(DataProcessorTest, DBConnectionFail) {
    Database db;
    DataProcessor processor(db);

    // Expect the call to connect on our db instance --> return false
    EasyMock::Database::connect::ExpectAndReturn(&db, "db://test", false, &::EasyMock::cmp<::std::string>);

    EXPECT_EQ(processor.process("Alice"), -1);
}
