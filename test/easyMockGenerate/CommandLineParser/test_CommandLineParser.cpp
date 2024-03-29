#include <gtest/gtest.h>

#include <algorithm>

#include <CmdLineParser.h>

#define ARRAY_SIZE(arr) ((sizeof(arr)/sizeof(arr[0])))

typedef ::testing::Types
<
  CmdLineParser
> CmdLineParserTestTypes;

template <typename T>
class CommandLineParser_testCase : public ::testing::Test
{
};

namespace
{
const char* CmdLineParserHeaderFile = PROJECT_ROOT_DIR"/src/easyMockGenerate/include/CmdLineParser.h";
const char* CmdLineOutputDir = PROJECT_ROOT_DIR"/src";
}

TYPED_TEST_SUITE(CommandLineParser_testCase, CmdLineParserTestTypes);

TYPED_TEST(CommandLineParser_testCase, InOut)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_inputHeaderFile.c_str(), CmdLineParserHeaderFile);
  ASSERT_STREQ(opt.m_outputDir.c_str(), CmdLineOutputDir);
  ASSERT_FALSE(opt.m_generateTypes);
  ASSERT_FALSE(opt.m_mockCpp);
  ASSERT_FALSE(opt.m_ignoreParserError);
}

TYPED_TEST(CommandLineParser_testCase, InOutGenerateType)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--generate-types", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_inputHeaderFile.c_str(), CmdLineParserHeaderFile);
  ASSERT_STREQ(opt.m_outputDir.c_str(), CmdLineOutputDir);
  ASSERT_TRUE(opt.m_generateTypes);
  ASSERT_FALSE(opt.m_mockCpp);
  ASSERT_FALSE(opt.m_ignoreParserError);
}

TYPED_TEST(CommandLineParser_testCase, InOutGeneratedIncludedFunctions)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--generate-included-functions", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_inputHeaderFile.c_str(), CmdLineParserHeaderFile);
  ASSERT_STREQ(opt.m_outputDir.c_str(), CmdLineOutputDir);
  ASSERT_TRUE(opt.m_generateIncludedFunctions);
}

TYPED_TEST(CommandLineParser_testCase, NoIn)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-o", CmdLineOutputDir, NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorInputMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, InWithoutParamBegin)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", "-o", CmdLineOutputDir, NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorInputMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, InWithoutParamEnd)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-o", CmdLineOutputDir, "-i", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorInputMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, NoOut)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorOutputMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, OutWithoutParamBegin)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-o", "-i", CmdLineParserHeaderFile, NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorOutputMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, OutWithoutParamEnd)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorOutputMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, ExtraParams)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o" ,CmdLineOutputDir, "-I", "i1", "-D", "d1", "-I", "i2", "-D", "d2" , NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_inputHeaderFile.c_str(), CmdLineParserHeaderFile);
  ASSERT_STREQ(opt.m_outputDir.c_str(), CmdLineOutputDir);
  ExtraArgsList expectedArgList = {"-I", "i1", "-D", "d1", "-I", "i2", "-D", "d2"};
  ASSERT_EQ(opt.m_extraArgs, expectedArgList);
  ASSERT_FALSE(opt.m_generateTypes);
  ASSERT_FALSE(opt.m_mockCpp);
  ASSERT_FALSE(opt.m_ignoreParserError);
}

TYPED_TEST(CommandLineParser_testCase, ExtraParamsMangled)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-I", "i1", "-o" ,CmdLineOutputDir, "-D", "d1", "-i", CmdLineParserHeaderFile, "-I", "i2", "-D", "d2" , NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_inputHeaderFile.c_str(), CmdLineParserHeaderFile);
  ASSERT_STREQ(opt.m_outputDir.c_str(), CmdLineOutputDir);
  ExtraArgsList expectedArgList = {"-I", "i1", "-D", "d1", "-I", "i2", "-D", "d2"};
  ASSERT_EQ(opt.m_extraArgs, expectedArgList);
  ASSERT_FALSE(opt.m_generateTypes);
  ASSERT_FALSE(opt.m_mockCpp);
  ASSERT_FALSE(opt.m_ignoreParserError);
}

TYPED_TEST(CommandLineParser_testCase, ParamHelpShort)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-h", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_FALSE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_helpMessage.c_str(), g_helpMessage.c_str());
  ASSERT_FALSE(opt.m_generateTypes);
  ASSERT_FALSE(opt.m_mockCpp);ASSERT_FALSE(opt.m_ignoreParserError);
  ASSERT_FALSE(opt.m_ignoreParserError);
}

TYPED_TEST(CommandLineParser_testCase, ParamHelpLong)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "--help", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_FALSE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_helpMessage.c_str(), g_helpMessage.c_str());
  ASSERT_FALSE(opt.m_generateTypes);
  ASSERT_FALSE(opt.m_mockCpp);
  ASSERT_FALSE(opt.m_ignoreParserError);
}

