add_executable(test_easyMockGenerate_common
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/common/test_moveCopy.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/common/test_equality.cpp
)
target_compile_options(test_easyMockGenerate_common PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(test_easyMockGenerate_common PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_easyMockGenerate_common ${TEST_LINK_LIB}  ${EASYMOCK_COMMON_OBJ})
add_test(NAME test_easyMockGenerate_common COMMAND test_easyMockGenerate_common)
