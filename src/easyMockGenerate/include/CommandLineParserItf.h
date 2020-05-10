#ifndef COMMANDLINEPARSERITF_H
#define COMMANDLINEPARSERITF_H

#include <vector>
#include <string>
#include <unordered_set>

const std::string g_inputHeaderParam("-i");
const std::string g_outputDirParam("-o");
const std::string g_helpParamShort("-h");
const std::string g_helpParamLong("--help");
const std::string g_mockOnlyParam("--mock-only");

using ExtraArgsList = std::vector<std::string>;
using MockOnlyList = std::unordered_set<std::string>;

struct EasyMockOptions
{
  std::string m_errorMessage;
  std::string m_helpMessage;
  std::string m_inputHeaderFile;
  std::string m_outputDir;
  ExtraArgsList m_extraArgs;
  MockOnlyList m_mockOnlyList;
};

class CommandLineParserItf
{
public:
  virtual EasyMockOptions getParsedArguments(int argc, char *argv[]) const = 0;
  virtual ~CommandLineParserItf() {}
};

#endif /* COMMANDLINEPARSERITF_H */