TYPED_TEST(CommandLineParser_testCase, MockOnly)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--mock-only", "fopen", "--mock-only", "fread", "--mock-only", "fwrite", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  MockOnlyList mockOnlyExpect = {"fopen", "fread", "fwrite"};
  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_inputHeaderFile.c_str(), CmdLineParserHeaderFile);
  ASSERT_STREQ(opt.m_outputDir.c_str(), CmdLineOutputDir);
  ASSERT_EQ(opt.m_extraArgs, std::vector<std::string>());
  ASSERT_EQ(opt.m_mockOnlyList, mockOnlyExpect);
  ASSERT_FALSE(opt.m_generateTypes);
  ASSERT_FALSE(opt.m_mockCpp);
  ASSERT_FALSE(opt.m_ignoreParserError);
}

TYPED_TEST(CommandLineParser_testCase, MockOnlyMissingArgBegin)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "--mock-only", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--mock-only", "fopen", "--mock-only", "fread", "--mock-only", "fwrite", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorMockOnlyParamMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, MockOnlyMissingArgEnd)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--mock-only", "fopen", "--mock-only", "fread", "--mock-only", "fwrite", "--mock-only", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorMockOnlyParamMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, CwdOk)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--cwd", "directory", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_inputHeaderFile.c_str(), CmdLineParserHeaderFile);
  ASSERT_STREQ(opt.m_outputDir.c_str(), CmdLineOutputDir);
  ASSERT_EQ(opt.m_changeWorkingDir, "directory");
  ASSERT_FALSE(opt.m_generateTypes);
  ASSERT_FALSE(opt.m_mockCpp);
  ASSERT_FALSE(opt.m_ignoreParserError);
}

TYPED_TEST(CommandLineParser_testCase, CwdMissing)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--cwd", "-notValid", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorCwdMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, CwdNotGiven)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--cwd", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorCwdMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, CwdMoreThanOnce)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--cwd", "directory", "--cwd", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_TRUE(opt.m_changeWorkingDir.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorCwdMoreThanOnce.c_str());
}

TYPED_TEST(CommandLineParser_testCase, GenerateAttrWithoutParameter)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--generate-attribute", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_TRUE(opt.m_changeWorkingDir.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorGenerateAttrAttrMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, GenerateAttrInvalidParameter)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--generate-attribute", "-notValid", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorGenerateAttrAttrMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, GenerateAttrOK)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--generate-attribute", "format", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_TRUE(std::find(opt.m_generateAttrList.begin(),opt.m_generateAttrList.end(), "format") != opt.m_generateAttrList.end());
}


TYPED_TEST(CommandLineParser_testCase, GenerateAttrOKMultipleUse)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "--generate-attribute", "inline", "-o", CmdLineOutputDir, "--generate-attribute", "format", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_TRUE(std::find(opt.m_generateAttrList.begin(),opt.m_generateAttrList.end(), "format") != opt.m_generateAttrList.end());
  ASSERT_TRUE(std::find(opt.m_generateAttrList.begin(),opt.m_generateAttrList.end(), "inline") != opt.m_generateAttrList.end());
}

TYPED_TEST(CommandLineParser_testCase, TypeIgnoreField)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--ignore-field-generation-of", "type1", "--ignore-field-generation-of", "type2", "--ignore-field-generation-of", "type3", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  IgnoreTypeFieldList ignoreTypeListExpect = {"type1", "type2", "type3"};
  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_inputHeaderFile.c_str(), CmdLineParserHeaderFile);
  ASSERT_STREQ(opt.m_outputDir.c_str(), CmdLineOutputDir);
  ASSERT_EQ(opt.m_extraArgs, std::vector<std::string>());
  ASSERT_EQ(opt.m_ignoreTypeList, ignoreTypeListExpect);
  ASSERT_FALSE(opt.m_generateTypes);
  ASSERT_FALSE(opt.m_mockCpp);
  ASSERT_FALSE(opt.m_ignoreParserError);
}

TYPED_TEST(CommandLineParser_testCase, TypeIgnoreFieldMissingArgBegin)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "--ignore-field-generation-of", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--ignore-field-generation-of", "type1", "--ignore-field-generation-of", "type2", "--ignore-field-generation-of", "type3", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorIgnoreFieldGenerationOfArgumentMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, TypeIgnoreFieldMissingArgEnd)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--ignore-field-generation-of", "type1", "--ignore-field-generation-of", "type2", "--ignore-field-generation-of", "type3", "--ignore-field-generation-of", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorIgnoreFieldGenerationOfArgumentMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, FunIgnore)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--ignore-generation-of", "type1", "--ignore-generation-of", "type2", "--ignore-generation-of", "type3", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  IgnoreFunList ignoreFunListExpect = {"type1", "type2", "type3"};
  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_inputHeaderFile.c_str(), CmdLineParserHeaderFile);
  ASSERT_STREQ(opt.m_outputDir.c_str(), CmdLineOutputDir);
  ASSERT_EQ(opt.m_extraArgs, std::vector<std::string>());
  ASSERT_EQ(opt.m_ignoreFunList, ignoreFunListExpect);
  ASSERT_FALSE(opt.m_generateTypes);
  ASSERT_FALSE(opt.m_mockCpp);
  ASSERT_FALSE(opt.m_ignoreParserError);
}

