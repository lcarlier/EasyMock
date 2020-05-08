#ifndef COMMANDLINEPARSERITF_H
#define COMMANDLINEPARSERITF_H

#include <vector>
#include <string>

const std::string g_inputHeaderParam("-i");
const std::string g_outputDirParam("-o");
const std::string g_helpParamShort("-h");
const std::string g_helpParamLong("--help");

using ExtraArgsList = std::vector<std::string>;

struct EasyMockOptions
{
  std::string m_errorMessage;
  std::string m_helpMessage;
  std::string m_inputHeaderFile;
  std::string m_outputDir;
  ExtraArgsList m_extraArgs;
};

class CommandLineParserItf
{
public:
  virtual EasyMockOptions getParsedArguments(int argc, char *argv[]) const = 0;
  virtual ~CommandLineParserItf() {}
};

#endif /* COMMANDLINEPARSERITF_H */

