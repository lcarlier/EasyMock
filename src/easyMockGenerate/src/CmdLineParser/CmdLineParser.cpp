#include "CmdLineParser.h"

#include <string>

EasyMockOptions CmdLineParser::getParsedArguments(int argc,const char* argv[]) const
{
  EasyMockOptions opt;

  const char helpMessage[] =
  "Generate mocks to be used into a unit test inside a specific directory\n\r"
  "Parameters not recognised by EasyMock (e.g. -I, -D) are given to the parser\n\r"
  "responsible for parsing the header file.\n\r"
  "Usage:\n\r"
  "./EasyMockGenerate [OPTION...]\n\r"
  "\n\r"
  "-i, arg              Input header file\n\r"
  "-o, arg              Output directory\n\r"
  "--mock-only arg      Mock only the function specified in this parameter.\n\r"
  "                     Can be used several times\n\r"
  "-h, --help           Print usage\n\r";

  int argIdx;
  for(argIdx = 1; argv[argIdx] != nullptr && argIdx < argc; argIdx++)
  {
    const std::string currentParam(argv[argIdx]);
    if(currentParam == g_inputHeaderParam && (argIdx+1) < argc)
    {
      opt.m_inputHeaderFile = std::string(argv[argIdx+1]);
      if(opt.m_inputHeaderFile[0] == '-')
      {
        opt.m_inputHeaderFile.clear();
      }
      else
      {
        argIdx++;
      }
    }
    else if(currentParam == g_outputDirParam && (argIdx+1) < argc)
    {
      opt.m_outputDir = std::string(argv[argIdx+1]);
      if(opt.m_outputDir[0] == '-')
      {
        opt.m_outputDir.clear();
      }
      else
      {
        argIdx++;
      }
    }
    else if(currentParam == g_mockOnlyParam)
    {
      if(argIdx+1 < argc)
      {
        if(argv[argIdx+1][0] == '-')
        {
          opt.m_errorMessage = g_errorMockOnlyParamMissing;
          return opt;
        }
        opt.m_mockOnlyList.insert(std::string(argv[argIdx+1]));
        argIdx++;
      }
      else
      {
        opt.m_errorMessage = g_errorMockOnlyParamMissing;
        return opt;
      }
    }
    else if(currentParam == g_helpParamLong || currentParam == g_helpParamShort)
    {
      opt.m_helpMessage = std::string(helpMessage);
      return opt;
    }
    else
    {
      opt.m_extraArgs.emplace_back(std::string(argv[argIdx]));
    }
  }
  if(opt.m_inputHeaderFile.empty())
  {
    opt.m_errorMessage = g_errorInputMissing;
    return opt;
  }
  if(opt.m_outputDir.empty())
  {
    opt.m_errorMessage = g_errorOutputMissing;
    return opt;
  }

  return opt;
}
