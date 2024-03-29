#include "CmdLineParser.h"

#include <string>

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
  namespace fs = std::experimental::filesystem;
#else
  error "Missing the <filesystem> header."
#endif

namespace
{
bool hasOneMoreArgument(int argIdx, int argc)
{
  return argIdx+1 < argc;
}

bool nextArgumentValid(int argIdx, const char* argv[])
{
  return argv[argIdx+1][0] != '-';
}
}

EasyMockOptions CmdLineParser::getParsedArguments(int argc,const char* argv[]) const
{
  EasyMockOptions opt;
  opt.m_generateTypes = false;
  opt.m_generateIncludedFunctions = false;
  opt.m_mockCpp = false;
  opt.m_ignoreParserError = false;

  int argIdx;
  for(argIdx = 1; argv[argIdx] != nullptr && argIdx < argc; argIdx++)
  {
    const std::string currentParam(argv[argIdx]);
    if(currentParam == g_inputHeaderParam && hasOneMoreArgument(argIdx, argc))
    {
      if(!opt.m_inputHeaderFile.empty())
      {
        opt.m_errorMessage = g_minusIParameterGivenTwice;
        return opt;
      }
      opt.m_inputHeaderFile = std::string(argv[argIdx+1]);
      if(opt.m_inputHeaderFile[0] == '-')
      {
        opt.m_inputHeaderFile.clear();
      }
      else
      {
        if(!fs::is_regular_file(opt.m_inputHeaderFile))
        {
          opt.m_errorMessage = g_inputFileIsntRegular;
          opt.m_inputHeaderFile.clear();
          return opt;
        }
        argIdx++;
      }
    }
    else if(currentParam == g_outputDirParam && hasOneMoreArgument(argIdx, argc))
    {
      if(!opt.m_outputDir.empty())
      {
        opt.m_errorMessage = g_minusOParameterGivenTwice;
        return opt;
      }
      opt.m_outputDir = std::string(argv[argIdx+1]);
      if(opt.m_outputDir[0] == '-')
      {
        opt.m_outputDir.clear();
      }
      else
      {
        if(!fs::is_directory(opt.m_outputDir))
        {
          opt.m_errorMessage = g_outputDirIsntDir;
          opt.m_outputDir.clear();
          return opt;
        }
        argIdx++;
      }
    }
    else if(currentParam == g_mockOnlyParam)
    {
      if(hasOneMoreArgument(argIdx, argc))
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
      opt.m_helpMessage = g_helpMessage;
      return opt;
    }
    else if(currentParam == g_changeWorkingDir)
    {
      if(!opt.m_changeWorkingDir.empty())
      {
        opt.m_changeWorkingDir.clear();
        opt.m_errorMessage = g_errorCwdMoreThanOnce;
        return opt;
      }
      if(hasOneMoreArgument(argIdx, argc))
      {
        if(!nextArgumentValid(argIdx, argv))
        {
          opt.m_errorMessage = g_errorCwdMissing;
          return opt;
        }
        opt.m_changeWorkingDir = std::string(argv[argIdx+1]);
        argIdx++;
      }
      else
      {
        opt.m_errorMessage = g_errorCwdMissing;
        return opt;
      }
    }
    else if(currentParam == g_generateAttribute)
    {
      if(hasOneMoreArgument(argIdx, argc))
      {
        if(!nextArgumentValid(argIdx, argv))
        {
          opt.m_errorMessage = g_errorGenerateAttrAttrMissing;
          return opt;
        }
        opt.m_generateAttrList.emplace(argv[argIdx+1]);
        argIdx++;
      }
      else
      {
        opt.m_errorMessage = g_errorGenerateAttrAttrMissing;
        return opt;
      }
    }
    else if(currentParam == g_generateTypes)
    {
      opt.m_generateTypes = true;
    }
    else if(currentParam == g_mockCpp)
    {
      opt.m_mockCpp = true;
    }
    else if(currentParam == g_ignoreParserError)
    {
      opt.m_ignoreParserError = true;
    }
    else if(currentParam == g_generateIncludedFunctions)
    {
      opt.m_generateIncludedFunctions = true;
    }
    else if(currentParam == g_ignoreFieldGenerationOfParam)
    {
      if(hasOneMoreArgument(argIdx, argc))
      {
        if(argv[argIdx+1][0] == '-')
        {
          opt.m_errorMessage = g_errorIgnoreFieldGenerationOfArgumentMissing;
          return opt;
        }
        opt.m_ignoreTypeList.insert(std::string(argv[argIdx+1]));
        argIdx++;
      }
      else
      {
        opt.m_errorMessage = g_errorIgnoreFieldGenerationOfArgumentMissing;
        return opt;
      }
    }
    else if(currentParam == g_ignoreGenerationOfParam)
    {
      if(hasOneMoreArgument(argIdx, argc))
      {
        if(argv[argIdx+1][0] == '-')
        {
          opt.m_errorMessage = g_errorIgnoreGenerationOfArgumentMissing;
          return opt;
        }
        opt.m_ignoreFunList.insert(std::string(argv[argIdx+1]));
        argIdx++;
      }
      else
      {
        opt.m_errorMessage = g_errorIgnoreGenerationOfArgumentMissing;
        return opt;
      }
    }
    else if(currentParam == g_generateComparatorOf)
    {
      if(hasOneMoreArgument(argIdx, argc))
      {
        if(argv[argIdx+1][0] == '-')
        {
          opt.m_errorMessage = g_errorGenerateComparatorOfArgumentMissing;
          return opt;
        }
        opt.m_comparatorList.insert(std::string(argv[argIdx+1]));
        argIdx++;
      }
      else
      {
        opt.m_errorMessage = g_errorGenerateComparatorOfArgumentMissing;
        return opt;
      }
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
