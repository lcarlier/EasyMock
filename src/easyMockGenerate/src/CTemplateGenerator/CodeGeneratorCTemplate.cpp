#include <cstdio>
#include <cstdlib>
#include <ctemplate/template.h>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cstring>
#include "CodeGeneratorCTemplate.h"
#include <boost/filesystem.hpp>

#include <sys/stat.h>
#include <fcntl.h>

#include "TypeItf.h"

#define TEMPLATE_VAR(VAR_NAME) "{{" VAR_NAME "}}"
#define TEMPLATE_BEG_SECTION(SECTION_NAME) "{{#" SECTION_NAME "}}"
#define TEMPLATE_END_SECTION(SECTION_NAME) "{{/" SECTION_NAME "}}"

#define MOCK_FRAMEWORK_NAME "easyMock"
#define MOCK_FRAMEWORK_NAME_UPPER "EASYMOCK"
#define MOCK_OUT_PREFIX "out_"

#define CARRIAGE_RETURN "\n"

#define MOCKED_HEADER_FILENAME "MOCKED_HEADER_FILENAME"
#define MOCKED_FILE_NAME_WITHOUT_EXT_UPPER "MOCKED_FILE_NAME_WITHOUT_EXT_UPPER"
#define FUNCTION_SECTION "FUNCTION_SECTION"
#define FUNCTION_PARAM_SECTION "FUNCTION_PARAM_SECTION"
#define FUNCTION_PARAM_PTR_SECTION "FUNCTION_PARAM_PTR_SECTION"
#define STRUCT_COMPARE_SECTION "STRUCT_COMPARE_SECTION"
#define STRUCT_COMPARE_PRE_IF_SECTION "STRUCT_COMPARE_PRE_IF_SECTION"
#define STRUCT_COMPARE_PRE_IF_SECTION_VAR_NAME "STRUCT_COMPARE_PRE_IF_SECTION_VAR_NAME"
#define STRUCT_COMPARE_PRE_IF_SECTION_FIELD_NAME "STRUCT_COMPARE_PRE_IF_SECTION_FIELD_NAME"
#define STRUCT_NAME "STRUCT_NAME"
#define STRUCT_COMPARE_PARAM_SECTION "STRUCT_COMPARE_PARAM_SECTION"
#define COMPARE_CONDITION "COMPARE_CONDITION"
#define STRUCT_COMPARE_ERROR "STRUCT_COMPARE_ERROR"
#define STRUCT_COMPARE_FIELD "STRUCT_COMPARE_FIELD"
#define STRUCT_COMPARE_TYPE "STRUCT_COMPARE_TYPE"
#define STRUCT_COMPARE_PRINTF_FORMAT "STRUCT_COMPARE_PRINTF_FORMAT"
#define FUNCTION_PARAM_SECTION_SEPARATOR FUNCTION_PARAM_SECTION "_separator"
#define FUNCTION_PARAM_PTR_SECTION_SEPARATOR FUNCTION_PARAM_PTR_SECTION "_separator"
#define FUNCTION_PARAM_TYPE "TYPEDEF_PARAM_RETURN_VALUE"
#define FUNCTION_PARAM_NAME "TYPEDEF_PARAM_NAME"
#define FUNCTION_RETURN_VALUE_PARAM_SECTION "FUNCTION_RETURN_VALUE_PARAM_SECTION"
#define FUNCTION_RETURN_VALUE_PARAM "FUNCTION_RETURN_VALUE_PARAM"
#define FUNCTION_RETURN_VALUE "FUNCTION_RETURN_VALUE"
#define FUNCTION_NAME "FUNCTION_NAME"
#define FUNCTION_NAME_UPPER "FUNCTION_NAME_UPPER"
#define FUNCTION_MATCHER_LIST_SECTION "FUNCTION_MATCHER_LIST_SECTION"
#define FUNCTION_PARAM_LIST_SECTION "FUNCTION_PARAM_LIST_SECTION"
#define FUNCTION_PARAM_PTR_LIST_SECTION "FUNCTION_PARAM_PTR_LIST_SECTION"

#define VOID_FUNCTION_RETURN_VALUE "void"

#define IF_RETURN_VALUE(STR_TO_PRINT) \
  TEMPLATE_BEG_SECTION(FUNCTION_RETURN_VALUE_PARAM_SECTION) \
  STR_TO_PRINT \
  TEMPLATE_END_SECTION(FUNCTION_RETURN_VALUE_PARAM_SECTION)

