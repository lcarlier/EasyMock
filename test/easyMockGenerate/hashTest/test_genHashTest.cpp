#include <gtest/gtest.h> // googletest header file

#include <FunctionDeclaration.h>

#include <TestTypes.h>

#include <PrintObjects.h>

template <typename T>
class GenericHashTest_testCase : public ::testing::Test
{
};

TYPED_TEST_CASE(GenericHashTest_testCase, HashTestTypes);

TYPED_TEST(GenericHashTest_testCase, hashTest)
{
  TypeParam funFactory;

  ElementToMockList funList = funFactory.functionFactoryArray();

  for(size_t funIdx = 0; funIdx < funList.size(); funIdx++)
  {
    FunctionDeclaration &f = funList[funIdx];
    std::size_t curHash = f.getHash();
    f.cacheHash();
    std::size_t cachedHash = f.getHash();
    EXPECT_EQ(curHash, cachedHash) << std::endl << "index: " << funIdx << std::endl << f;

    f.getFunctionsParameters().emplace_back(Parameter{std::make_shared<CType>(CTYPE_INT), "dummy"});
    f.cacheHash();
    std::size_t newHash = f.getHash();
    EXPECT_NE(newHash, cachedHash) << std::endl << "index: " << funIdx << std::endl << f;
  }
}

TYPED_TEST(GenericHashTest_testCase, rawHashTest)
{
  TypeParam funFactory;

  ElementToMockList funList = funFactory.functionFactoryArray();

  for(size_t funIdx = 0; funIdx < funList.size(); funIdx++)
  {
    FunctionDeclaration &f = funList[funIdx];
    std::size_t curHash = f.getRawHash();
    f.cacheHash();
    std::size_t cachedHash = f.getRawHash();
    EXPECT_EQ(curHash, cachedHash) << std::endl << "index: " << funIdx << std::endl << f;

    f.getFunctionsParameters().emplace_back(Parameter{std::make_shared<CType>(CTYPE_INT), "dummy"});
    f.cacheHash();
    std::size_t newHash = f.getRawHash();
    EXPECT_NE(newHash, cachedHash) << std::endl << "index: " << funIdx << std::endl << f;
  }
}
