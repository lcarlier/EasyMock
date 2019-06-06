#include <cstdio>
#include <cstdlib>
#include <ctemplate/template.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include "CodeGeneratorCTemplate.h"
#include <boost/filesystem.hpp>

#include <sys/stat.h>
#include <fcntl.h>

#define TEMPLATE_VAR(VAR_NAME) "{{" VAR_NAME "}}"
#define TEMPLATE_BEG_SECTION(SECTION_NAME) "{{#" SECTION_NAME "}}"
#define TEMPLATE_END_SECTION(SECTION_NAME) "{{/" SECTION_NAME "}}"

#define MOCK_FRAMEWORK_NAME "easyMock"
#define MOCK_FRAMEWORK_NAME_UPPER "EASYMOCK"

#define CARRIAGE_RETURN "\n"

#define MOCKED_HEADER_FILENAME "MOCKED_HEADER_FILENAME"
#define MOCKED_FILE_NAME_WITHOUT_EXT_UPPER "MOCKED_FILE_NAME_WITHOUT_EXT_UPPER"
#define FUNCTION_SECTION "FUNCTION_SECTION"
#define FUNCTION_PARAM_SECTION "FUNCTION_PARAM_SECTION"
#define FUNCTION_PARAM_SECTION_SEPARATOR FUNCTION_PARAM_SECTION "_separator"
#define FUNCTION_PARAM_TYPE "TYPEDEF_PARAM_RETURN_VALUE"
#define FUNCTION_PARAM_NAME "TYPEDEF_PARAM_NAME"
#define FUNCTION_RETURN_VALUE_PARAM_SECTION "FUNCTION_RETURN_VALUE_PARAM_SECTION"
#define FUNCTION_RETURN_VALUE_PARAM "FUNCTION_RETURN_VALUE_PARAM"
#define FUNCTION_RETURN_VALUE "FUNCTION_RETURN_VALUE"
#define FUNCTION_NAME "FUNCTION_NAME"
#define FUNCTION_NAME_UPPER "FUNCTION_NAME_UPPER"
#define FUNCTION_MATCHER_LIST_SECTION "FUNCTION_MATCHER_LIST_SECTION"
#define FUNCTION_PARAM_LIST_SECTION "FUNCTION_PARAM_LIST_SECTION"

#define VOID_FUNCTION_RETURN_VALUE "void"

#define IF_RETURN_VALUE(STR_TO_PRINT) \
  TEMPLATE_BEG_SECTION(FUNCTION_RETURN_VALUE_PARAM_SECTION) \
  STR_TO_PRINT \
  TEMPLATE_END_SECTION(FUNCTION_RETURN_VALUE_PARAM_SECTION)

#define IF_PARAM_LIST(STR_TO_PRINT) \
  TEMPLATE_BEG_SECTION(FUNCTION_PARAM_LIST_SECTION) \
  STR_TO_PRINT \
  TEMPLATE_END_SECTION(FUNCTION_PARAM_LIST_SECTION)

#define FUNCTION_PARAM_LIST \
  TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION) \
    TEMPLATE_VAR(FUNCTION_PARAM_TYPE) " " TEMPLATE_VAR(FUNCTION_PARAM_NAME) \
    TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION_SEPARATOR) \
      ", " \
    TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION_SEPARATOR) \
  TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)

#define FUNCTION_MATCHER_LIST \
  TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION) \
    MOCK_FRAMEWORK_NAME_UPPER "_MATCHER match_" TEMPLATE_VAR(FUNCTION_PARAM_NAME) \
    TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION_SEPARATOR)\
      ", " \
    TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION_SEPARATOR) \
  TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)

#define FUNCTION_EXPECT_AND_RETURN_SIGNATURE \
"void " TEMPLATE_VAR(FUNCTION_NAME) "_ExpectAndReturn(" FUNCTION_PARAM_LIST IF_RETURN_VALUE(IF_PARAM_LIST(", ") TEMPLATE_VAR(FUNCTION_RETURN_VALUE) " to_return") IF_PARAM_LIST(", ") FUNCTION_MATCHER_LIST ")"

#define RESET_ALL_MOCK_FUNCTION_NAME \
MOCK_FRAMEWORK_NAME "_resetAllMocksInThisHeader"

#define FUNCTION_RESET_ALL_MOCK_SIGNATURE \
"static void " RESET_ALL_MOCK_FUNCTION_NAME "()"

#define VERIFY_ALL_MOCK_FUNCTION_NAME \
MOCK_FRAMEWORK_NAME "_verifyAllMocksInThisHeader"

#define FUNCTION_VERIFY_ALL_MOCK_SIGNATURE \
"static bool " VERIFY_ALL_MOCK_FUNCTION_NAME "()"

