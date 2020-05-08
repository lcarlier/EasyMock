#include <CodeGeneratorCTemplate.h>
#include "CodeParserCLang.h"
#include "MainCodeGenerator.h"
#include "Function.h"
#include <CXXOptsCmdLineParser.h>
#include <LLVMParser.h>

#include <stdio.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

static bool fileExists(const std::string& path);
static bool dirExists(const std::string& path);

static bool validateParameter(const EasyMockOptions& opt);

int main(int argc, char *argv[])
{
  CXXOptsCmdLineParser cmdParser;
  EasyMockOptions opt = cmdParser.getParsedArguments(argc, argv);
  if(!opt.m_helpMessage.empty())
  {
    std::fprintf(stdout, "%s\n\r", opt.m_helpMessage.c_str());
    return 0;
  }
  if(!opt.m_errorMessage.empty())
  {
    std::fprintf(stderr, "%s\n\r", opt.m_errorMessage.c_str());
    return 1;
  }
  if(!validateParameter(opt))
  {
    return 1;
  }
  
  CodeGeneratorCTemplate cg;
  LLVMParser of;
  of.setFlags(opt.m_extraArgs);
  MainCodeGenerator cp(opt.m_inputHeaderFile, of, cg);
  cp.generateCode(opt.m_outputDir);

  return 0;
}

static bool validateParameter(const EasyMockOptions& opt)
{
  const char* inputHeaderFile = opt.m_inputHeaderFile.c_str();
  if(!fileExists(opt.m_inputHeaderFile))
  {
    std::fprintf(stderr, "Error: input file '%s' doesn't exists\n\r", inputHeaderFile);
    return false;
  }
  const char* outputDir = opt.m_outputDir.c_str();
  if(!dirExists(opt.m_outputDir))
  {
    std::fprintf(stderr, "Error: output directory '%s' doesn't exists\n\r", outputDir);
    return false;
  }
  return true;
}

static bool fileExists(const std::string& path)
{
  std::ifstream f(path.c_str());
  return f.good();
}

static bool dirExists(const std::string& path)
{
  struct stat info;

  bool rv;
  if(stat(path.c_str(), &info) != 0)
  {
    rv = false;
  }
  else if( info.st_mode & S_IFDIR )
  {
    rv = true;
  }
  else
  {
    rv = false;
  }
  return rv;
}