#define IF_PARAM_LIST(SECTION, STR_TO_PRINT) \
  TEMPLATE_BEG_SECTION(SECTION) \
  STR_TO_PRINT \
  TEMPLATE_END_SECTION(SECTION)

#define PARAMETER_NAME(PREFIX) PREFIX TEMPLATE_VAR(FUNCTION_PARAM_NAME)
#define PARAMETER_TYPE TEMPLATE_VAR(FUNCTION_PARAM_TYPE)
#define FUNCTION_RETURN_VALUE_TYPE TEMPLATE_VAR(FUNCTION_RETURN_VALUE)

#define DECLARE_PARAMETER(PREFIX) \
PARAMETER_TYPE " " PARAMETER_NAME(PREFIX)

#define FUNCTION_PARAM_LIST(SECTION, PREFIX) \
  TEMPLATE_BEG_SECTION(SECTION) \
    DECLARE_PARAMETER(PREFIX) \
    TEMPLATE_BEG_SECTION(SECTION ## _SEPARATOR) \
      ", " \
    TEMPLATE_END_SECTION(SECTION ## _SEPARATOR) \
  TEMPLATE_END_SECTION(SECTION)

#define FUNCTION_PARAM_CALL(SECTION, PREFIX) \
  TEMPLATE_BEG_SECTION(SECTION) \
    PARAMETER_NAME(PREFIX) \
    TEMPLATE_BEG_SECTION(SECTION ## _SEPARATOR) \
      ", " \
    TEMPLATE_END_SECTION(SECTION ## _SEPARATOR) \
  TEMPLATE_END_SECTION(SECTION)

#define FUNCTION_HARDCODED_PARAM_CALL(SECTION, VALUE)\
  TEMPLATE_BEG_SECTION(SECTION) \
    VALUE \
    TEMPLATE_BEG_SECTION(SECTION ## _SEPARATOR) \
      ", " \
    TEMPLATE_END_SECTION(SECTION ## _SEPARATOR) \
  TEMPLATE_END_SECTION(SECTION)

#define FUNCTION_PARAM_MATCH_VAR \
"easyMock_match_" PARAMETER_NAME("")

#define FUNCTION_MATCHER_LIST \
  TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION) \
    "EasyMock_Matcher " FUNCTION_PARAM_MATCH_VAR \
    TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION_SEPARATOR)\
      ", " \
    TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION_SEPARATOR) \
  TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)

#define FUNCTION_MATCHER_CALL \
  TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION) \
    FUNCTION_PARAM_MATCH_VAR \
    TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION_SEPARATOR)\
      ", " \
    TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION_SEPARATOR) \
  TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)

#define FUNCTION_EXPECT_AND_RETURN_NAME \
TEMPLATE_VAR(FUNCTION_NAME) "_ExpectAndReturn("

#define FUNCTION_EXPECT_RETURN_AND_OUTPUT_PARAM \
FUNCTION_PARAM_LIST(FUNCTION_PARAM_SECTION, "") IF_RETURN_VALUE(IF_PARAM_LIST(FUNCTION_PARAM_LIST_SECTION, ", ") FUNCTION_RETURN_VALUE_TYPE " to_return") IF_PARAM_LIST(FUNCTION_PARAM_LIST_SECTION, ", ") FUNCTION_MATCHER_LIST

#define FUNCTION_EXPECT_AND_RETURN_SIGNATURE \
"void " FUNCTION_EXPECT_AND_RETURN_NAME FUNCTION_EXPECT_RETURN_AND_OUTPUT_PARAM ")"

#define FUNCTION_EXPECT_RETURN_AND_OUTPUT_NAME \
TEMPLATE_VAR(FUNCTION_NAME) "_ExpectReturnAndOutput"

#define FUNCTION_EXPECT_RETURN_AND_OUTPUT_COMMON_NAME \
TEMPLATE_VAR(FUNCTION_NAME) "_ExpectReturnAndOutput_common"

#define FUNCTION_EXPECT_RETURN_AND_OUTPUT_SIGNATURE_PARAM \
FUNCTION_EXPECT_RETURN_AND_OUTPUT_PARAM IF_PARAM_LIST(FUNCTION_PARAM_PTR_LIST_SECTION, ", ") FUNCTION_PARAM_LIST(FUNCTION_PARAM_PTR_SECTION, MOCK_OUT_PREFIX)

#define FUNCTION_EXPECT_RETURN_AND_OUTPUT_SIGNATURE \
"void " FUNCTION_EXPECT_RETURN_AND_OUTPUT_NAME "(" FUNCTION_EXPECT_RETURN_AND_OUTPUT_SIGNATURE_PARAM ")"

