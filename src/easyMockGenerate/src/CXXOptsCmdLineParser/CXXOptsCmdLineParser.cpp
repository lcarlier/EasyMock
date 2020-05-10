#include "CXXOptsCmdLineParser.h"

#include <cxxopts.hpp>

EasyMockOptions CXXOptsCmdLineParser::getParsedArguments(int argc,char* argv[]) const
{
  EasyMockOptions opt;

  /*
   * Do this before calling cxxopts::Options::parse because that function actually
   * modifies argv and we can't fetch the extra arguments anymore...
   */
  int argIdx;
  const char* inputParam = g_inputHeaderParam.c_str();
  const char* outputParam = g_outputDirParam.c_str();
  const char* mockOnlyParam = g_mockOnlyParam.c_str();
  for(argIdx = 1; argv[argIdx] != nullptr && argIdx < argc; argIdx++)
  {
    const char* currentArg = argv[argIdx];
    if(std::strncmp(currentArg, inputParam, std::strlen(inputParam) + 1) == 0)
    {
      argIdx++;
      continue;
    }
    if(std::strncmp(currentArg, outputParam, std::strlen(outputParam) + 1) == 0)
    {
      argIdx++;
      continue;
    }
    if(std::strncmp(currentArg, mockOnlyParam, std::strlen(outputParam) + 1) == 0)
    {
      argIdx++;
      continue;
    }
    opt.m_extraArgs.emplace_back(currentArg);
  }

  const char helpMessage[] =
  "Generate mocks to be used into a unit test inside a specific directory\n\r"
  "Parameters not recognised by EasyMock (e.g. -I, -D) are given to the parser\n\r"
  "responsible for parsing the header file.";
  cxxopts::Options options(argv[0], helpMessage);
  options.allow_unrecognised_options();

  std::string helpParamOpt(&g_helpParamShort[1]);
  helpParamOpt.push_back(',');
  helpParamOpt.append(g_helpParamLong.substr(2));
  std::vector<std::string> mockOnlyList;
  options.add_options()
      (&inputParam[1], "Input header file", cxxopts::value<std::string>())
      (&outputParam[1], "Output directory", cxxopts::value<std::string>())
      (&mockOnlyParam[2], "Mock only the function specified in this parameter. Can be used several times", cxxopts::value(mockOnlyList))
      (helpParamOpt.c_str(), "Print usage")
  ;

  cxxopts::ParseResult result = options.parse(argc, argv);

  for(std::string str : mockOnlyList)
  {
    opt.m_mockOnlyList.insert(str);
  }

  if(result.count(&g_helpParamShort[1]))
  {
    opt.m_helpMessage = options.help({});
    return opt;
  }

  try
  {
    opt.m_inputHeaderFile = result["i"].as<std::string>();
  }
  catch(std::domain_error)
  {
    opt.m_errorMessage = "Error: The input header file is not provided";
    return opt;
  }

  try
  {
    opt.m_outputDir = result["o"].as<std::string>();
  }
  catch(std::domain_error)
  {
    opt.m_errorMessage = "Error: The output directory file is not provided";
    return opt;
  }

  return opt;
}