#define FUNCTION_MOCK_DATA_TYPE \
TEMPLATE_VAR(FUNCTION_NAME) "_data"

#define FUNCTION_MOCK_DATA_RETURN_VALUE_VARIABLE \
TEMPLATE_VAR(FUNCTION_NAME) "_returnValue"

#define TEMPLATE_FUNCTION_TO_BE_MOCKED TEMPLATE_VAR(FUNCTION_RETURN_VALUE) " " TEMPLATE_VAR(FUNCTION_NAME) "(" FUNCTION_PARAM_LIST ")"
#define MOCKED_FUN_CLASS(F_NAME) "mocked_" F_NAME
#define TEMPLATE_MOCKED_FUN_CLASS MOCKED_FUN_CLASS(TEMPLATE_VAR(FUNCTION_NAME))

#define GENERATE_COMMENT \
"//------------------- GENERATING '" TEMPLATE_FUNCTION_TO_BE_MOCKED "' -------------------"

#define END_GENERATE_COMMENT \
"//----------------- END GENERATION '" TEMPLATE_FUNCTION_TO_BE_MOCKED "' -----------------"

static const char templateText[] =
        "#include <" TEMPLATE_VAR(MOCKED_HEADER_FILENAME) ">" CARRIAGE_RETURN
        "#include <" MOCK_FRAMEWORK_NAME "_" TEMPLATE_VAR(MOCKED_HEADER_FILENAME) ">" CARRIAGE_RETURN
        "#include <easyMock_framework.h>" CARRIAGE_RETURN
        "#include <MockedFunction.h>" CARRIAGE_RETURN
        "#include <string>" CARRIAGE_RETURN
        CARRIAGE_RETURN
        FUNCTION_RESET_ALL_MOCK_SIGNATURE ";" CARRIAGE_RETURN
        FUNCTION_VERIFY_ALL_MOCK_SIGNATURE ";" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_SECTION)
        GENERATE_COMMENT CARRIAGE_RETURN
        "typedef struct {" CARRIAGE_RETURN
        IF_RETURN_VALUE("    " TEMPLATE_VAR(FUNCTION_RETURN_VALUE) " " FUNCTION_MOCK_DATA_RETURN_VALUE_VARIABLE ";" CARRIAGE_RETURN)
        "} " FUNCTION_MOCK_DATA_TYPE";" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "static MockedFunction<" FUNCTION_MOCK_DATA_TYPE "> " TEMPLATE_MOCKED_FUN_CLASS "(\"" TEMPLATE_FUNCTION_TO_BE_MOCKED "\");" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "extern \"C\" " TEMPLATE_FUNCTION_TO_BE_MOCKED CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    bool printCallStack = true;" CARRIAGE_RETURN
        CARRIAGE_RETURN
        IF_RETURN_VALUE("    " TEMPLATE_VAR(FUNCTION_RETURN_VALUE) " default_res;" CARRIAGE_RETURN CARRIAGE_RETURN)
        "    if(!" TEMPLATE_MOCKED_FUN_CLASS ".addActuallCall())" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        easyMock_addError(printCallStack, \"Error : unexpected call of '%s'." IF_RETURN_VALUE(" " TEMPLATE_VAR(FUNCTION_NAME) " is returning a random value.") "\", " TEMPLATE_MOCKED_FUN_CLASS ".getName().c_str());" CARRIAGE_RETURN
        "        return" IF_RETURN_VALUE(" " TEMPLATE_VAR(FUNCTION_RETURN_VALUE) "()") ";" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "    " FUNCTION_MOCK_DATA_TYPE " currentDataCall;" CARRIAGE_RETURN
        "    if (!" TEMPLATE_MOCKED_FUN_CLASS ".getCurrentCallParam(currentDataCall))" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        easyMock_addError(printCallStack, \"BUG IN EASYMOCK: CONTACT DEVELOPPER TO FIX THIS\");" CARRIAGE_RETURN
        "        return" IF_RETURN_VALUE(" " TEMPLATE_VAR(FUNCTION_RETURN_VALUE) "()") ";" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        CARRIAGE_RETURN
        IF_RETURN_VALUE("    default_res = currentDataCall." FUNCTION_MOCK_DATA_RETURN_VALUE_VARIABLE ";" CARRIAGE_RETURN)
        "    const std::string currentCall = easyMock_popCurrentCall();" CARRIAGE_RETURN
        "    const std::string &curFuncCall = " TEMPLATE_MOCKED_FUN_CLASS ".getName();" CARRIAGE_RETURN
        "    if(currentCall.compare(curFuncCall) != 0)" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        easyMock_addError(printCallStack, \"Error : got call to '%s',  but was expecting call to '%s'\", " TEMPLATE_MOCKED_FUN_CLASS ".getName().c_str(), currentCall.c_str());" CARRIAGE_RETURN
        "        return" IF_RETURN_VALUE(" default_res") ";" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        IF_RETURN_VALUE(CARRIAGE_RETURN "    return default_res;" CARRIAGE_RETURN)
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "extern \"C\" " FUNCTION_EXPECT_AND_RETURN_SIGNATURE CARRIAGE_RETURN CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    " FUNCTION_MOCK_DATA_TYPE " mockedData;" CARRIAGE_RETURN
        IF_RETURN_VALUE("    mockedData." FUNCTION_MOCK_DATA_RETURN_VALUE_VARIABLE " = to_return;" CARRIAGE_RETURN)
        "    " TEMPLATE_MOCKED_FUN_CLASS ".addExpectedCall(mockedData);" CARRIAGE_RETURN
        "    easyMock_addCall(" TEMPLATE_MOCKED_FUN_CLASS ".getName());" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        END_GENERATE_COMMENT CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_SECTION)
        CARRIAGE_RETURN
        FUNCTION_RESET_ALL_MOCK_SIGNATURE CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_SECTION)
        "    " TEMPLATE_MOCKED_FUN_CLASS ".reset();" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_SECTION)
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        FUNCTION_VERIFY_ALL_MOCK_SIGNATURE CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    bool rv = true;" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_SECTION)
        "    if(!" TEMPLATE_MOCKED_FUN_CLASS ".verify())" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        rv = false;" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_SECTION)
        "    return rv;" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "static " MOCK_FRAMEWORK_NAME "_mockedFileRegister_t mockedRegister = {\"" TEMPLATE_VAR(MOCKED_HEADER_FILENAME) "\", &" RESET_ALL_MOCK_FUNCTION_NAME ", &" VERIFY_ALL_MOCK_FUNCTION_NAME " };" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "static void __attribute__((constructor(102))) " MOCK_FRAMEWORK_NAME "_register_this_header()" CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    " MOCK_FRAMEWORK_NAME "_registerMock(&mockedRegister);" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "static void __attribute__((destructor)) " MOCK_FRAMEWORK_NAME "_unregister_this_header()" CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    " MOCK_FRAMEWORK_NAME "_unregisterMock(&mockedRegister);" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN;

