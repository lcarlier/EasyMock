/*! \file
 * \brief Contains the interface that must be implemented by a command line
 * parser.
 */
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

/*!
 * \brief Represents the value of all the options that are given to
 * EasyMockGenerate.
 */
struct EasyMockOptions
{
  /*!
   * \brief The error message while parsing the command line argument.
   *
   * If this string is not empty, the value of the other members are not valid.
   */
  std::string m_errorMessage;
  /*!
   * \brief The help message to be printed if required.
   */
  std::string m_helpMessage;
  /*!
   * \brief The value given to the `-i` parameter.
   */
  std::string m_inputHeaderFile;
  /*!
   * \brief The value given to the `-o` parameter.
   */
  std::string m_outputDir;
  /*!
   * \brief The values given to the `--mock-only` parameter.
   */
  MockOnlyList m_mockOnlyList;
  /*!
   * \brief All the values that are not recognised by the command line parser.
   */
  ExtraArgsList m_extraArgs;
};

/*!
 * \brief The interface that must be implemented by a command line
 * parser.
 *
 * The current sent of parameters to be supported is:
 * * `-i`: the input header to  be mocked
 * * `-o`: the directory where to create the mocks
 * * `-h`: prints the help string
 * * `--help`: prints the help
 * * `--mock-only`: Can be used several time. Select which function must be mocked.
 */
class CommandLineParserItf
{
public:
 /*!
  * \brief Parses the command line arguments.
  *
  * \param argc The number of arguments in argv.
  * \param argv The value of each arguments.
  *
  * argv[0] is the name of the executable.
  *
  * \return An EasyMockOptions which contains the value of all the options
  * that are given to EasyMockGenerate.
  */
  virtual EasyMockOptions getParsedArguments(int argc, char *argv[]) const = 0;
  virtual ~CommandLineParserItf() {}
};

#endif /* COMMANDLINEPARSERITF_H */

