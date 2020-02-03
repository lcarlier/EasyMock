add_executable(test_easyMockGenerate_parser
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/parser/test_genParser.cpp
)
target_compile_options(test_easyMockGenerate_parser PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(test_easyMockGenerate_parser PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_easyMockGenerate_parser ${TEST_LINK_LIB} ${TEST_FACTORIES_COMMON_OBJ} ${EASYMOCK_COMMON_OBJ} ${EASYMOCK_TEST_LIBRARY} ${LLVM_PARSER_OBJ})
add_test(NAME test_easyMockGenerate_parser COMMAND test_easyMockGenerate_parser)