#define FUNCTION_EXPECT_RETURN_AND_OUTPUT_COMMON_SIGNATURE \
"void " FUNCTION_EXPECT_RETURN_AND_OUTPUT_COMMON_NAME "(" FUNCTION_EXPECT_RETURN_AND_OUTPUT_SIGNATURE_PARAM ")"

#define FUNCTION_EXPECT_RETURN_COMMON_CALL_PARAM \
FUNCTION_PARAM_CALL(FUNCTION_PARAM_SECTION, "") IF_RETURN_VALUE(IF_PARAM_LIST(FUNCTION_PARAM_LIST_SECTION, ", ") "to_return") IF_PARAM_LIST(FUNCTION_PARAM_LIST_SECTION, ", ") FUNCTION_MATCHER_CALL

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

#define FUNCTION_MOCK_DATA_CUR_MATCH_VAR \
TEMPLATE_VAR(FUNCTION_NAME) "_match_" PARAMETER_NAME("")

#define CURRENT_DATA_CALL "currentDataCall"
#define CURRENT_DATA_CALL_MEMBER(member) CURRENT_DATA_CALL "." member
#define CURRENT_DATA_CALL_PTR(member) "*" CURRENT_DATA_CALL "." member

#define MOCKED_DATA "mockedData"
#define MOCKED_DATA_MEMBER(member) MOCKED_DATA "." member

#define TEMPLATE_FUNCTION_TO_BE_MOCKED FUNCTION_RETURN_VALUE_TYPE " " TEMPLATE_VAR(FUNCTION_NAME) "(" FUNCTION_PARAM_LIST(FUNCTION_PARAM_SECTION, "") ")"
#define MOCKED_FUN_CLASS(F_NAME) "mocked_" F_NAME
#define TEMPLATE_MOCKED_FUN_CLASS MOCKED_FUN_CLASS(TEMPLATE_VAR(FUNCTION_NAME))

#define STRUCT_COMPARE_SECTION_STRUCT_NAME_VAR TEMPLATE_VAR(STRUCT_NAME)
#define STRUCT_COMPARE_PARAM_SECTION_COMPARE_CONDITION_VAR TEMPLATE_VAR(COMPARE_CONDITION)
#define STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR TEMPLATE_VAR(STRUCT_COMPARE_FIELD)
#define STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_PRINTF_FORMAT_VAR TEMPLATE_VAR(STRUCT_COMPARE_PRINTF_FORMAT)
#define STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_STRUCT_TYPE_VAR TEMPLATE_VAR(STRUCT_COMPARE_TYPE)

