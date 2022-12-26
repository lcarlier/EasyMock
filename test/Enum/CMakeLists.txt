set(TEST_ENUM_BINARY test_EnumType)
add_executable(${TEST_ENUM_BINARY}
        ${EasyMock_SOURCE_DIR}/test/Enum/test_Enum.cpp
        )

set(STRUCT_TYPE_TEST_COMPILE_FLAGS ${TEST_COMPILE_FLAGS} -fno-access-control)
target_compile_options(${TEST_ENUM_BINARY} PRIVATE ${STRUCT_TYPE_TEST_COMPILE_FLAGS})
target_include_directories(${TEST_ENUM_BINARY} PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(${TEST_ENUM_BINARY} ${TEST_LINK_LIB} ${EASYMOCK_COMMON_OBJ})
add_test(NAME ${TEST_ENUM_BINARY} COMMAND ${TEST_ENUM_BINARY})
set_tests_properties(${TEST_ENUM_BINARY} PROPERTIES TIMEOUT 7200
        FAIL_REGULAR_EXPRESSION "ERROR;runtime error"
        ENVIRONMENT UBSAN_OPTIONS=print_stacktrace=1)