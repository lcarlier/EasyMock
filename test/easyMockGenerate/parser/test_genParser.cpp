#include <gtest/gtest.h> // googletest header file

#include <LLVMParser.h>
#include <Function.h>

#include <TestTypes.h>

template <typename T>
class GenericParser_testCase : public ::testing::Test
{
};

TYPED_TEST_CASE(GenericParser_testCase, TestTypes);

TYPED_TEST(GenericParser_testCase, parser)
{
  TypeParam funFactory;
  ElementToMock::Vector elem;
  LLVMParser parser;
  std::string fileName(PROJECT_ROOT_DIR"/test/easyMockGenerate/include/");
  fileName.append(funFactory.getFilename());
  parser.setFilename(fileName);
  parser.getElementToStub(elem);
  EXPECT_EQ(elem.size(), 1);
  Function& fp = Function::toFunction(elem[0]);
  Function f = funFactory.functionFactory();
  EXPECT_EQ(f, fp);
}