#define STRUCT_COMPARE_FUNCTION_SIGNATURE \
"int cmp_struct_" STRUCT_COMPARE_SECTION_STRUCT_NAME_VAR "( void *currentCall_ptr, void *expectedCall_ptr, const char *paramName, char *errorMessage )"

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
        "#include <cstring>" CARRIAGE_RETURN
        CARRIAGE_RETURN
        FUNCTION_RESET_ALL_MOCK_SIGNATURE ";" CARRIAGE_RETURN
        FUNCTION_VERIFY_ALL_MOCK_SIGNATURE ";" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(STRUCT_COMPARE_SECTION)
        "extern \"C\" " STRUCT_COMPARE_FUNCTION_SIGNATURE CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    struct " STRUCT_COMPARE_SECTION_STRUCT_NAME_VAR " *currentCall_val = static_cast<struct " STRUCT_COMPARE_SECTION_STRUCT_NAME_VAR " *>(currentCall_ptr);" CARRIAGE_RETURN
        "    struct " STRUCT_COMPARE_SECTION_STRUCT_NAME_VAR " *expectedCall_val = static_cast<struct " STRUCT_COMPARE_SECTION_STRUCT_NAME_VAR " *>(expectedCall_ptr);" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(STRUCT_COMPARE_PARAM_SECTION)
        TEMPLATE_BEG_SECTION(STRUCT_COMPARE_PRE_IF_SECTION)
        "    std::string " TEMPLATE_VAR(STRUCT_COMPARE_PRE_IF_SECTION_VAR_NAME) "(paramName);" CARRIAGE_RETURN
        "    " TEMPLATE_VAR(STRUCT_COMPARE_PRE_IF_SECTION_VAR_NAME) ".append(\"." TEMPLATE_VAR(STRUCT_COMPARE_PRE_IF_SECTION_FIELD_NAME) "\");" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(STRUCT_COMPARE_PRE_IF_SECTION)
        "    if(" STRUCT_COMPARE_PARAM_SECTION_COMPARE_CONDITION_VAR ")" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(STRUCT_COMPARE_ERROR)
        "        snprintf(errorMessage, 256 , \"Parameter '%s' which is a struct of type '" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_STRUCT_TYPE_VAR "' has field '" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR "' with value '%" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_PRINTF_FORMAT_VAR "', was expecting '%" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_PRINTF_FORMAT_VAR "'\", paramName, currentCall_val->" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR ", expectedCall_val->" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR ");" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(STRUCT_COMPARE_ERROR)
        "        return -1;" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(STRUCT_COMPARE_PARAM_SECTION)
        "    return 0;" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_END_SECTION(STRUCT_COMPARE_SECTION)
        TEMPLATE_BEG_SECTION(FUNCTION_SECTION)
        GENERATE_COMMENT CARRIAGE_RETURN
        "typedef struct {" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION)
        "    " DECLARE_PARAMETER("") ";" CARRIAGE_RETURN
        "    EasyMock_Matcher " FUNCTION_MOCK_DATA_CUR_MATCH_VAR ";" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)
        IF_RETURN_VALUE("    " FUNCTION_RETURN_VALUE_TYPE " " FUNCTION_MOCK_DATA_RETURN_VALUE_VARIABLE ";" CARRIAGE_RETURN)
        TEMPLATE_BEG_SECTION(FUNCTION_PARAM_PTR_SECTION)
        "    " DECLARE_PARAMETER(MOCK_OUT_PREFIX) ";" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_PARAM_PTR_SECTION)
        "} " FUNCTION_MOCK_DATA_TYPE";" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "static " FUNCTION_EXPECT_RETURN_AND_OUTPUT_COMMON_SIGNATURE ";" CARRIAGE_RETURN
        "static MockedFunction<" FUNCTION_MOCK_DATA_TYPE "> " TEMPLATE_MOCKED_FUN_CLASS "(\"" TEMPLATE_FUNCTION_TO_BE_MOCKED "\");" CARRIAGE_RETURN
        IF_RETURN_VALUE("static " FUNCTION_RETURN_VALUE_TYPE " dummyRes;" CARRIAGE_RETURN)
        CARRIAGE_RETURN
        "extern \"C\" " TEMPLATE_FUNCTION_TO_BE_MOCKED CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    bool printCallStack = easyMock_printCallStack();" CARRIAGE_RETURN
        "    bool checkFifoCall = easyMock_checkFifoCall();" CARRIAGE_RETURN
        CARRIAGE_RETURN
        IF_RETURN_VALUE
        (
            "    " FUNCTION_RETURN_VALUE_TYPE " default_res;" CARRIAGE_RETURN
            "    std::memcpy(&default_res, &dummyRes, sizeof(default_res));" CARRIAGE_RETURN
            CARRIAGE_RETURN
        )
        "    if(!" TEMPLATE_MOCKED_FUN_CLASS ".addActualCall())" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        easyMock_addError(printCallStack, \"Error : unexpected call of '%s'." IF_RETURN_VALUE(" " TEMPLATE_VAR(FUNCTION_NAME) " is returning a random value.") "\", " TEMPLATE_MOCKED_FUN_CLASS ".getName().c_str());" CARRIAGE_RETURN
        "        return" IF_RETURN_VALUE(" default_res") ";" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "    " FUNCTION_MOCK_DATA_TYPE " " CURRENT_DATA_CALL ";" CARRIAGE_RETURN
        "    if (!" TEMPLATE_MOCKED_FUN_CLASS ".getCurrentCallParam(" CURRENT_DATA_CALL "))" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        easyMock_addError(printCallStack, \"BUG IN EASYMOCK: CONTACT DEVELOPPER TO FIX THIS\");" CARRIAGE_RETURN
        "        return" IF_RETURN_VALUE(" default_res") ";" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION)
        "    if(" CURRENT_DATA_CALL_MEMBER(FUNCTION_MOCK_DATA_CUR_MATCH_VAR) " != NULL)" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        char errorMessage[EASYMOCK_MAX_CMP_ERR] = {0};" CARRIAGE_RETURN
        "        void *curCallVal = (void *) &" PARAMETER_NAME("") ";" CARRIAGE_RETURN
        "        void *expectedCallVal = (void *) &" CURRENT_DATA_CALL_MEMBER(PARAMETER_NAME("")) ";" CARRIAGE_RETURN
        "        EasyMock_Matcher matcher = " CURRENT_DATA_CALL_MEMBER(FUNCTION_MOCK_DATA_CUR_MATCH_VAR) ";" CARRIAGE_RETURN
        "        int error = matcher(curCallVal, expectedCallVal, \"" PARAMETER_NAME("") "\", errorMessage);" CARRIAGE_RETURN
        "        if(error)" CARRIAGE_RETURN
        "        {" CARRIAGE_RETURN
        "            easyMock_addError(printCallStack, \"Error : at call %d of '%s': %s\", " TEMPLATE_MOCKED_FUN_CLASS ".getNbActualCall(), " TEMPLATE_MOCKED_FUN_CLASS ".getName().c_str(), errorMessage);" CARRIAGE_RETURN
        "        }" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)
        IF_RETURN_VALUE("    default_res = currentDataCall." FUNCTION_MOCK_DATA_RETURN_VALUE_VARIABLE ";" CARRIAGE_RETURN)
        CARRIAGE_RETURN
        "    const std::string currentCall = easyMock_popCurrentCall();" CARRIAGE_RETURN
        "    if(checkFifoCall)" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        const std::string &curFuncCall = " TEMPLATE_MOCKED_FUN_CLASS ".getName();" CARRIAGE_RETURN
        "        if(currentCall.compare(curFuncCall) != 0)" CARRIAGE_RETURN
        "        {" CARRIAGE_RETURN
        "            easyMock_addError(printCallStack, \"Error : got call to '%s',  but was expecting call to '%s'\", " TEMPLATE_MOCKED_FUN_CLASS ".getName().c_str(), currentCall.c_str());" CARRIAGE_RETURN
        "            return" IF_RETURN_VALUE(" default_res") ";" CARRIAGE_RETURN
        "        }" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_PARAM_PTR_SECTION)
        "    if(" CURRENT_DATA_CALL_MEMBER(PARAMETER_NAME(MOCK_OUT_PREFIX)) ")" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        "        std::memcpy(" PARAMETER_NAME("") ", " CURRENT_DATA_CALL_MEMBER(PARAMETER_NAME(MOCK_OUT_PREFIX)) ", sizeof(*" PARAMETER_NAME("") "));" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_PARAM_PTR_SECTION)
        IF_RETURN_VALUE(CARRIAGE_RETURN "    return default_res;" CARRIAGE_RETURN)
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "extern \"C\" " FUNCTION_EXPECT_AND_RETURN_SIGNATURE CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    " FUNCTION_EXPECT_RETURN_AND_OUTPUT_COMMON_NAME "(" FUNCTION_EXPECT_RETURN_COMMON_CALL_PARAM IF_PARAM_LIST(FUNCTION_PARAM_PTR_LIST_SECTION, ", ") FUNCTION_HARDCODED_PARAM_CALL(FUNCTION_PARAM_PTR_SECTION, "nullptr") ");" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        IF_PARAM_LIST(FUNCTION_PARAM_PTR_LIST_SECTION,
             "    extern\"C\" " FUNCTION_EXPECT_RETURN_AND_OUTPUT_SIGNATURE CARRIAGE_RETURN
             "    {" CARRIAGE_RETURN
             "        " FUNCTION_EXPECT_RETURN_AND_OUTPUT_COMMON_NAME "(" FUNCTION_EXPECT_RETURN_COMMON_CALL_PARAM IF_PARAM_LIST(FUNCTION_PARAM_PTR_LIST_SECTION, ", ") FUNCTION_PARAM_CALL(FUNCTION_PARAM_PTR_SECTION, MOCK_OUT_PREFIX) ");"
             "    }" CARRIAGE_RETURN
        )
        "static " FUNCTION_EXPECT_RETURN_AND_OUTPUT_COMMON_SIGNATURE CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    " FUNCTION_MOCK_DATA_TYPE " " MOCKED_DATA ";" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION)
        "    " MOCKED_DATA_MEMBER(PARAMETER_NAME("")) " = " PARAMETER_NAME("") ";" CARRIAGE_RETURN
        "    " MOCKED_DATA_MEMBER(FUNCTION_MOCK_DATA_CUR_MATCH_VAR) " = " FUNCTION_PARAM_MATCH_VAR ";" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)
        TEMPLATE_BEG_SECTION(FUNCTION_PARAM_PTR_SECTION)
        "    " MOCKED_DATA_MEMBER(PARAMETER_NAME(MOCK_OUT_PREFIX)) " = " PARAMETER_NAME(MOCK_OUT_PREFIX) ";" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_PARAM_PTR_SECTION)
        IF_RETURN_VALUE("    " MOCKED_DATA_MEMBER(FUNCTION_MOCK_DATA_RETURN_VALUE_VARIABLE) " = to_return;" CARRIAGE_RETURN CARRIAGE_RETURN)
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
        TEMPLATE_BEG_SECTION(STRUCT_COMPARE_SECTION)
        STRUCT_COMPARE_FUNCTION_SIGNATURE ";" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(STRUCT_COMPARE_SECTION)
        TEMPLATE_BEG_SECTION(FUNCTION_SECTION)
        "//------------------- GENERATING '" TEMPLATE_FUNCTION_TO_BE_MOCKED "' -------------------" CARRIAGE_RETURN
        FUNCTION_EXPECT_AND_RETURN_SIGNATURE ";" CARRIAGE_RETURN
        IF_PARAM_LIST(FUNCTION_PARAM_PTR_LIST_SECTION, FUNCTION_EXPECT_RETURN_AND_OUTPUT_SIGNATURE ";" CARRIAGE_RETURN)
        "//----------------- END GENERATION '" TEMPLATE_FUNCTION_TO_BE_MOCKED "' -----------------" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_SECTION)
        "#ifdef __cplusplus" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        "#endif" CARRIAGE_RETURN
        "#endif" CARRIAGE_RETURN;

