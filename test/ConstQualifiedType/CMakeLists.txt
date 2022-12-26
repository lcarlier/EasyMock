add_executable(test_ConstQualifiedType
    ${EasyMock_SOURCE_DIR}/test/ConstQualifiedType/test_ConstQualifiedType.cpp
)

set(STRUCT_TYPE_TEST_COMPILE_FLAGS ${TEST_COMPILE_FLAGS} -fno-access-control)
target_compile_options(test_ConstQualifiedType PRIVATE ${STRUCT_TYPE_TEST_COMPILE_FLAGS})
target_include_directories(test_ConstQualifiedType PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_ConstQualifiedType ${TEST_LINK_LIB} ${EASYMOCK_COMMON_OBJ})
add_test(NAME test_ConstQualifiedType COMMAND test_ConstQualifiedType)
set_tests_properties(test_ConstQualifiedType PROPERTIES TIMEOUT 7200
        FAIL_REGULAR_EXPRESSION "ERROR;runtime error"
        ENVIRONMENT UBSAN_OPTIONS=print_stacktrace=1)