add_executable(test_FunctionPointer
    ${EasyMock_SOURCE_DIR}/test/FunctionPointer/test_FunctionPointer.cpp
)

set(FUNCTION_POINTER_TEST_COMPILE_FLAGS ${TEST_COMPILE_FLAGS} -fno-access-control)
target_compile_options(test_FunctionPointer PRIVATE ${FUNCTION_POINTER_TEST_COMPILE_FLAGS})
target_include_directories(test_FunctionPointer PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_FunctionPointer ${TEST_LINK_LIB} ${EASYMOCK_COMMON_OBJ})
add_test(NAME test_FunctionPointer COMMAND test_FunctionPointer)
set_tests_properties(test_FunctionPointer PROPERTIES TIMEOUT 7200
        FAIL_REGULAR_EXPRESSION "ERROR;runtime error"
        ENVIRONMENT UBSAN_OPTIONS=print_stacktrace=1)
