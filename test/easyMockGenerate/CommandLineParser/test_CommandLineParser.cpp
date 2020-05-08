#include <gtest/gtest.h>

#include <CXXOptsCmdLineParser.h>

#define ARRAY_SIZE(arr) ((sizeof(arr)/sizeof(arr[0])))

typedef ::testing::Types
<
  CXXOptsCmdLineParser
> CmdLineParserTestTypes;

template <typename T>
class CommandLineParser_testCase : public ::testing::Test
{
};

TYPED_TEST_CASE(CommandLineParser_testCase, CmdLineParserTestTypes);

TYPED_TEST(CommandLineParser_testCase, InOut)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * const parsedArgs[] = {"./test", "-i", "foo", "-o", "bar", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, (char **) parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_EQ(opt.m_inputHeaderFile, "foo");
  ASSERT_EQ(opt.m_outputDir, "bar");
}

TYPED_TEST(CommandLineParser_testCase, NoIn)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * const parsedArgs[] = {"./test", "-o", "bar", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, (char **) parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), "Error: The input header file is not provided");
}

TYPED_TEST(CommandLineParser_testCase, NoOut)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * const parsedArgs[] = {"./test", "-i", "foo", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, (char **) parsedArgs);

  ASSERT_FALSE(opt.m_errorMessage.empty());
  ASSERT_STREQ(opt.m_errorMessage.c_str(), "Error: The output directory file is not provided");
}

TYPED_TEST(CommandLineParser_testCase, ExtraParams)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * const parsedArgs[] = {"./test", "-i", "foo", "-o" ,"bar", "-I", "i1", "-D", "d1", "-I", "i2", "-D", "d2" , NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, (char **) parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_EQ(opt.m_inputHeaderFile, "foo");
  ASSERT_EQ(opt.m_outputDir, "bar");
  ExtraArgsList expectedArgList = {"-I", "i1", "-D", "d1", "-I", "i2", "-D", "d2"};
  ASSERT_EQ(opt.m_extraArgs, expectedArgList);
}

TYPED_TEST(CommandLineParser_testCase, ExtraParamsMangled)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * const parsedArgs[] = {"./test", "-I", "i1", "-o" ,"bar", "-D", "d1", "-i", "foo", "-I", "i2", "-D", "d2" , NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, (char **) parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_TRUE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
  ASSERT_EQ(opt.m_inputHeaderFile, "foo");
  ASSERT_EQ(opt.m_outputDir, "bar");
  ExtraArgsList expectedArgList = {"-I", "i1", "-D", "d1", "-I", "i2", "-D", "d2"};
  ASSERT_EQ(opt.m_extraArgs, expectedArgList);
}

TYPED_TEST(CommandLineParser_testCase, ParamHelpShort)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * const parsedArgs[] = {"./test", "-h", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, (char **) parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_FALSE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
}

TYPED_TEST(CommandLineParser_testCase, ParamHelpLong)
{
  TypeParam parser;
  CommandLineParserItf& parserItf = parser;
  const char * const parsedArgs[] = {"./test", "--help", NULL};
  EasyMockOptions opt = parserItf.getParsedArguments(ARRAY_SIZE(parsedArgs) - 1, (char **) parsedArgs);

  ASSERT_TRUE(opt.m_errorMessage.empty()) << opt.m_errorMessage;
  ASSERT_FALSE(opt.m_helpMessage.empty()) << opt.m_helpMessage;
}
