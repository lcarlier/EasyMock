#include <cstdio>
#include <cstdlib>
#include <ctemplate/template.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include "CodeGeneratorCTemplate.h"

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


#define TEMPLATE_FUNCTION_TO_BE_MOCKED TEMPLATE_VAR(FUNCTION_RETURN_VALUE) " " TEMPLATE_VAR(FUNCTION_NAME) "(" FUNCTION_PARAM_LIST ")"
#define MOCKED_FUN_CLASS(F_NAME) "mocked_" F_NAME
#define TEMPLATE_MOCKED_FUN_CLASS MOCKED_FUN_CLASS(TEMPLATE_VAR(FUNCTION_NAME))

#define GENERATE_COMMENT \
"//------------------- GENERATING '" TEMPLATE_FUNCTION_TO_BE_MOCKED "' -------------------"

#define END_GENERATE_COMMENT \
"//----------------- END GENERATION '" TEMPLATE_FUNCTION_TO_BE_MOCKED "' -----------------"

#if 0
static const char templateText[] =
        "#include <" TEMPLATE_VAR(MOCKED_HEADER_FILENAME) ">" CARRIAGE_RETURN
        "#include <stdio.h>" CARRIAGE_RETURN
        "#include <string.h>" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "static void " MOCK_FRAMEWORK_NAME "_reset_all_mocks_in_this_header();" CARRIAGE_RETURN
        "static void " MOCK_FRAMEWORK_NAME "_verify_all_mocks_in_this_header();" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_SECTION)
GENERATE_COMMENT CARRIAGE_RETURN
        "typedef struct" CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION)
"    " TEMPLATE_VAR(FUNCTION_PARAM_TYPE)" " TEMPLATE_VAR(FUNCTION_PARAM_NAME) ";" CARRIAGE_RETURN
TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)
TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION)
"    " MOCK_FRAMEWORK_NAME_UPPER "_MATCHER match_" TEMPLATE_VAR(FUNCTION_PARAM_NAME) ";" CARRIAGE_RETURN
TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)
TEMPLATE_BEG_SECTION(FUNCTION_RETURN_VALUE_PARAM_SECTION)
"    " TEMPLATE_VAR(FUNCTION_RETURN_VALUE) " to_return;" CARRIAGE_RETURN
TEMPLATE_END_SECTION(FUNCTION_RETURN_VALUE_PARAM_SECTION)
"    char check_params;" CARRIAGE_RETURN
        "} " TEMPLATE_VAR(FUNCTION_NAME) "_call;" CARRIAGE_RETURN
CARRIAGE_RETURN
        "typedef struct" CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    int expectedCalls;" CARRIAGE_RETURN
        "    int actualCalls;" CARRIAGE_RETURN
        "    " MOCK_FRAMEWORK_NAME_UPPER "_" TEMPLATE_VAR(FUNCTION_NAME_UPPER) "_CALLBACK callback;" CARRIAGE_RETURN
        "    " TEMPLATE_VAR(FUNCTION_NAME) "_call calls[MAX_FUNC_CALL];" CARRIAGE_RETURN
        "} " TEMPLATE_VAR(FUNCTION_NAME) "_struct;" CARRIAGE_RETURN
CARRIAGE_RETURN
        "static " TEMPLATE_VAR(FUNCTION_NAME) "_struct " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst;" CARRIAGE_RETURN
CARRIAGE_RETURN
TEMPLATE_FUNCTION_TO_BE_MOCKED CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_RETURN_VALUE_PARAM_SECTION)
"    " TEMPLATE_VAR(FUNCTION_RETURN_VALUE) " default_res = " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.calls[0].to_return;" CARRIAGE_RETURN
TEMPLATE_END_SECTION(FUNCTION_RETURN_VALUE_PARAM_SECTION)
"    int " MOCK_FRAMEWORK_NAME "_i;" CARRIAGE_RETURN
        "    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.actualCalls++;" CARRIAGE_RETURN
