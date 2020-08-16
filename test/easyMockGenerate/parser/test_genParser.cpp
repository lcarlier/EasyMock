#include <gtest/gtest.h> // googletest header file

#include <LLVMParser.h>
#include <FunctionDeclaration.h>

#include <TestTypes.h>

#include <gtestPrintClasses.h>

template <typename T>
class GenericParser_testCase : public ::testing::Test
{
};

TYPED_TEST_CASE(GenericParser_testCase, ParserTestTypes);

TYPED_TEST(GenericParser_testCase, parser)
{
  TypeParam funFactory;
  ElementToMock::Vector elem;
  LLVMParser parser;
  std::string fileName(PROJECT_ROOT_DIR"/test/easyMockGenerate/include/");
  fileName.append(funFactory.getFilename());
  parser.setFilename(fileName);
  parser.getElementToStub(elem);
  ElementToMockList funList = funFactory.functionFactoryArray();
  ASSERT_EQ(elem.size(), funList.size());
  for(size_t funIdx = 0; funIdx < funList.size(); funIdx++)
  {
    FunctionDeclaration* funFromFactory = funList[funIdx];
    FunctionDeclaration& funFromParser = FunctionDeclaration::toFunctionDeclaration(elem[funIdx]);
    EXPECT_EQ(*funFromFactory, funFromParser) << "funIdx: " << funIdx;
    delete funFromFactory;
  }
}