static void fillInTemplateVariables(ctemplate::TemplateDictionary *dict, const std::string &mockedHeader, const ElementToMock::Vector &fList);
static void generateFunctionSection(ctemplate::TemplateDictionary *rootDictionnary, const ElementToMock *f);
static void generateFunctionParamSection(ctemplate::TemplateDictionary *rootDictionnary, ctemplate::TemplateDictionary *dict, const Parameter::Vector *functionParam);
static void generateStructCompareSection(ctemplate::TemplateDictionary *rootDictionnary, const TypeItf *structType);
static bool generateCodeToFile(const std::string &outDir, const std::string &filename, const std::string &extension, const std::string &generatedCode);
static std::string getDeclaratorString(const Declarator* decl);

bool CodeGeneratorCTemplate::generateCode(const std::string& outDir, const std::string &fullPathToHeaderToMock, const ElementToMock::Vector& elem) const
{
  ctemplate::TemplateDictionary dict("generateCode");

  std::string filenameToMock = boost::filesystem::path(fullPathToHeaderToMock).filename().string();
  fillInTemplateVariables(&dict, filenameToMock, elem);

  ctemplate::StringToTemplateCache("programTemplate", templateText, ctemplate::DO_NOT_STRIP);
  ctemplate::StringToTemplateCache("headerTemplate", headerFileTemplate, ctemplate::DO_NOT_STRIP);

  std::string generatedCode;
  ctemplate::ExpandTemplate("programTemplate", ctemplate::DO_NOT_STRIP, &dict, &generatedCode);
  if (!generateCodeToFile(outDir, filenameToMock, "cpp", generatedCode))
  {
    return false;
  }

  generatedCode.clear();
  ctemplate::ExpandTemplate("headerTemplate", ctemplate::DO_NOT_STRIP, &dict, &generatedCode);
  if (!generateCodeToFile(outDir, filenameToMock, "h", generatedCode))
  {
    return false;
  }

  return true;
}

