set(TEST_POINTER_TYPE_BINARY test_PointerType)
add_executable(${TEST_POINTER_TYPE_BINARY}
    ${EasyMock_SOURCE_DIR}/test/Pointer/test_Pointer.cpp
)

set(STRUCT_TYPE_TEST_COMPILE_FLAGS ${TEST_COMPILE_FLAGS} -fno-access-control)
target_compile_options(${TEST_POINTER_TYPE_BINARY} PRIVATE ${STRUCT_TYPE_TEST_COMPILE_FLAGS})
target_include_directories(${TEST_POINTER_TYPE_BINARY} PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(${TEST_POINTER_TYPE_BINARY} ${TEST_LINK_LIB} ${EASYMOCK_COMMON_OBJ})
add_test(NAME ${TEST_POINTER_TYPE_BINARY} COMMAND ${TEST_POINTER_TYPE_BINARY})
set_tests_properties(${TEST_POINTER_TYPE_BINARY} PROPERTIES TIMEOUT 7200
        FAIL_REGULAR_EXPRESSION "ERROR;runtime error"
        ENVIRONMENT UBSAN_OPTIONS=print_stacktrace=1)
