#include <gtest/gtest.h> // googletest header file

#include <LLVMParser.h>
#include <FunctionDeclaration.h>
#include <ElementToMockContext.h>

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
  parser.getElementToMockContext(ctxt);
  const ElementToMock::Vector& elementToMock = ctxt.getElementToMock();
  ASSERT_EQ(elementToMock.size(), funList.size());
  for(size_t funIdx = 0; funIdx < funList.size(); funIdx++)
  {
    const FunctionDeclaration& funFromFactory = funList[funIdx];
    std::ostringstream factorySs;
    factorySs <<  funFromFactory;

    const FunctionDeclaration& funFromParser = FunctionDeclaration::toFunctionDeclaration(elementToMock[funIdx]);
    std::ostringstream parserSs;
    parserSs << funFromParser;

    ASSERT_STRCASEEQ(factorySs.str().c_str(), parserSs.str().c_str()) << std::endl << "factoryStr" << factorySs.str() << std::endl << "parserStr" << parserSs.str();
    ASSERT_EQ(funFromFactory, funFromParser) << "funIdx: " << funIdx;
  }
  DefinedMacroList ml = funFactory.getDefinedMacroList();
  for(const std::pair<const std::string, std::string>& elem : ml)
  {
    const std::string& id = elem.first;
    const std::string& definition = elem.second;
    ASSERT_TRUE(ctxt.hasMacroDefine(id)) << "cross defined ID: " << id;
    ASSERT_STREQ(definition.c_str(), ctxt.getMacroDefinition(id).c_str()) << "cross defined ID: " << id;
  }
}