static void fillInTemplateVariables(ctemplate::TemplateDictionary *rootDictionnary, const std::string &mockedHeader, const ElementToMock::Vector &fList)
{
  rootDictionnary->SetValue(MOCKED_HEADER_FILENAME, mockedHeader);
  std::string fileNameWithoutExtUpper = mockedHeader.substr(0, mockedHeader.find_last_of("."));
  std::transform(fileNameWithoutExtUpper.begin(), fileNameWithoutExtUpper.end(), fileNameWithoutExtUpper.begin(), ::toupper);
  rootDictionnary->SetValue(MOCKED_FILE_NAME_WITHOUT_EXT_UPPER, fileNameWithoutExtUpper);
  for (ElementToMock::Vector::const_iterator it = fList.begin(); it != fList.end(); ++it)
  {
    const ElementToMock *f = *it;
    switch (f->getMockType())
    {
      case ETS_function:
      {
        generateFunctionSection(rootDictionnary, f);
        break;
      }
      default:
        break;
    }
  }
}

static void generateFunctionSection(ctemplate::TemplateDictionary *rootDictionnary, const ElementToMock *f)
{
  ctemplate::TemplateDictionary *functionSectionDict = rootDictionnary->AddSectionDictionary(FUNCTION_SECTION);
  functionSectionDict->SetValue(FUNCTION_NAME, *f->getName());
  std::string upperString(*f->getName());
  std::transform(upperString.begin(), upperString.end(), upperString.begin(), ::toupper);
  functionSectionDict->SetValue(FUNCTION_NAME_UPPER, upperString);

  const ReturnValue *returnValue = f->getReturnType();
  const TypeItf* rvType = returnValue->getType();
  std::string returnTypeStr = getDeclaratorString(returnValue);
  functionSectionDict->SetValue(FUNCTION_RETURN_VALUE, returnTypeStr);

  bool isRvVoid = rvType->isCType() && rvType->getCType() == CTYPE_VOID && !returnValue->isPointer();
  if (!isRvVoid)
  {
    ctemplate::TemplateDictionary *returnValParamDict = functionSectionDict->AddSectionDictionary(FUNCTION_RETURN_VALUE_PARAM_SECTION);
    returnValParamDict->SetValue(FUNCTION_RETURN_VALUE, returnTypeStr);
  }
  generateFunctionParamSection(rootDictionnary, functionSectionDict, f->getFunctionsParameters());
}

