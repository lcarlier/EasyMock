/*! \file
 * \brief Contains the interface that must be implemented by a command line
 * parser.
 */
#ifndef COMMANDLINEPARSERITF_H
#define COMMANDLINEPARSERITF_H

#include <vector>
#include <string>
#include <unordered_set>

#include <CodeGeneratorItf.h>

const std::string g_inputHeaderParam("-i");
const std::string g_outputDirParam("-o");
const std::string g_helpParamShort("-h");
const std::string g_helpParamLong("--help");
const std::string g_mockOnlyParam("--mock-only");
const std::string g_changeWorkingDir("--cwd");
const std::string g_generateTypes("--generate-types");
const std::string g_generateAttribute("--generate-attribute");
const std::string g_ignoreFieldGenerationOfParam("--ignore-field-generation-of");
const std::string g_ignoreGenerationOfParam("--ignore-generation-of");

const std::string g_errorInputMissing("Error: The input header file is not provided");
const std::string g_errorOutputMissing("Error: The output directory is not provided");
const std::string g_errorMockOnlyParamMissing("Error: Argument to --mock-only is missing");
const std::string g_errorCwdMissing("Error: Argument to --cwd is missing");
const std::string g_errorCwdMoreThanOnce("Error: Argument to --cwd is given more than once");
const std::string g_errorGenerateAttrAttrMissing("Error: Argument --generate-attribute needs a value");
const std::string g_errorIgnoreFieldGenerationOfArgumentMissing("Error: Argument --ignore-field-generation-of needs a value");
const std::string g_errorIgnoreGenerationOfArgumentMissing("Error: Argument --ignore-generation-of needs a value");

const std::string g_helpMessage =
  "Generate mocks to be used into a unit test inside a specific directory\n\r"
  "Parameters not recognised by EasyMock (e.g. -I, -D) are given to the parser\n\r"
  "responsible for parsing the header file.\n\r"
  "Usage:\n\r"
  "./EasyMockGenerate [OPTIONS...]\n\r"
  "\n\r"
  "OPTIONS are:\n\r"
  "\t-i <header>                    Input header file.\n\r"
  "\t-o <directory>                 Output directory.\n\r"
  "\t--cwd <directory>              Change to the directory passed on this parameter before running the parser.\n\r"
  "\t--mock-only <function>         Mock only the function specified in this parameter.\n\r"
  "\t--generate-types               Generate the used type instead of including the original header.\n\r"
  "\t                               When using this option, the original header (i.e. the header given to -i) doesn't\n\r"
  "\t                               need to be used when compiling the mock.\n\r"
  "\t                               The generated functions signature will not contain any function attribute unless\n\r"
  "\t                               the --generate-attribute option is used.\n\r"
  "\t                               Can be used several times.\n\r"
  "\t--generate-attribute           Generate the function attribute if the function has been declared with it.\n\r"
  "\t                               E.G. if a function has been declared with the format attribute, give the parameter\n\r"
  "\t                               \"--generate-attribute format\" will generate the code __attribute__((format(x, y, z))) where\n\r"
  "\t                               x, y and z are the parameters given to the format attribute.\n\r"
  "\t                               Can be used several times.\n\r"
  "\t--ignore-generation-of         Ignore the parsing and the generation of the given function.\n\r"
  "\t                               Can be used several times.\n\r"
  "\t--ignore-field-generation-of   Ignore the field generation of the given struct or union type.\n\r"
  "\t                               Consider using this option if mocking some types takes too much time.\n\r"
  "\t                               The list is given to the parser which ignores the reporting the fields of\n\r"
  "\t                               the given types.\n\r"
  "\t                               Can be used several times.\n\r"
  "\t-h, --help                     Print usage.\n\r";

using ExtraArgsList = std::vector<std::string>;

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
   *
   * If this string is not empty, the value of the other members are not valid.
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
   * \brief The value given to the `--cwd` parameter.
   */
  std::string m_changeWorkingDir;
  /*!
   * \brief The values given to the `--mock-only` parameter.
   */
  MockOnlyList m_mockOnlyList;
  /*!
   * \brief All the values that are not recognised by the command line parser.
   */
  ExtraArgsList m_extraArgs;
  /*!
   * \brief Generate the used type instead of including the original header.
   */
  bool m_generateTypes;
  /*!
   * \brief All the function attributes to generate.
   */
  GenerateAttrList m_generateAttrList;
  /*!
   * \brief The values given to the `--ignore-field-generation-of` parameter.
   */
  IgnoreTypeFieldList m_ignoreTypeList;
  /*!
   * \brief The values given to the `--ignore-generation-of` parameter.
   */
  IgnoreFunList m_ignoreFunList;
};

/*!
 * \brief The interface that must be implemented by a command line
 * parser.
 *
 * The current sent of parameters to be supported is:
 * * `-i`: the input header to be mocked
 * * `-o`: the directory where to create the mocks
 * * `--cwd`: change to the directory passed on this parameter before running the parser
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
  virtual EasyMockOptions getParsedArguments(int argc,const char *argv[]) const = 0;
  virtual ~CommandLineParserItf() {}
};

#endif /* COMMANDLINEPARSERITF_H */
