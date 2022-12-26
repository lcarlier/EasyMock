add_executable(test_TypedefType
        ${EasyMock_SOURCE_DIR}/test/TypedefType/test_TypedefType.cpp
        )

set(STRUCT_TYPE_TEST_COMPILE_FLAGS ${TEST_COMPILE_FLAGS} -fno-access-control)
target_compile_options(test_TypedefType PRIVATE ${STRUCT_TYPE_TEST_COMPILE_FLAGS})
target_include_directories(test_TypedefType PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_TypedefType ${TEST_LINK_LIB} ${EASYMOCK_COMMON_OBJ})
add_test(NAME test_TypedefType COMMAND test_TypedefType)
set_tests_properties(test_TypedefType PROPERTIES TIMEOUT 7200
        FAIL_REGULAR_EXPRESSION "ERROR;runtime error"
        ENVIRONMENT UBSAN_OPTIONS=print_stacktrace=1)