static void generateFunctionParamSection(ctemplate::TemplateDictionary *rootDictionnary, ctemplate::TemplateDictionary *functionSectionDict, const Parameter::Vector *functionParam)
{
  bool ptrSectionAdded = false;
  if (functionParam->size() > 0)
  {
    //This specific section to show the comma ',' conditionally for the expect and return function generation
    functionSectionDict->AddSectionDictionary(FUNCTION_PARAM_LIST_SECTION);
  }
  for (Parameter::Vector::const_iterator it = functionParam->begin(); it != functionParam->end(); ++it)
  {
    ctemplate::TemplateDictionary* newTypedefParamSection = functionSectionDict->AddSectionDictionary(FUNCTION_PARAM_SECTION);
    const Parameter *fParam = *it;
    std::string argType = getDeclaratorString(fParam);
    if(fParam->getType()->isStruct())
    {
      generateStructCompareSection(rootDictionnary, fParam->getType());
    }
    newTypedefParamSection->SetValue(FUNCTION_PARAM_TYPE, argType);
    newTypedefParamSection->SetValue(FUNCTION_PARAM_NAME, fParam->getName());
    //It doesn't make sense to generate an output parameter for void pointer. The mock doesn't know the size of the data to copy into the pointer
    if(fParam->isPointer() && fParam->getType()->getCType() != CTYPE_VOID)
    {
      if(!ptrSectionAdded)
      {
        functionSectionDict->AddSectionDictionary(FUNCTION_PARAM_PTR_LIST_SECTION);
        ptrSectionAdded = true;
      }
      ctemplate::TemplateDictionary* newPtrParamSection = functionSectionDict->AddSectionDictionary(FUNCTION_PARAM_PTR_SECTION);
      newPtrParamSection->SetValue(FUNCTION_PARAM_TYPE, argType);
      newPtrParamSection->SetValue(FUNCTION_PARAM_NAME, fParam->getName());
    }
  }
}

/*
 * e.g
extern "C" int cmp_struct_s ( void *currentCall_ptr, void *expectedCall_ptr, const char *paramName, char *errorMessage ) {
  struct s currentCall_val = *(( struct s *)currentCall_ptr);
  struct s expectedCall_val = *(( struct s *)expectedCall_ptr);
  if(currentCall_val.f1 != expectedCall_val.f1) {
    snprintf(errorMessage, 256 , "Parameter '%s' has field f1 with value '" "%c" "', was expecting '" "%c" "'", paramName, currentCall_val.f1, expectedCall_val.f1);
    return -1;
  }
  if(currentCall_val.f2 != expectedCall_val.f2) {
    snprintf(errorMessage, 256 , "Parameter '%s' has field f2 with value '" "%c" "', was expecting '" "%c" "'", paramName, currentCall_val.f1, expectedCall_val.f1);
    return -1;
  }
  if(cmp_struct_s2 (&currentCall_val.f3, expectedCall_val.f3, "f3", errorMessage) != 0)
  {
    return -1;
  }
  return 0;
}
 * TEMPLATED VERSION
{{BEGIN_STRUCT_COMPARE_SECTION}}
extern "C" int cmp_struct_{{STRUCT_NAME}} ( void *currentCall_ptr, void *expectedCall_ptr, const char *paramName, char *errorMessage ) {
  struct {{STRUCT_NAME}} currentCall_val = *(( struct {{STRUCT_NAME}} *)currentCall_ptr);
  struct {{STRUCT_NAME}} expectedCall_val = *(( struct {{STRUCT_NAME}} *)expectedCall_ptr);
  {{BEGIN_STRUCT_COMPARE_PARAM_SECTION}}
  if({{COMPARE_CONDITION}}) {
    {{BEGIN_STRUCT_COMPARE_ERROR}}
    snprintf(errorMessage, 256 , "Parameter '%s' which is a struct of type {{STRUCT_COMPARE_TYPE}} has field {{STRUCT_COMPARE_FIELD}} with value '" "%{{STRUCT_COMPARE_PRINTF_FORMAT}}" "', was expecting '" "%{{STRUCT_COMPARE_PRINTF_FORMAT}}" "'", paramName, currentCall_val.{{STRUCT_COMPARE_FIELD}}, expectedCall_val.{{STRUCT_COMPARE_FIELD}});
    {{END_STRUCT_COMPARE_ERROR}}
    return -1;
  }
  {{END_STRUCT_COMPARE_PARAM_SECTION}}
  return 0;
}
{{END_STRUCT_COMPARE_SECTION}}
 */
