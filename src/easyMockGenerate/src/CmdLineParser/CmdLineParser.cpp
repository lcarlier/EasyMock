#include "CmdLineParser.h"

#include <string>

EasyMockOptions CmdLineParser::getParsedArguments(int argc,const char* argv[]) const
{
  EasyMockOptions opt;

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
      if(argIdx+1 < argc)
      {
        if(argv[argIdx+1][0] == '-')
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