TYPED_TEST(CommandLineParser_testCase, FunIgnoreMissingArgBegin)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "--ignore-generation-of", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--ignore-generation-of", "type1", "--ignore-generation-of", "type2", "--ignore-generation-of", "type3", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorIgnoreGenerationOfArgumentMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, FunIgnoreMissingArgEnd)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--ignore-generation-of", "type1", "--ignore-generation-of", "type2", "--ignore-generation-of", "type3", "--ignore-generation-of", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorIgnoreGenerationOfArgumentMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, ComparatorGen)
{
TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--generate-comparator-of", "type1", "--generate-comparator-of", "type2", "--generate-comparator-of", "type3", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ComparatorList comparatorList = {"type1", "type2", "type3"};
  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_inputHeaderFile.c_str(), CmdLineParserHeaderFile);
  ASSERT_STREQ(opt.m_outputDir.c_str(), CmdLineOutputDir);
  ASSERT_EQ(opt.m_extraArgs, std::vector<std::string>());
  ASSERT_EQ(opt.m_comparatorList, comparatorList);
  ASSERT_FALSE(opt.m_generateTypes);
  ASSERT_FALSE(opt.m_mockCpp);
  ASSERT_FALSE(opt.m_ignoreParserError);
}

TYPED_TEST(CommandLineParser_testCase, ComparatorGenMissingArgBegin)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "--generate-comparator-of", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--generate-comparator-of", "type1", "--generate-comparator-of", "type2", "--generate-comparator-of", "type3", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorGenerateComparatorOfArgumentMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, ComparatorGenMissingArgEnd)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--generate-comparator-of", "type1", "--generate-comparator-of", "type2", "--generate-comparator-of", "type3", "--generate-comparator-of", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), g_errorGenerateComparatorOfArgumentMissing.c_str());
}

TYPED_TEST(CommandLineParser_testCase, MockCpp)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--mock-cpp", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_inputHeaderFile.c_str(), CmdLineParserHeaderFile);
  ASSERT_STREQ(opt.m_outputDir.c_str(), CmdLineOutputDir);
  ASSERT_FALSE(opt.m_generateTypes);
  ASSERT_TRUE(opt.m_mockCpp);
  ASSERT_FALSE(opt.m_ignoreParserError);
}


TYPED_TEST(CommandLineParser_testCase, IgnoreParser)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "--ignore-parser-error", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_STREQ(opt.m_inputHeaderFile.c_str(), CmdLineParserHeaderFile);
  ASSERT_STREQ(opt.m_outputDir.c_str(), CmdLineOutputDir);
  ASSERT_FALSE(opt.m_generateTypes);
  ASSERT_FALSE(opt.m_mockCpp);
  ASSERT_TRUE(opt.m_ignoreParserError);
}

TYPED_TEST(CommandLineParser_testCase, minusIGivenOnlyOnce)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "-i", CmdLineParserHeaderFile, NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  EXPECT_FALSE(opt.m_errorMessage.empty());
  EXPECT_STREQ(opt.m_errorMessage.c_str(), g_minusIParameterGivenTwice.c_str());
}

TYPED_TEST(CommandLineParser_testCase, minusOGivenOnlyOnce)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineOutputDir, "-o", "bar2", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  EXPECT_FALSE(opt.m_errorMessage.empty());
  EXPECT_STREQ(opt.m_errorMessage.c_str(), g_minusOParameterGivenTwice.c_str());
}

TYPED_TEST(CommandLineParser_testCase, inputFileIsntRegular)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineOutputDir, "-o", CmdLineOutputDir,  NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  EXPECT_FALSE(opt.m_errorMessage.empty());
  EXPECT_TRUE(opt.m_inputHeaderFile.empty());
  EXPECT_STREQ(opt.m_errorMessage.c_str(), g_inputFileIsntRegular.c_str());
}

TYPED_TEST(CommandLineParser_testCase, inputFileDoesntExists)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", "doesntExists", "-o", CmdLineOutputDir,  NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  EXPECT_FALSE(opt.m_errorMessage.empty());
  EXPECT_TRUE(opt.m_inputHeaderFile.empty());
  EXPECT_STREQ(opt.m_errorMessage.c_str(), g_inputFileIsntRegular.c_str());
}

TYPED_TEST(CommandLineParser_testCase, outputDirIsntDirectory)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", CmdLineParserHeaderFile,  NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  EXPECT_FALSE(opt.m_errorMessage.empty());
  EXPECT_TRUE(opt.m_outputDir.empty());
  EXPECT_STREQ(opt.m_errorMessage.c_str(), g_outputDirIsntDir.c_str());
}

TYPED_TEST(CommandLineParser_testCase, outputDirDoesntExists)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * parsedArgs[] = {"./test", "-i", CmdLineParserHeaderFile, "-o", "doesntExists",  NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, parsedArgs);

  EXPECT_FALSE(opt.m_errorMessage.empty());
  EXPECT_TRUE(opt.m_outputDir.empty());
  EXPECT_STREQ(opt.m_errorMessage.c_str(), g_outputDirIsntDir.c_str());
}