static void generateStructCompareSection(ctemplate::TemplateDictionary *rootDictionnary, const TypeItf *p_structType)
{
  ctemplate::TemplateDictionary *compareDict = rootDictionnary->AddSectionDictionary(STRUCT_COMPARE_SECTION);
  compareDict->SetValue(STRUCT_NAME, p_structType->getName());
  const StructField::Vector *vectField = p_structType->getContainedFields();
  for (StructField::Vector::const_iterator it = vectField->begin(); it != vectField->end(); ++it)
  {
    std::string condition;
    const StructField *curField = *it;
    ctemplate::TemplateDictionary *paramSectDict = compareDict->AddSectionDictionary(STRUCT_COMPARE_PARAM_SECTION);
    const TypeItf *curType = curField->getType();
    if(curType->isStruct())
    {
      if(!curField->isRecursiveTypeField())
      {
        ctemplate::TemplateDictionary *ifPreSectionDict = paramSectDict->AddSectionDictionary(STRUCT_COMPARE_PRE_IF_SECTION);
        std::string preFieldVarName(curField->getName());
        preFieldVarName.append("_parameter");
        ifPreSectionDict->SetValue(STRUCT_COMPARE_PRE_IF_SECTION_VAR_NAME, preFieldVarName.c_str());
        ifPreSectionDict->SetValue(STRUCT_COMPARE_PRE_IF_SECTION_FIELD_NAME, curField->getName());
        condition.append("cmp_struct_");
        condition.append(curType->getName());
        condition.append("(&currentCall_val->");
        condition.append(curField->getName());
        condition.append(", ");
        condition.append("&expectedCall_val->");
        condition.append(curField->getName());
        condition.append(", ");
        condition.append(preFieldVarName.c_str());
        condition.append(".c_str(), errorMessage)");
        generateStructCompareSection(rootDictionnary, curType);
      }
      else
      {
        condition.append("currentCall_val !=  expectedCall_val");
      }
    } else if (curType->isCType()) {
      condition.append("currentCall_val->");
      condition.append(curField->getName());
      condition.append(" != expectedCall_val->");
      condition.append(curField->getName());
      ctemplate::TemplateDictionary *errorDict = paramSectDict->AddSectionDictionary(STRUCT_COMPARE_ERROR);
      errorDict->SetValue(STRUCT_COMPARE_FIELD, curField->getName());
      errorDict->SetValue(STRUCT_COMPARE_TYPE, p_structType->getName());
      if(!curField->isPointer())
      {
        errorDict->SetValue(STRUCT_COMPARE_PRINTF_FORMAT, easyMock_printfFormat[curType->getCType()]);
      }
      else
      {
        errorDict->SetValue(STRUCT_COMPARE_PRINTF_FORMAT, "p");
      }
    } else {
      std::fprintf(stderr, "Type %s unexpected here. Contact owner for bug fixing\n\r", curType->getName().c_str());
      assert(false);
    }
    paramSectDict->SetValue(COMPARE_CONDITION, condition);
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

static std::string getDeclaratorString(const Declarator* decl)
{
  const TypeItf* rvType = decl->getType();
  std::string returnTypeStr;
  if (rvType->isStruct())
  {
    returnTypeStr.append("struct ");
  }
  returnTypeStr.append(rvType->getName());
  if(decl->isPointer())
  {
    returnTypeStr.push_back('*');
  }
  return returnTypeStr;
}
