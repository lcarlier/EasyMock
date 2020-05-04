#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cstring>
#include "CodeGeneratorCTemplate.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <unordered_set>

#include <sys/stat.h>
#include <fcntl.h>

#include "TypeItf.h"
#include "ComposableType.h"
#include "Pointer.h"
#include "Function.h"

#define TEMPLATE_VAR(VAR_NAME) "{{" VAR_NAME "}}"
#define TEMPLATE_BEG_SECTION(SECTION_NAME) "{{#" SECTION_NAME "}}"
#define TEMPLATE_END_SECTION(SECTION_NAME) "{{/" SECTION_NAME "}}"
#define TEMPLATE_INCL_SECTION(SECTION_NAME) "{{>" SECTION_NAME "}}"

#define MOCK_FRAMEWORK_NAME "easyMock"
#define MOCK_FRAMEWORK_NAME_UPPER "EASYMOCK"
#define MOCK_OUT_PREFIX "out_"

#define CARRIAGE_RETURN "\n"

#define MOCKED_HEADER_FILENAME "MOCKED_HEADER_FILENAME"
#define MOCKED_FILE_NAME_WITHOUT_EXT_UPPER "MOCKED_FILE_NAME_WITHOUT_EXT_UPPER"
#define FUNCTION_SECTION "FUNCTION_SECTION"
#define FUNCTION_PARAM_SECTION "FUNCTION_PARAM_SECTION"
#define FUNCTION_PARAM_PTR_SECTION "FUNCTION_PARAM_PTR_SECTION"
#define COMPOSED_TYPE_COMPARE_SECTION "STRUCT_COMPARE_SECTION"
#define STRUCT_COMPARE_PRE_IF_SECTION "STRUCT_COMPARE_PRE_IF_SECTION"
#define STRUCT_COMPARE_PRE_IF_SECTION_VAR_NAME "STRUCT_COMPARE_PRE_IF_SECTION_VAR_NAME"
#define STRUCT_COMPARE_PRE_IF_SECTION_FIELD_NAME "STRUCT_COMPARE_PRE_IF_SECTION_FIELD_NAME"
#define COMPOSED_TYPED_DECL_STRING "COMPOSED_TYPED_DECL_STRING"
#define COMPOSED_TYPED_UNIQUE_NAME "COMPOSED_TYPED_UNIQUE_NAME"
#define STRUCT_COMPARE_PARAM_SECTION "STRUCT_COMPARE_PARAM_SECTION"
#define STRUCT_COMPARE_ARRAY_SECTION "STRUCT_COMPARE_ARRAY_SECTION"
#define STRUCT_PRINT_IDX_SECTION "STRUCT_PRINT_IDX_SECTION"
#define COMPARE_CONDITION "COMPARE_CONDITION"
#define STRUCT_COMPARE_ERROR "STRUCT_COMPARE_ERROR"
#define STRUCT_COMPARE_FIELD "STRUCT_COMPARE_FIELD"
#define STRUCT_COMPARE_TYPE "STRUCT_COMPARE_TYPE"
#define STRUCT_COMPARE_PRINTF_FORMAT "STRUCT_COMPARE_PRINTF_FORMAT"
#define FUNCTION_PARAM_SECTION_SEPARATOR FUNCTION_PARAM_SECTION "_separator"
#define FUNCTION_PARAM_PTR_SECTION_SEPARATOR FUNCTION_PARAM_PTR_SECTION "_separator"
#define FUNCTION_PARAM_TYPE "TYPEDEF_PARAM_RETURN_VALUE"
#define FUNCTION_PARAM_NON_QUALIFIED_TYPE "FUNCTION_PARAM_NON_QUALIFIED_TYPE"
#define FUNCTION_PARAM_NAME "TYPEDEF_PARAM_NAME"
#define FUNCTION_RETURN_VALUE_PARAM_SECTION "FUNCTION_RETURN_VALUE_PARAM_SECTION"
#define FUNCTION_RETURN_VALUE_PARAM "FUNCTION_RETURN_VALUE_PARAM"
#define FUNCTION_RETURN_VALUE "FUNCTION_RETURN_VALUE"
#define FUNCTION_TO_RETURN_VALUE "FUNCTION_TO_RETURN_VALUE"
#define FUNCTION_NAME "FUNCTION_NAME"
#define FUNCTION_NAME_UPPER "FUNCTION_NAME_UPPER"
#define FUNCTION_MATCHER_LIST_SECTION "FUNCTION_MATCHER_LIST_SECTION"
#define FUNCTION_PARAM_LIST_SECTION "FUNCTION_PARAM_LIST_SECTION"
#define FUNCTION_PARAM_PTR_LIST_SECTION "FUNCTION_PARAM_PTR_LIST_SECTION"
#define NON_TYPED_DEF_COMPOSED_TYPE_SECTION "NON_TYPED_DEF_COMPOSED_TYPE_SECTION"

#define COMPOSED_TYPE_TEMPLATE_VAR "NON_TYPED_DEF_COMPOSED_TYPE_VAR" //struct or union
#define COMPOSED_TYPE_VAR TEMPLATE_VAR(COMPOSED_TYPE_TEMPLATE_VAR)

