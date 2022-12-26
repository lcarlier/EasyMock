set(TEST_CTYPE test_ctype)
add_executable(${TEST_CTYPE}
    ${EasyMock_SOURCE_DIR}/test/CType/test_CType.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/PrintObjects.cpp
)
target_compile_options(${TEST_CTYPE} PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(${TEST_CTYPE} PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(${TEST_CTYPE} ${TEST_LINK_LIB} ${EASYMOCK_COMMON_OBJ})
add_test(NAME ${TEST_CTYPE} COMMAND ${TEST_CTYPE})
set_tests_properties(${TEST_CTYPE} PROPERTIES TIMEOUT 7200
        FAIL_REGULAR_EXPRESSION "ERROR;runtime error"
        ENVIRONMENT UBSAN_OPTIONS=print_stacktrace=1)
