#include <gtest/gtest.h> // googletest header file

#include <LLVMParser.h>
#include <FunctionDeclaration.h>
#include <ElementToMockContext.h>

#include <TestTypes.h>

#include <PrintObjects.h>

template <typename T>
class GenericParser_testCase : public ::testing::Test
{
};

TYPED_TEST_SUITE(GenericParser_testCase, ParserTestTypes);

TYPED_TEST(GenericParser_testCase, parser)
{
  TypeParam funFactory;

  /*
   * Get the function list from the factory before the parser to make sure the
   * anonymous type ID is correctly reset. The parser will then generate the
   * same anonymous type ID.
   */
  ElementToMockList funList = funFactory.functionFactoryArray();

  ElementToMockContext ctxt;
  LLVMParser parser;
  std::string fileName(PROJECT_ROOT_DIR"/test/easyMockGenerate/include/");
  fileName.append(funFactory.getFilename());
  parser.setFilename(fileName);
  parser.setForceCpp(funFactory.isCpp());
  ASSERT_EQ(parser.getElementToMockContext(ctxt), cp_OK);
  const auto& elementToMock = ctxt.getElementToMock();
  ASSERT_EQ(elementToMock.size(), funList.size());
  for(size_t funIdx = 0; funIdx < funList.size(); funIdx++)
  {
    const auto& funFromFactory = funList[funIdx];
    std::ostringstream factorySs;
    factorySs <<  *funFromFactory;

    const auto& funFromParser = elementToMock[funIdx];
    std::ostringstream parserSs;
    parserSs << *funFromParser;

    EXPECT_STREQ(factorySs.str().c_str(), parserSs.str().c_str()) << std::endl << "index: " << funIdx << std::endl << "factoryStr" << factorySs.str() << std::endl << "parserStr" << parserSs.str();
    EXPECT_EQ(*funFromFactory, *funFromParser) << "funIdx: " << funIdx;
  }
  const auto& ml = funFactory.getDefinedMacroList();
  for(const auto& elem : ml)
  {
    const std::string& id = elem.first;
    const std::string& definition = elem.second.getDefinition();
    EXPECT_TRUE(ctxt.hasMacroDefine(id)) << "cross defined ID: " << id;
    EXPECT_STREQ(definition.c_str(), ctxt.getMacroDefinition(id).getDefinition().c_str()) << "cross defined ID: " << id;
  }
}
