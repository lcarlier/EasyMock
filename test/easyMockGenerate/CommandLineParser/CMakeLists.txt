add_executable(test_CommandLineParser
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/CommandLineParser/test_CommandLineParser.cpp
)

set(CMD_LINE_PARSER_TEST_COMPILE_FLAGS ${TEST_COMPILE_FLAGS} -fno-access-control)
target_compile_options(test_CommandLineParser PRIVATE ${CMD_LINE_PARSER_TEST_COMPILE_FLAGS})
target_include_directories(test_CommandLineParser PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_CommandLineParser ${CMD_LINE_PARSER_OBJ} ${TEST_LINK_LIB} ${EASYMOCK_COMMON_OBJ})
add_test(NAME test_CommandLineParser COMMAND test_CommandLineParser)
