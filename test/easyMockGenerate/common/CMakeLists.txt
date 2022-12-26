add_executable(test_easyMockGenerate_common
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/PrintObjects.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/common/test_move.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/common/test_equality.cpp
)
target_compile_options(test_easyMockGenerate_common PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(test_easyMockGenerate_common PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_easyMockGenerate_common ${TEST_LINK_LIB}  ${EASYMOCK_COMMON_OBJ})
add_test(NAME test_easyMockGenerate_common COMMAND test_easyMockGenerate_common)
set_tests_properties(test_easyMockGenerate_common PROPERTIES TIMEOUT 7200
        FAIL_REGULAR_EXPRESSION "ERROR;runtime error"
        ENVIRONMENT UBSAN_OPTIONS=print_stacktrace=1)