static const char headerFileTemplate[] =
        "#ifndef _" TEMPLATE_VAR(MOCKED_FILE_NAME_WITHOUT_EXT_UPPER) "_" MOCK_FRAMEWORK_NAME_UPPER "_H" CARRIAGE_RETURN
        "#define _" TEMPLATE_VAR(MOCKED_FILE_NAME_WITHOUT_EXT_UPPER) "_" MOCK_FRAMEWORK_NAME_UPPER "_H" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "#include <" TEMPLATE_VAR(MOCKED_HEADER_FILENAME) ">" CARRIAGE_RETURN
        "#include <" MOCK_FRAMEWORK_NAME ".h>" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "#ifdef __cplusplus" CARRIAGE_RETURN
        "extern \"C\" {" CARRIAGE_RETURN
        "#endif" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_SECTION)
        "//------------------- GENERATING '" TEMPLATE_FUNCTION_TO_BE_MOCKED "' -------------------" CARRIAGE_RETURN
        FUNCTION_EXPECT_AND_RETURN_SIGNATURE ";" CARRIAGE_RETURN
        "//----------------- END GENERATION '" TEMPLATE_FUNCTION_TO_BE_MOCKED "' -----------------" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_SECTION)
        "#ifdef __cplusplus" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        "#endif" CARRIAGE_RETURN
        "#endif" CARRIAGE_RETURN;

static void fillInTemplateVariables(ctemplate::TemplateDictionary *dict, const std::string &mockedHeader, const ElementToMockVector &fList);
static void generateFunctionParamSection(ctemplate::TemplateDictionary *dict, const ParameterVector *functionParam);
static bool generateCodeToFile(const std::string &outDir, const std::string &filename, const std::string &extension, const std::string &generatedCode);