#define RECURSIVE_ANONYMOUS_TYPE_DECLARATION_SECTION "RECURSIVE_ANONYMOUS_TYPE_DECLARATION_SECTION"
#define RECURSIVE_ANONYMOUS_TYPE_DECLARATION_FIELD_SECTION "RECURSIVE_ANONYMOUS_TYPE_DECLARATION_FIELD_SECTION"
#define RECURSIVE_ANONYMOUS_TYPE_DECLARATION_TYPE_TEMPLATE_VAR "RECURSIVE_ANONYMOUS_TYPE_DECLARATION_TYPE_TEMPLATE_VAR"
#define RECURSIVE_ANONYMOUS_TYPE_DECLARATION_TYPE_VAR TEMPLATE_VAR(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_TYPE_TEMPLATE_VAR)
#define RECURSIVE_ANONYMOUS_TYPE_DECLARATION_NAME_TEMPLATE_VAR "RECURSIVE_ANONYMOUS_TYPE_DECLARATION_NAME_TEMPLATE_VAR"
#define RECURSIVE_ANONYMOUS_TYPE_DECLARATION_NAME_VAR TEMPLATE_VAR(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_NAME_TEMPLATE_VAR)

#define ANONYMOUS_TYPE_DECLARATION_FIELD_SECTION "ANONYMOUS_TYPE_DECLARATION_FIELD_SECTION"
#define ANONYMOUS_TYPE_DECLARATION_FIELD_TYPE_TEMPLATE_VAR "ANONYMOUS_TYPE_DECLARATION_FIELD_TYPE_TEMPLATE_VAR"
#define ANONYMOUS_TYPE_DECLARATION_FIELD_TYPE_VAR TEMPLATE_VAR(ANONYMOUS_TYPE_DECLARATION_FIELD_TYPE_TEMPLATE_VAR)
#define ANONYMOUS_TYPE_DECLARATION_FIELD_NAME_TEMPLATE_VAR "ANONYMOUS_TYPE_DECLARATION_FIELD_NAME_TEMPLATE_VAR"
#define ANONYMOUS_TYPE_DECLARATION_FIELD_NAME_VAR TEMPLATE_VAR(ANONYMOUS_TYPE_DECLARATION_FIELD_NAME_TEMPLATE_VAR)

#define CFILE_TEMPLATE "cfile_template"
#define HFILE_TEMPLATE "hfile_template"
#define RECURSIVE_ANONYMOUS_TYPE_DECLARATION_TEMPLATE_NAME "include_anonymous_decl_template"
#define RECURSIVE_ANONYMOUS_TYPE_DECLARATION_TEMPLATE_FIELD_NAME "include_anonymous_decl_template_field"

#define VARIADIC_SECTION "VARIADIC_SECTION"
#define VARIADIC_VAR "VARIADIC_VAR"
#define VARIADIC_TEMPLATE_VAR TEMPLATE_VAR(VARIADIC_VAR)

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
#define PARAMETER_NON_QUALIFIED_TYPE TEMPLATE_VAR(FUNCTION_PARAM_NON_QUALIFIED_TYPE)
#define FUNCTION_RETURN_VALUE_TYPE TEMPLATE_VAR(FUNCTION_RETURN_VALUE)
#define FUNCTION_TO_RETURN_VALUE_TYPE TEMPLATE_VAR(FUNCTION_TO_RETURN_VALUE)

#define FUNCTION_NON_QUALIFIED_RETURN_VALUE "FUNCTION_NON_QUALIFIED_RETURN_VALUE"
#define FUNCTION_NON_QUALIFIED_RETURN_VALUE_TYPE TEMPLATE_VAR(FUNCTION_NON_QUALIFIED_RETURN_VALUE)

#define PRINT_CMP_ARRAY_IDX \
  IF_PARAM_LIST(STRUCT_PRINT_IDX_SECTION, "at idx == %d")

#define PRINT_CMP_ARRAY_IDX_value \
  IF_PARAM_LIST(STRUCT_PRINT_IDX_SECTION, ", idx")

#define DECLARE_PARAMETER(PREFIX) \
PARAMETER_TYPE " " PARAMETER_NAME(PREFIX)

#define DECLARE_NON_QUALIFIED_PARAMETER(PREFIX) \
PARAMETER_NON_QUALIFIED_TYPE " " PARAMETER_NAME(PREFIX)

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
FUNCTION_PARAM_LIST(FUNCTION_PARAM_SECTION, "") IF_RETURN_VALUE(IF_PARAM_LIST(FUNCTION_PARAM_LIST_SECTION, ", ") FUNCTION_TO_RETURN_VALUE_TYPE " to_return") IF_PARAM_LIST(FUNCTION_PARAM_LIST_SECTION, ", ") FUNCTION_MATCHER_LIST

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

#define TEMPLATE_FUNCTION_TO_BE_MOCKED FUNCTION_RETURN_VALUE_TYPE " " TEMPLATE_VAR(FUNCTION_NAME) "(" FUNCTION_PARAM_LIST(FUNCTION_PARAM_SECTION, "") IF_PARAM_LIST(VARIADIC_SECTION, VARIADIC_TEMPLATE_VAR) ")"
#define MOCKED_FUN_CLASS(F_NAME) "mocked_" F_NAME
#define TEMPLATE_MOCKED_FUN_CLASS MOCKED_FUN_CLASS(TEMPLATE_VAR(FUNCTION_NAME))

#define COMPOSED_TYPED_COMPARE_SECTION_DECL_NAME_VAR TEMPLATE_VAR(COMPOSED_TYPED_DECL_STRING)
#define COMPOSED_TYPED_COMPARE_SECTION_UNIQUE_NAME_VAR TEMPLATE_VAR(COMPOSED_TYPED_UNIQUE_NAME)
#define STRUCT_COMPARE_PARAM_SECTION_COMPARE_CONDITION_VAR TEMPLATE_VAR(COMPARE_CONDITION)
#define STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR TEMPLATE_VAR(STRUCT_COMPARE_FIELD)
#define STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_PRINTF_FORMAT_VAR TEMPLATE_VAR(STRUCT_COMPARE_PRINTF_FORMAT)
#define STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_STRUCT_TYPE_VAR TEMPLATE_VAR(STRUCT_COMPARE_TYPE)