CARRIAGE_RETURN
        "    if (" TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.callback != NULL)" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        " IF_RETURN_VALUE("default_res = ") TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.callback(" FUNCTION_PARAM_LIST IF_PARAM_LIST(", ") TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.actualCalls)" ";" CARRIAGE_RETURN
        "        return" IF_RETURN_VALUE(" default_res") ";" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        "    if (" TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.expectedCalls == 0)" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        " MOCK_FRAMEWORK_NAME "_add_error_message((char *) \"WARNING : unexpected call of '" TEMPLATE_VAR(FUNCTION_NAME) "', returning random value.\");" CARRIAGE_RETURN
        "        return" IF_RETURN_VALUE(" default_res") ";" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "    if(strcmp(" MOCK_FRAMEWORK_NAME "_get_current_call(), \"int " TEMPLATE_VAR(FUNCTION_NAME) "(" FUNCTION_PARAM_LIST ")\") != 0)" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        char buffer[OP_ERROR_MESSAGE_LENGTH];" CARRIAGE_RETURN
        "        snprintf(buffer, OP_ERROR_MESSAGE_LENGTH, \"WARNING : got call to 'int " TEMPLATE_VAR(FUNCTION_NAME) "(" FUNCTION_PARAM_LIST ")',  but was expecting call to '%s'\", " MOCK_FRAMEWORK_NAME "_get_current_call());" CARRIAGE_RETURN
        "        " MOCK_FRAMEWORK_NAME "_add_error_message(buffer);" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        "    " MOCK_FRAMEWORK_NAME "_pop_call();" CARRIAGE_RETURN
        CARRIAGE_RETURN
        IF_PARAM_LIST(
        "    if (" TEMPLATE_VAR(FUNCTION_NAME) "}}_struct_inst.calls[0].check_params == 1)" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION)
        "        if(" TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.calls[0].match_" TEMPLATE_VAR(FUNCTION_PARAM_NAME) ") {" CARRIAGE_RETURN
        "            void * val1 = (void *) &" TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.calls[0]." TEMPLATE_VAR(FUNCTION_PARAM_NAME) ";" CARRIAGE_RETURN
        "            void * val2 = (void *) &" TEMPLATE_VAR(FUNCTION_PARAM_NAME) ";" CARRIAGE_RETURN
        "            int match_result = " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.calls[0].match_" TEMPLATE_VAR(FUNCTION_PARAM_NAME) "(val1, val2, \"" TEMPLATE_VAR(FUNCTION_PARAM_NAME) "\", get_matcher_message());" CARRIAGE_RETURN
        "            if(match_result){" CARRIAGE_RETURN
        "                char buffer[OP_ERROR_MESSAGE_LENGTH];" CARRIAGE_RETURN
        "                snprintf(buffer, OP_ERROR_MESSAGE_LENGTH, \"WARNING : on call number %d of '" TEMPLATE_VAR(FUNCTION_NAME) "', %s\"," TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.actualCalls, get_matcher_message());" CARRIAGE_RETURN
        "                " MOCK_FRAMEWORK_NAME "_add_error_message((char *) buffer);" CARRIAGE_RETURN
        "            }" CARRIAGE_RETURN
        "        }" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)
        "    }" CARRIAGE_RETURN
        )