bool CodeGeneratorCTemplate::generateCode(const std::string& outDir, const std::string &fullPathToHeaderToMock, const ElementToMockVector& elem) const
{
  ctemplate::StringToTemplateCache("programTemplate", templateText, ctemplate::DO_NOT_STRIP);
  ctemplate::StringToTemplateCache("headerTemplate", headerFileTemplate, ctemplate::DO_NOT_STRIP);

  ctemplate::TemplateDictionary dict("generateCode");
  ctemplate::TemplateDictionary headerDict("headerCode");

  std::string filenameToMock = boost::filesystem::path(fullPathToHeaderToMock).filename().string();
  fillInTemplateVariables(&dict, filenameToMock, elem);
  fillInTemplateVariables(&headerDict, filenameToMock, elem);

  std::string generatedCode;
  ctemplate::ExpandTemplate("programTemplate", ctemplate::DO_NOT_STRIP, &dict, &generatedCode);
  if (!generateCodeToFile(outDir, filenameToMock, "cpp", generatedCode))
  {
    return false;
  }

  generatedCode.clear();
  ctemplate::ExpandTemplate("headerTemplate", ctemplate::DO_NOT_STRIP, &headerDict, &generatedCode);
  if (!generateCodeToFile(outDir, filenameToMock, "h", generatedCode))
  {
    return false;
  }

  return true;
}

static void fillInTemplateVariables(ctemplate::TemplateDictionary *rootDictionnary, const std::string &mockedHeader, const ElementToMockVector &fList)
{
  rootDictionnary->SetValue(MOCKED_HEADER_FILENAME, mockedHeader);
  std::string fileNameWithoutExtUpper = mockedHeader.substr(0, mockedHeader.find_last_of("."));
  std::transform(fileNameWithoutExtUpper.begin(), fileNameWithoutExtUpper.end(), fileNameWithoutExtUpper.begin(), ::toupper);
  rootDictionnary->SetValue(MOCKED_FILE_NAME_WITHOUT_EXT_UPPER, fileNameWithoutExtUpper);
  for (ElementToMockVector::const_iterator it = fList.begin(); it != fList.end(); ++it)
  {
    const ElementToMock *f = *it;
    switch (*f->getMockType())
    {
      case ETS_function:
      {
        ctemplate::TemplateDictionary *functionSectionDict = rootDictionnary->AddSectionDictionary(FUNCTION_SECTION);
        functionSectionDict->SetValue(FUNCTION_NAME, *f->getName());
        std::string upperString(*f->getName());
        std::transform(upperString.begin(), upperString.end(), upperString.begin(), ::toupper);
        functionSectionDict->SetValue(FUNCTION_NAME_UPPER, upperString);
        functionSectionDict->SetValue(FUNCTION_RETURN_VALUE, *f->getReturnType());
        if (*f->getReturnType() != VOID_FUNCTION_RETURN_VALUE)
        {
          ctemplate::TemplateDictionary *returnValParamDict = functionSectionDict->AddSectionDictionary(FUNCTION_RETURN_VALUE_PARAM_SECTION);
          returnValParamDict->SetValue(FUNCTION_RETURN_VALUE, *f->getReturnType());
        }
        generateFunctionParamSection(functionSectionDict, f->getFunctionsParameters());
        break;
      }
      default:
        break;
    }
  }
}

static void generateFunctionParamSection(ctemplate::TemplateDictionary *functionSectionDict, const ParameterVector *functionParam)
{
  if (functionParam->size() > 0)
  {
    //This specific section to show the comma ',' conditionally for the expect and return function generation
    functionSectionDict->AddSectionDictionary(FUNCTION_PARAM_LIST_SECTION);
  }
  for (ParameterVector::const_iterator it = functionParam->begin(); it != functionParam->end(); ++it)
  {
    ctemplate::TemplateDictionary* newTypedefParamSection = functionSectionDict->AddSectionDictionary(FUNCTION_PARAM_SECTION);
    const Parameter &fParam = *it;
    newTypedefParamSection->SetValue(FUNCTION_PARAM_TYPE, fParam.type);
    newTypedefParamSection->SetValue(FUNCTION_PARAM_NAME, fParam.name);
  }
}

static bool generateCodeToFile(const std::string &outDir, const std::string &filename, const std::string &extension, const std::string &generatedCode)
{
  bool rv = true;
  FILE *f = NULL;
  std::string outFilename(outDir);
  outFilename.append("/" MOCK_FRAMEWORK_NAME "_");
  outFilename.append(filename.substr(0, filename.find_last_of(".")));
  outFilename.append(".");
  outFilename.append(extension);

  std::fprintf(stdout, "Generating %s\n\r", outFilename.c_str());
  f = std::fopen(outFilename.c_str(), "w+");
  if (f == NULL)
  {
    std::fprintf(stderr, "Error creating %s: %s", outFilename.c_str(), strerror(errno));
    rv = false;
    goto closeFile;
  }
  if (std::fprintf(f, "%s", generatedCode.c_str()) < 0)
  {
    std::fprintf(stderr, "Error writing into %s: %s", outFilename.c_str(), strerror(errno));
    rv = false;
    goto closeFile;
  }
closeFile:
  if (f != NULL)
  {
    std::fclose(f);
  }

  return rv;
}