#define COMPOSED_TYPED_COMPARE_FUNCTION_SIGNATURE \
"int cmp_" COMPOSED_TYPED_COMPARE_SECTION_UNIQUE_NAME_VAR "( void *currentCall_ptr, void *expectedCall_ptr, const char *paramName, char *errorMessage )"

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

        TEMPLATE_BEG_SECTION(COMPOSED_TYPE_COMPARE_SECTION)
        "extern \"C\" " COMPOSED_TYPED_COMPARE_FUNCTION_SIGNATURE CARRIAGE_RETURN
        "{" CARRIAGE_RETURN

        "    " TEMPLATE_INCL_SECTION(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_SECTION) CARRIAGE_RETURN

        "    " IF_PARAM_LIST(NON_TYPED_DEF_COMPOSED_TYPE_SECTION, COMPOSED_TYPE_VAR " ") COMPOSED_TYPED_COMPARE_SECTION_DECL_NAME_VAR " *currentCall_val = static_cast<" IF_PARAM_LIST(NON_TYPED_DEF_COMPOSED_TYPE_SECTION, COMPOSED_TYPE_VAR " ") COMPOSED_TYPED_COMPARE_SECTION_DECL_NAME_VAR " *>(currentCall_ptr);" CARRIAGE_RETURN
        "    " IF_PARAM_LIST(NON_TYPED_DEF_COMPOSED_TYPE_SECTION, COMPOSED_TYPE_VAR " ") COMPOSED_TYPED_COMPARE_SECTION_DECL_NAME_VAR " *expectedCall_val = static_cast<" IF_PARAM_LIST(NON_TYPED_DEF_COMPOSED_TYPE_SECTION, COMPOSED_TYPE_VAR " ") COMPOSED_TYPED_COMPARE_SECTION_DECL_NAME_VAR " *>(expectedCall_ptr);" CARRIAGE_RETURN

        TEMPLATE_BEG_SECTION(STRUCT_COMPARE_PARAM_SECTION)
        TEMPLATE_BEG_SECTION(STRUCT_COMPARE_PRE_IF_SECTION)
        "    std::string " TEMPLATE_VAR(STRUCT_COMPARE_PRE_IF_SECTION_VAR_NAME) "(paramName);" CARRIAGE_RETURN
        "    " TEMPLATE_VAR(STRUCT_COMPARE_PRE_IF_SECTION_VAR_NAME) ".append(\"" TEMPLATE_VAR(STRUCT_COMPARE_PRE_IF_SECTION_FIELD_NAME) "\");" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(STRUCT_COMPARE_PRE_IF_SECTION)
        "    if(" STRUCT_COMPARE_PARAM_SECTION_COMPARE_CONDITION_VAR ")" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(STRUCT_COMPARE_ERROR)
        "        snprintf(errorMessage, 256 , \"Parameter '%s' which is a" COMPOSED_TYPE_VAR " of type '" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_STRUCT_TYPE_VAR "' has field '" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR "' with value '%" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_PRINTF_FORMAT_VAR "', was expecting '%" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_PRINTF_FORMAT_VAR "'\", paramName, currentCall_val->" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR ", expectedCall_val->" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR ");" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(STRUCT_COMPARE_ERROR)
        "        return -1;" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(STRUCT_COMPARE_PARAM_SECTION)

        TEMPLATE_BEG_SECTION(STRUCT_COMPARE_ARRAY_SECTION)
        "    for(unsigned int idx = 0; idx < (sizeof(currentCall_val->" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR ")/sizeof(currentCall_val->" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR "[0])); idx++)" CARRIAGE_RETURN
        "    {" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(STRUCT_COMPARE_PRE_IF_SECTION)
        "        std::string " TEMPLATE_VAR(STRUCT_COMPARE_PRE_IF_SECTION_VAR_NAME) "(paramName);" CARRIAGE_RETURN
        "        " TEMPLATE_VAR(STRUCT_COMPARE_PRE_IF_SECTION_VAR_NAME) ".append(\"" TEMPLATE_VAR(STRUCT_COMPARE_PRE_IF_SECTION_FIELD_NAME) "\");" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(STRUCT_COMPARE_PRE_IF_SECTION)
        "        if(" STRUCT_COMPARE_PARAM_SECTION_COMPARE_CONDITION_VAR ")" CARRIAGE_RETURN
        "        {" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(STRUCT_COMPARE_ERROR)
        "            snprintf(errorMessage, 256 , \"Parameter '%s' which is a" COMPOSED_TYPE_VAR " of type '" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_STRUCT_TYPE_VAR "' has field array '" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR "' " PRINT_CMP_ARRAY_IDX " with value '%" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_PRINTF_FORMAT_VAR "', was expecting '%" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_PRINTF_FORMAT_VAR "'\", paramName" PRINT_CMP_ARRAY_IDX_value ",  currentCall_val->" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR ", expectedCall_val->" STRUCT_COMPARE_ERROR_SECTION_STRUCT_COMPARE_FIELD_VAR ");" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(STRUCT_COMPARE_ERROR)
        "            return -1;" CARRIAGE_RETURN
        "        }" CARRIAGE_RETURN
        "    }" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(STRUCT_COMPARE_ARRAY_SECTION)

        "    return 0;" CARRIAGE_RETURN
        "}" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_END_SECTION(COMPOSED_TYPE_COMPARE_SECTION)

        TEMPLATE_BEG_SECTION(FUNCTION_SECTION)
        GENERATE_COMMENT CARRIAGE_RETURN
        "typedef struct {" CARRIAGE_RETURN
        TEMPLATE_BEG_SECTION(FUNCTION_PARAM_SECTION)
        "    " DECLARE_NON_QUALIFIED_PARAMETER("") ";" CARRIAGE_RETURN
        "    EasyMock_Matcher " FUNCTION_MOCK_DATA_CUR_MATCH_VAR ";" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)
        IF_RETURN_VALUE("    " FUNCTION_NON_QUALIFIED_RETURN_VALUE_TYPE " " FUNCTION_MOCK_DATA_RETURN_VALUE_VARIABLE ";" CARRIAGE_RETURN)
        TEMPLATE_BEG_SECTION(FUNCTION_PARAM_PTR_SECTION)
        "    " DECLARE_PARAMETER(MOCK_OUT_PREFIX) ";" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_PARAM_PTR_SECTION)
        "} " FUNCTION_MOCK_DATA_TYPE";" CARRIAGE_RETURN
        CARRIAGE_RETURN
        "static " FUNCTION_EXPECT_RETURN_AND_OUTPUT_COMMON_SIGNATURE ";" CARRIAGE_RETURN
        "static MockedFunction<" FUNCTION_MOCK_DATA_TYPE "> " TEMPLATE_MOCKED_FUN_CLASS "(\"" TEMPLATE_FUNCTION_TO_BE_MOCKED "\");" CARRIAGE_RETURN
        IF_RETURN_VALUE("static " FUNCTION_NON_QUALIFIED_RETURN_VALUE_TYPE " dummyRes_" TEMPLATE_VAR(FUNCTION_NAME) ";" CARRIAGE_RETURN)
        CARRIAGE_RETURN
        "extern \"C\" " TEMPLATE_FUNCTION_TO_BE_MOCKED CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    bool printCallStack = easyMock_printCallStack();" CARRIAGE_RETURN
        "    bool checkFifoCall = easyMock_checkFifoCall();" CARRIAGE_RETURN
        CARRIAGE_RETURN
        IF_RETURN_VALUE
        (
            "    " FUNCTION_NON_QUALIFIED_RETURN_VALUE_TYPE " default_res;" CARRIAGE_RETURN
            "    std::memcpy(&default_res, &dummyRes_" TEMPLATE_VAR(FUNCTION_NAME) ", sizeof(default_res));" CARRIAGE_RETURN
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
        "     std::memcpy(&" MOCKED_DATA_MEMBER(PARAMETER_NAME("")) ", &" PARAMETER_NAME("") ", sizeof(" MOCKED_DATA_MEMBER(PARAMETER_NAME("")) "));" CARRIAGE_RETURN
        "    " MOCKED_DATA_MEMBER(FUNCTION_MOCK_DATA_CUR_MATCH_VAR) " = " FUNCTION_PARAM_MATCH_VAR ";" CARRIAGE_RETURN
        CARRIAGE_RETURN
        TEMPLATE_END_SECTION(FUNCTION_PARAM_SECTION)
        TEMPLATE_BEG_SECTION(FUNCTION_PARAM_PTR_SECTION)
        "     std::memcpy(&" MOCKED_DATA_MEMBER(PARAMETER_NAME(MOCK_OUT_PREFIX)) ", &" PARAMETER_NAME(MOCK_OUT_PREFIX) ", sizeof(" MOCKED_DATA_MEMBER(PARAMETER_NAME(MOCK_OUT_PREFIX)) "));" CARRIAGE_RETURN
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
        TEMPLATE_BEG_SECTION(COMPOSED_TYPE_COMPARE_SECTION)
        COMPOSED_TYPED_COMPARE_FUNCTION_SIGNATURE ";" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(COMPOSED_TYPE_COMPARE_SECTION)
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

static const char declareAnonymousComposableTypeTemplate[] =
        "typedef " RECURSIVE_ANONYMOUS_TYPE_DECLARATION_TYPE_VAR CARRIAGE_RETURN
        "{" CARRIAGE_RETURN
        "    " TEMPLATE_INCL_SECTION(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_FIELD_SECTION) CARRIAGE_RETURN
        "} " RECURSIVE_ANONYMOUS_TYPE_DECLARATION_NAME_VAR ";";

static const char declareAnonymousComposableTypeFieldTemplate[] =
        TEMPLATE_BEG_SECTION(ANONYMOUS_TYPE_DECLARATION_FIELD_SECTION)
        ANONYMOUS_TYPE_DECLARATION_FIELD_TYPE_VAR " " ANONYMOUS_TYPE_DECLARATION_FIELD_NAME_VAR ";" CARRIAGE_RETURN
        TEMPLATE_END_SECTION(ANONYMOUS_TYPE_DECLARATION_FIELD_SECTION)
        TEMPLATE_INCL_SECTION(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_SECTION);

CodeGeneratorCTemplate::CodeGeneratorCTemplate():
m_nbUnamedParam(0)
{
  m_generatedComparator.clear();
}


bool CodeGeneratorCTemplate::generateCode(const std::string& p_outDir, const std::string &p_fullPathToHeaderToMock, const ElementToMock::Vector& p_elem)
{
  ctemplate::TemplateDictionary dict("generateCode");

  std::string filenameToMock = boost::filesystem::path(p_fullPathToHeaderToMock).filename().string();
  fillInTemplateVariables(&dict, filenameToMock, p_elem);

  ctemplate::StringToTemplateCache(CFILE_TEMPLATE, templateText, ctemplate::DO_NOT_STRIP);
  ctemplate::StringToTemplateCache(HFILE_TEMPLATE, headerFileTemplate, ctemplate::DO_NOT_STRIP);
  ctemplate::StringToTemplateCache(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_TEMPLATE_NAME, declareAnonymousComposableTypeTemplate, ctemplate::DO_NOT_STRIP);
  ctemplate::StringToTemplateCache(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_TEMPLATE_FIELD_NAME, declareAnonymousComposableTypeFieldTemplate, ctemplate::DO_NOT_STRIP);

  std::string generatedCode;
  ctemplate::ExpandTemplate(CFILE_TEMPLATE, ctemplate::DO_NOT_STRIP, &dict, &generatedCode);
  if (!generateCodeToFile(p_outDir, filenameToMock, "cpp", generatedCode))
  {
    return false;
  }

  generatedCode.clear();
  ctemplate::ExpandTemplate(HFILE_TEMPLATE, ctemplate::DO_NOT_STRIP, &dict, &generatedCode);
  if (!generateCodeToFile(p_outDir, filenameToMock, "h", generatedCode))
  {
    return false;
  }

  return true;
}

void CodeGeneratorCTemplate::fillInTemplateVariables(ctemplate::TemplateDictionary *p_rootDictionnary, const std::string &p_mockedHeader, const ElementToMock::Vector &p_fList)
{
  p_rootDictionnary->SetValue(MOCKED_HEADER_FILENAME, p_mockedHeader);
  std::string fileNameWithoutExtUpper = p_mockedHeader.substr(0, p_mockedHeader.find_last_of("."));
  std::transform(fileNameWithoutExtUpper.begin(), fileNameWithoutExtUpper.end(), fileNameWithoutExtUpper.begin(), ::toupper);
  p_rootDictionnary->SetValue(MOCKED_FILE_NAME_WITHOUT_EXT_UPPER, fileNameWithoutExtUpper);
  std::unordered_set<std::string> generatedElements;
  for (ElementToMock::Vector::const_iterator it = p_fList.begin(); it != p_fList.end(); ++it)
  {
    const ElementToMock *elemToMock = *it;
    switch (elemToMock->getMockType())
    {
      case ETS_function:
      {
        const Function* fun = dynamic_cast<const Function*>(elemToMock);
        std::string functionPrototype = fun->getFunctionPrototype();
        if(generatedElements.find(functionPrototype) != generatedElements.end())
        {
          break;
        }
        generatedElements.insert(functionPrototype);
        generateFunctionSection(p_rootDictionnary, elemToMock);
        break;
      }
      default:
        break;
    }
  }
}

void CodeGeneratorCTemplate::generateFunctionSection(ctemplate::TemplateDictionary *p_rootDictionnary, const ElementToMock *p_elemToMock)
{
  ctemplate::TemplateDictionary *functionSectionDict = p_rootDictionnary->AddSectionDictionary(FUNCTION_SECTION);
  functionSectionDict->SetValue(FUNCTION_NAME, *p_elemToMock->getName());
  std::string upperString(*p_elemToMock->getName());
  std::transform(upperString.begin(), upperString.end(), upperString.begin(), ::toupper);
  functionSectionDict->SetValue(FUNCTION_NAME_UPPER, upperString);

  const ReturnValue *returnValue = p_elemToMock->getReturnType();
  const std::string returnTypeStr = returnValue->getType()->getFullDeclarationName();
  std::string nonQualRetTypeStr = getNonQualifiedDeclaratorString(returnValue);
  functionSectionDict->SetValue(FUNCTION_RETURN_VALUE, returnTypeStr);
  functionSectionDict->SetValue(FUNCTION_TO_RETURN_VALUE, returnTypeStr);
  const TypeItf* rvType = returnValue->getType();
  if(!rvType->isPointer())
  {
    functionSectionDict->SetValue(FUNCTION_NON_QUALIFIED_RETURN_VALUE, nonQualRetTypeStr);
  }
  else
  {
    functionSectionDict->SetValue(FUNCTION_NON_QUALIFIED_RETURN_VALUE, returnTypeStr);
  }

  bool isRvVoid = rvType->isCType() && rvType->getCType() == CTYPE_VOID && !rvType->isPointer();
  if (!isRvVoid)
  {
    ctemplate::TemplateDictionary *returnValParamDict = functionSectionDict->AddSectionDictionary(FUNCTION_RETURN_VALUE_PARAM_SECTION);
    if(!rvType->isPointer())
    {
      returnValParamDict->SetValue(FUNCTION_NON_QUALIFIED_RETURN_VALUE, nonQualRetTypeStr);
    }
    else
    {
      returnValParamDict->SetValue(FUNCTION_NON_QUALIFIED_RETURN_VALUE, returnTypeStr);
    }
  }
  const Parameter::Vector& funParams = p_elemToMock->getFunctionsParameters();
  generateFunctionParamSection(p_rootDictionnary, functionSectionDict, funParams);
  if(p_elemToMock->isVariadic())
  {
    ctemplate::TemplateDictionary *variadicSection = functionSectionDict->AddSectionDictionary(VARIADIC_SECTION);
    std::string variadicString;
    if(funParams.size() > 0)
    {
      variadicString.append(", ");
    }
    variadicString.append("...");
    variadicSection->SetValue(VARIADIC_VAR, variadicString);
  }
}

void CodeGeneratorCTemplate::generateFunctionParamSection(ctemplate::TemplateDictionary *p_rootDictionnary, ctemplate::TemplateDictionary *p_functionSectionDict, const Parameter::Vector& p_functionParam)
{
  bool ptrSectionAdded = false;
  if (p_functionParam.size() > 0)
  {
    //This specific section to show the comma ',' conditionally for the expect and return function generation
    p_functionSectionDict->AddSectionDictionary(FUNCTION_PARAM_LIST_SECTION);
  }
  for (Parameter::Vector::const_iterator it = p_functionParam.begin(); it != p_functionParam.end(); ++it)
  {
    ctemplate::TemplateDictionary* newTypedefParamSection = p_functionSectionDict->AddSectionDictionary(FUNCTION_PARAM_SECTION);
    const Parameter *fParam = *it;
    const TypeItf *paramType = fParam->getType();
    //For the rest of this function paramPtrType tells whether we are dealing with a pointer parameter or not
    const Pointer *paramPtrType = dynamic_cast<const Pointer *>(paramType);
    const std::string& argType = getDeclaratorString(fParam);
    std::string nonQualifiedArgType = getNonQualifiedDeclaratorString(fParam);
    if(paramPtrType)
    {
      paramType = paramPtrType->getPointedType();
    }
    if((paramType->isStruct() || paramType->isUnion()) && !paramType->isImplicit())
    {
      std::string prepend("");
      std::string declare("");
      generateComposedTypedCompareSection(p_rootDictionnary, dynamic_cast<const ComposableType*>(paramType), prepend, declare);
    }
    newTypedefParamSection->SetValue(FUNCTION_PARAM_TYPE, argType);
    if(!paramPtrType)
    {
      newTypedefParamSection->SetValue(FUNCTION_PARAM_NON_QUALIFIED_TYPE, nonQualifiedArgType);
    }
    else
    {
      newTypedefParamSection->SetValue(FUNCTION_PARAM_NON_QUALIFIED_TYPE, argType);
    }
    std::string paramName = fParam->getName();
    if(paramName.empty())
    {
      paramName.append("param" + std::to_string(m_nbUnamedParam));
      m_nbUnamedParam++;
    }
    newTypedefParamSection->SetValue(FUNCTION_PARAM_NAME, paramName);

    /*
     * It doesn't make sense to generate an output parameter for void pointer.
     * The mock doesn't know the size of the data to copy into the pointer.
     * Also do not generate the output parameter for const pointers.
     */
    if(paramPtrType)
    {
      const TypeItf* pointedType = paramPtrType->getPointedType();
      if(pointedType->getCType() != CTYPE_VOID &&
         !pointedType->isConst() &&
         !pointedType->isImplicit())
      {
        if(!ptrSectionAdded)
        {
          p_functionSectionDict->AddSectionDictionary(FUNCTION_PARAM_PTR_LIST_SECTION);
          ptrSectionAdded = true;
        }
        ctemplate::TemplateDictionary* newPtrParamSection = p_functionSectionDict->AddSectionDictionary(FUNCTION_PARAM_PTR_SECTION);
        //No need to add the FUNCTION_PARAM_NON_QUALIFIED_TYPE because we will not generate output pointer for const
        newPtrParamSection->SetValue(FUNCTION_PARAM_TYPE, argType);
        newPtrParamSection->SetValue(FUNCTION_PARAM_NAME, paramName);
      }
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

void CodeGeneratorCTemplate::generateFieldCmp(std::string& p_condition, const ComposableType *p_composedType, const ComposableField *p_curField, const ComposableField *p_previousField, std::string p_varName)
{
  if(p_curField->isAnonymous())
  {
    if(p_previousField)
    {
      p_condition.append("(char*)&");
      p_condition.append(p_varName);
      p_condition.append("->");
      p_condition.append(p_previousField->getName());
      /*
       * If the parent composable type is an union, we do not need to add sizeof
       * because all of the elements of the union have the same base address
       */
      if(!p_composedType->isUnion())
      {
        p_condition.append(" + sizeof(");
        p_condition.append(p_varName);
        p_condition.append("->");
        p_condition.append(p_previousField->getName());
        p_condition.append(")");
      }
    }
    else
    {
      /*
       * This anonymous composable type is the first field of the parent
       * composable type, so we just give the pointer as is
       */
      p_condition.append(p_varName);
    }
  }
  else
  {
    p_condition.push_back('&');
    p_condition.append(p_varName);
    p_condition.append("->");
    p_condition.append(p_curField->getName());
  }
  if(p_curField->isBoundSpecifiedArray())
  {
    p_condition.append("[idx]");
  }
}

void CodeGeneratorCTemplate::generateBodyStructCompare(ctemplate::TemplateDictionary *rootDictionnary, ctemplate::TemplateDictionary *p_paramSectDict, const ComposableType *p_composedType, const ComposableField *p_curField, const ComposableField *p_previousField, std::string p_uniquePrepend, std::string p_declPrepend)
{
  static unsigned int s_nbAnonymousField = 0;
  const TypeItf* curType = p_curField->getType();
  if(curType->isPointer())
  {
    curType = dynamic_cast<const Pointer *>(curType)->getPointedType();
  }
  if(curType->isComposableType())
  {
    const ComposableType* curComposableType = dynamic_cast<const ComposableType*>(curType);
    if(p_curField->isRecursiveTypeField())
    {
      //Recursive types are pointers, so simple field generation will do
      generateBasicTypeField(p_curField, p_paramSectDict, p_composedType, p_declPrepend);
    }
    else
    {
      std::string condition;
      ctemplate::TemplateDictionary *ifPreSectionDict = p_paramSectDict->AddSectionDictionary(STRUCT_COMPARE_PRE_IF_SECTION);
      std::string uniqueName = curComposableType->getUniqueName();

      std::string preFieldVarName("");
      if(p_curField->isAnonymous())
      {
        preFieldVarName.append("parameter_");
        preFieldVarName.append(std::to_string(s_nbAnonymousField));
        s_nbAnonymousField++;
      }
      else
      {
        preFieldVarName.append(p_curField->getName());
        preFieldVarName.append("_parameter");
        std::string ifSectionFieldName(".");
        ifSectionFieldName.append(p_curField->getName());
        ifPreSectionDict->SetValue(STRUCT_COMPARE_PRE_IF_SECTION_FIELD_NAME, ifSectionFieldName);
      }
      ifPreSectionDict->SetValue(STRUCT_COMPARE_PRE_IF_SECTION_VAR_NAME, preFieldVarName.c_str());
      condition.append("cmp_");
      condition.append(p_uniquePrepend);
      condition.push_back('_');
      condition.append(uniqueName);
      condition.push_back('(');
      generateFieldCmp(condition, p_composedType, p_curField, p_previousField, "currentCall_val");
      condition.append(", ");
      generateFieldCmp(condition, p_composedType, p_curField, p_previousField, "expectedCall_val");
      condition.append(", ");
      condition.append(preFieldVarName.c_str());
      condition.append(".c_str(), errorMessage)");

      p_uniquePrepend.push_back('_');
      p_declPrepend.append("::");
      generateComposedTypedCompareSection(rootDictionnary, curComposableType, p_uniquePrepend, p_declPrepend);

      p_paramSectDict->SetValue(COMPARE_CONDITION, condition);
    }
  } else if (curType->isCType()) {
    generateBasicTypeField(p_curField, p_paramSectDict, p_composedType, p_declPrepend);
  } else {
    std::fprintf(stderr, "Type '%s' unexpected here. Contact owner for bug fixing\n\r", curType->getFullDeclarationName().c_str());
    assert(false);
  }
}

void CodeGeneratorCTemplate::generateBasicTypeField(const ComposableField *p_curField, ctemplate::TemplateDictionary *p_paramSectDict, const ComposableType *p_composedType, std::string p_declPrepend)
{
  std::string condition;
  condition.append("currentCall_val->");
  condition.append(p_curField->getName());
  if(p_curField->isBoundSpecifiedArray())
  {
    condition.append("[idx]");
  }
  condition.append(" != expectedCall_val->");
  condition.append(p_curField->getName());
  if(p_curField->isBoundSpecifiedArray())
  {
    condition.append("[idx]");
  }
  ctemplate::TemplateDictionary *errorDict = p_paramSectDict->AddSectionDictionary(STRUCT_COMPARE_ERROR);
  std::string compareField = p_curField->getName();
  if(p_curField->isBoundSpecifiedArray())
  {
    errorDict->AddSectionDictionary(STRUCT_PRINT_IDX_SECTION); //This section needs to be added only once
    compareField.append("[idx]");
  }
  errorDict->SetValue(STRUCT_COMPARE_FIELD, compareField);
  std::string compareType;
  if(!p_composedType->isEmbeddedInOtherType())
  {
    compareType.append(p_composedType->getMostDefinedName());
  }
  else
  {
    compareType.append(p_declPrepend);
    if(p_composedType->isAnonymous())
    {
      compareType.append("<anonymous>");
    }
  }
  errorDict->SetValue(STRUCT_COMPARE_TYPE, compareType);
  const TypeItf *curFieldType = p_curField->getType();
  if(curFieldType->isPointer())
  {
    errorDict->SetValue(STRUCT_COMPARE_PRINTF_FORMAT, "p");
  }
  else
  {
    errorDict->SetValue(STRUCT_COMPARE_PRINTF_FORMAT, easyMock_printfFormat[curFieldType->getCType()]);
  }
  p_paramSectDict->SetValue(COMPARE_CONDITION, condition);
}

void CodeGeneratorCTemplate::generateDeclarationOfAnonymousType(ctemplate::TemplateDictionary* p_compareDict, const ComposableType* p_composedType)
{
  ctemplate::TemplateDictionary *anonymousDeclDict = p_compareDict->AddIncludeDictionary(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_SECTION);
  anonymousDeclDict->SetFilename(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_TEMPLATE_NAME);

  std::string typeVar("");
  if(p_composedType->isStruct())
  {
    typeVar.append("struct");
  }
  else if(p_composedType->isUnion())
  {
    typeVar.append("union");
  }
  else
  {
    fprintf(stderr, "Declaration string unknown composable type\n\r");
    assert(false);
  }
  anonymousDeclDict->SetValue(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_TYPE_TEMPLATE_VAR, typeVar);
  anonymousDeclDict->SetValue(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_NAME_TEMPLATE_VAR, p_composedType->getUniqueName());

  const ComposableField::Vector& vectField = p_composedType->getContainedFields();
  for (ComposableField::Vector::const_iterator it = vectField.begin(); it != vectField.end(); ++it)
  {
    ctemplate::TemplateDictionary *curFieldDict = anonymousDeclDict->AddIncludeDictionary(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_FIELD_SECTION);
    curFieldDict->SetFilename(RECURSIVE_ANONYMOUS_TYPE_DECLARATION_TEMPLATE_FIELD_NAME);
    const ComposableField *curField = *it;
    const TypeItf* fieldType = curField->getType();

    if(fieldType->isComposableType())
    {
      generateDeclarationOfAnonymousType(curFieldDict, dynamic_cast<const ComposableType*>(fieldType));
    }
    else
    {
      ctemplate::TemplateDictionary *curFieldValDict = curFieldDict->AddSectionDictionary(ANONYMOUS_TYPE_DECLARATION_FIELD_SECTION);
      curFieldValDict->SetValue(ANONYMOUS_TYPE_DECLARATION_FIELD_TYPE_TEMPLATE_VAR, fieldType->getFullDeclarationName());
      std::string fieldName = curField->getName();
      if(curField->isBoundSpecifiedArray())
      {
        fieldName.push_back('[');
        fieldName.append(std::to_string(curField->getArraySize()));
        fieldName.push_back(']');
      }
      curFieldValDict->SetValue(ANONYMOUS_TYPE_DECLARATION_FIELD_NAME_TEMPLATE_VAR, fieldName);
    }
  }
}

void CodeGeneratorCTemplate::generateComposedTypedCompareSection(ctemplate::TemplateDictionary *p_rootDictionnary, const ComposableType *p_composedType, std::string p_uniquePrepend, std::string p_declPrepend)
{
  const std::string& uniqueName = p_composedType->getUniqueName();
  const std::string& mostDefinedName = p_composedType->getMostDefinedName();

  //Generate each comparator only once.
  if(m_generatedComparator.find(mostDefinedName) != m_generatedComparator.end())
  {
    return;
  }
  m_generatedComparator.insert(mostDefinedName);

  p_uniquePrepend.append(uniqueName);

  p_declPrepend.append(mostDefinedName);

  ctemplate::TemplateDictionary *compareDict = p_rootDictionnary->AddSectionDictionary(COMPOSED_TYPE_COMPARE_SECTION);

  //Take care of generating the declaration of the anonymous type within the scope of the compare function
  if(p_composedType->isAnonymous())
  {
    generateDeclarationOfAnonymousType(compareDict, p_composedType);
  }

  if(p_composedType->isStruct())
  {
    //The space before struct is needed
    compareDict->SetValue(COMPOSED_TYPE_TEMPLATE_VAR, " struct");
  }
  else if(p_composedType->isUnion())
  {
    //Weird value but we want 'an union' iso 'a union'
    compareDict->SetValue(COMPOSED_TYPE_TEMPLATE_VAR, "n union");
  }
  else
  {
    fprintf(stderr, "Unknown composed type given\n\r");
    assert(false);
  }

  std::string declarationString;
  if(p_composedType->isAnonymous())
  {
    declarationString.append(p_composedType->getUniqueName());
  }
  else if(!p_composedType->isEmbeddedInOtherType())
  {
    declarationString.append(p_composedType->getFullDeclarationName());
  }
  else
  {
    declarationString.append(p_declPrepend);
  }
  compareDict->SetValue(COMPOSED_TYPED_DECL_STRING, declarationString);
  compareDict->SetValue(COMPOSED_TYPED_UNIQUE_NAME, p_uniquePrepend);

  const ComposableField::Vector& vectField = p_composedType->getContainedFields();
  const ComposableField *prevField = nullptr;
  for (ComposableField::Vector::const_iterator it = vectField.begin(); it != vectField.end(); ++it)
  {
    const ComposableField *curField = *it;
    if(curField->isBoundSpecifiedArray())
    {
      ctemplate::TemplateDictionary *arrayParamSect = compareDict->AddSectionDictionary(STRUCT_COMPARE_ARRAY_SECTION);
      arrayParamSect->SetValue(STRUCT_COMPARE_FIELD, curField->getName());
      generateBodyStructCompare(p_rootDictionnary, arrayParamSect, p_composedType, curField, prevField, p_uniquePrepend, p_declPrepend);
    }
    else
    {
      if(!curField->isUnboundSpecifiedArray())
      {
        //simple variable case
        ctemplate::TemplateDictionary *paramSectDict = compareDict->AddSectionDictionary(STRUCT_COMPARE_PARAM_SECTION);
        generateBodyStructCompare(p_rootDictionnary, paramSectDict, p_composedType, curField, prevField, p_uniquePrepend, p_declPrepend);
      }
      //else {???} Since we do not know the how many element is in the array, we cannot generate any code for it
    }
    prevField = curField;
  }
}

bool CodeGeneratorCTemplate::generateCodeToFile(const std::string &p_outDir, const std::string &p_filename, const std::string &p_extension, const std::string &p_generatedCode)
{
  bool rv = true;
  FILE *f = NULL;
  std::string outFilename(p_outDir);
  outFilename.append("/" MOCK_FRAMEWORK_NAME "_");
  outFilename.append(p_filename.substr(0, p_filename.find_last_of(".")));
  outFilename.append(".");
  outFilename.append(p_extension);

  std::fprintf(stdout, "Generating %s\n\r", outFilename.c_str());
  f = std::fopen(outFilename.c_str(), "w+");
  if (f == NULL)
  {
    std::fprintf(stderr, "Error creating %s: %s", outFilename.c_str(), strerror(errno));
    rv = false;
    goto closeFile;
  }
  if (std::fprintf(f, "%s", p_generatedCode.c_str()) < 0)
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

std::string CodeGeneratorCTemplate::getNonQualifiedDeclaratorString(const Declarator* p_decl)
{
  return p_decl->getType()->getFullNonQualifiedDeclarationName();
}

const std::string& CodeGeneratorCTemplate::getDeclaratorString(const Declarator* p_decl)
{
  return p_decl->getDeclareString();
}