CARRIAGE_RETURN
        "    for(" MOCK_FRAMEWORK_NAME "_i = 1; " MOCK_FRAMEWORK_NAME "_i < " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.expectedCalls; " MOCK_FRAMEWORK_NAME "_i++) {" CARRIAGE_RETURN
        "        " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.calls[" MOCK_FRAMEWORK_NAME "_i - 1] = " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.calls[" MOCK_FRAMEWORK_NAME "_i];" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.expectedCalls--;" CARRIAGE_RETURN
        "    return" IF_RETURN_VALUE(" default_res") ";" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "void " TEMPLATE_VAR(FUNCTION_NAME) "_MockReset()" CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.expectedCalls = 0;" CARRIAGE_RETURN
        "    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.actualCalls = 0;" CARRIAGE_RETURN
        "    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.callback = NULL;" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "void " TEMPLATE_VAR(FUNCTION_NAME) "_MockWithCallback(" MOCK_FRAMEWORK_NAME_UPPER "_" TEMPLATE_VAR(FUNCTION_NAME_UPPER) "_CALLBACK callback)" CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    " MOCK_FRAMEWORK_NAME "_add_reset_callback(" MOCK_FRAMEWORK_NAME "_reset_all_mocks_in_this_header);" CARRIAGE_RETURN
        "    " MOCK_FRAMEWORK_NAME "_add_verify_callback(" MOCK_FRAMEWORK_NAME "_verify_all_mocks_in_this_header);" CARRIAGE_RETURN
        "    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.callback = callback;" CARRIAGE_RETURN
        "    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.expectedCalls = 0;" CARRIAGE_RETURN
        "    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.actualCalls = 0;" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "void " TEMPLATE_VAR(FUNCTION_NAME) "_VerifyMock()" CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    if (" TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.expectedCalls != 0) {" CARRIAGE_RETURN
        "        char buffer[OP_ERROR_MESSAGE_LENGTH];" CARRIAGE_RETURN
        "        snprintf(buffer, OP_ERROR_MESSAGE_LENGTH, \"WARNING : Bad number of calls (%d) for '" TEMPLATE_VAR(FUNCTION_NAME) "'\"," TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.actualCalls);" CARRIAGE_RETURN
        "        " MOCK_FRAMEWORK_NAME "_add_error_message((char *) buffer);" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        FUNCTION_EXPECT_AND_RETURN_SIGNATURE CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    if(" TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.callback != NULL)" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        " TEMPLATE_VAR(FUNCTION_NAME) "_MockReset();" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "    if(" TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.expectedCalls >= MAX_FUNC_CALL)" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        printf(\"WARNING : aborting " TEMPLATE_VAR(FUNCTION_NAME) "_ExpectAndReturn, call stack overload.\");" CARRIAGE_RETURN
        "        return;" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "    " MOCK_FRAMEWORK_NAME "_add_reset_callback(" MOCK_FRAMEWORK_NAME "_reset_all_mocks_in_this_header);" CARRIAGE_RETURN
        "    " MOCK_FRAMEWORK_NAME "_add_verify_callback(" MOCK_FRAMEWORK_NAME "_verify_all_mocks_in_this_header);" CARRIAGE_RETURN
        "    " MOCK_FRAMEWORK_NAME "_add_call((char *)\"int " TEMPLATE_VAR(FUNCTION_NAME) "(" FUNCTION_PARAM_LIST ")\");" CARRIAGE_RETURN
TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION)
"    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.calls[" TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.expectedCalls]." TEMPLATE_VAR(FUNCTION_PARAM_NAME) " = " TEMPLATE_VAR(FUNCTION_PARAM_NAME) ";" CARRIAGE_RETURN
TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)
TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION)
"    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.calls[" TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.expectedCalls].match_" TEMPLATE_VAR(FUNCTION_PARAM_NAME) " = match_" TEMPLATE_VAR(FUNCTION_PARAM_NAME) ";" CARRIAGE_RETURN
TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)
"    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.calls[" TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.expectedCalls].to_return = to_return;" CARRIAGE_RETURN
        "    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.calls[" TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.expectedCalls].check_params = 1;" CARRIAGE_RETURN
        "    " TEMPLATE_VAR(FUNCTION_NAME) "_struct_inst.expectedCalls++;" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        END_GENERATE_COMMENT CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_SECTION)
CARRIAGE_RETURN
        "static void " MOCK_FRAMEWORK_NAME "_reset_all_mocks_in_this_header()" CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_SECTION)
"    " TEMPLATE_VAR(FUNCTION_NAME) "_MockReset();" CARRIAGE_RETURN
TEMPLATE_END_SECTION(FUNCTION_SECTION)
"}" CARRIAGE_RETURN
CARRIAGE_RETURN
        "static void " MOCK_FRAMEWORK_NAME "_verify_all_mocks_in_this_header()" CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_SECTION)
"    " TEMPLATE_VAR(FUNCTION_NAME) "_VerifyMock();" CARRIAGE_RETURN
TEMPLATE_END_SECTION(FUNCTION_SECTION)
"}" CARRIAGE_RETURN
        "static " MOCK_FRAMEWORK_NAME "_mockedFileRegister_t mockedRegister = {\"" TEMPLATE_VAR(MOCKED_HEADER_FILENAME) "\", &" MOCK_FRAMEWORK_NAME "_reset_all_mocks_in_this_header, &" MOCK_FRAMEWORK_NAME "_verify_all_mocks_in_this_header };" CARRIAGE_RETURN
        "static void __attribute__((constructor(102))) " MOCK_FRAMEWORK_NAME "_register_this_header()" CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    " MOCK_FRAMEWORK_NAME "_registerMock(&mockedRegister);" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN;
#endif
static const char templateText[] =
        "#include <" TEMPLATE_VAR(MOCKED_HEADER_FILENAME) ">" CARRIAGE_RETURN
        "#include <stub_" TEMPLATE_VAR(MOCKED_HEADER_FILENAME) ">" CARRIAGE_RETURN
        "#include <easyMock_framework.h>" CARRIAGE_RETURN
        "#include <string.h>" CARRIAGE_RETURN
        CARRIAGE_RETURN
        FUNCTION_RESET_ALL_MOCK_SIGNATURE ";" CARRIAGE_RETURN
        FUNCTION_VERIFY_ALL_MOCK_SIGNATURE ";" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_SECTION)
GENERATE_COMMENT CARRIAGE_RETURN
        "static MockedFunction " TEMPLATE_MOCKED_FUN_CLASS "(\"" TEMPLATE_FUNCTION_TO_BE_MOCKED "\");" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "extern \"C\" " TEMPLATE_FUNCTION_TO_BE_MOCKED CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    bool printCallStack = true;" CARRIAGE_RETURN
        "    if(!" TEMPLATE_MOCKED_FUN_CLASS ".addActuallCall())" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        easyMock_addError(printCallStack, \"Error : unexpected call of '%s'\", " TEMPLATE_MOCKED_FUN_CLASS ".getName());" CARRIAGE_RETURN
        "        return;" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "    const char *currentCall = easyMock_popCurrentCall();" CARRIAGE_RETURN
        "    if(strcmp(currentCall, " TEMPLATE_MOCKED_FUN_CLASS ".getName()) != 0)" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        easyMock_addError(printCallStack, \"Error : got call to '%s',  but was expecting call to '%s'\", " TEMPLATE_MOCKED_FUN_CLASS ".getName(), currentCall);" CARRIAGE_RETURN
        "        return;" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "extern \"C\" " FUNCTION_EXPECT_AND_RETURN_SIGNATURE CARRIAGE_RETURN CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    " TEMPLATE_MOCKED_FUN_CLASS ".addExpectedCall();" CARRIAGE_RETURN
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
        "static " MOCK_FRAMEWORK_NAME "_mockedFileRegister_t mockedRegister = {\"" TEMPLATE_VAR(MOCKED_HEADER_FILENAME) "\", &" RESET_ALL_MOCK_FUNCTION_NAME ", &" VERIFY_ALL_MOCK_FUNCTION_NAME " };" CARRIAGE_RETURN
        "static void __attribute__((constructor(102))) " MOCK_FRAMEWORK_NAME "_register_this_header()" CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    " MOCK_FRAMEWORK_NAME "_registerMock(&mockedRegister);" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN;

static const char headerFileTemplate[] =
        "#ifndef _" TEMPLATE_VAR(MOCKED_FILE_NAME_WITHOUT_EXT_UPPER) "_STUB_H" CARRIAGE_RETURN
        "#define _" TEMPLATE_VAR(MOCKED_FILE_NAME_WITHOUT_EXT_UPPER) "_STUB_H" CARRIAGE_RETURN
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

static void fillInTemplateVariables(ctemplate::TemplateDictionary *dict, const std::string &mockedHeader, const ElementToStubVector &fList);
static void generateFunctionParamSection(ctemplate::TemplateDictionary *dict, const ParameterVector *functionParam);
static bool generateCodeToFile(const std::string &outDir, const std::string &filename, const std::string &extension, const std::string &generatedCode);

bool CodeGeneratorCTemplate::generateCode(const std::string& outDir, const std::string &headerToMock, const ElementToStubVector& elem) const
{
  ctemplate::StringToTemplateCache("programTemplate", templateText, ctemplate::DO_NOT_STRIP);
  ctemplate::StringToTemplateCache("headerTemplate", headerFileTemplate, ctemplate::DO_NOT_STRIP);

  ctemplate::TemplateDictionary dict("generateCode");
  ctemplate::TemplateDictionary headerDict("headerCode");

  fillInTemplateVariables(&dict, headerToMock, elem);
  fillInTemplateVariables(&headerDict, headerToMock, elem);

  std::string generatedCode;
  ctemplate::ExpandTemplate("programTemplate", ctemplate::DO_NOT_STRIP, &dict, &generatedCode);
  if (!generateCodeToFile(outDir, headerToMock, "cpp", generatedCode))
  {
    return false;
  }

  generatedCode.clear();
  ctemplate::ExpandTemplate("headerTemplate", ctemplate::DO_NOT_STRIP, &headerDict, &generatedCode);
  if (!generateCodeToFile(outDir, headerToMock, "h", generatedCode))
  {
    return false;
  }

  return true;
}

static void fillInTemplateVariables(ctemplate::TemplateDictionary *rootDictionnary, const std::string &mockedHeader, const ElementToStubVector &fList)
{
  rootDictionnary->SetValue(MOCKED_HEADER_FILENAME, mockedHeader);
  std::string fileNameWithoutExtUpper = mockedHeader.substr(0, mockedHeader.find_last_of("."));
  std::transform(fileNameWithoutExtUpper.begin(), fileNameWithoutExtUpper.end(), fileNameWithoutExtUpper.begin(), ::toupper);
  rootDictionnary->SetValue(MOCKED_FILE_NAME_WITHOUT_EXT_UPPER, fileNameWithoutExtUpper);
  for (ElementToStubVector::const_iterator it = fList.begin(); it != fList.end(); ++it)
  {
    const ElementToStub *f = *it;
    switch (*f->getStubType())
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
    //This specific section to show the comma ',' conditionaly for the expect and return function generation
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
  outFilename.append("/stub_");
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
