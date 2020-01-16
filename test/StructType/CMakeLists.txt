add_executable(test_structType
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/StructType.cpp
    ${EasyMock_SOURCE_DIR}/test/StructType/test_StructType.cpp
    ${TEST_COMMON_SRC_DIR})
target_compile_options(test_structType PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(test_structType PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_structType ${TEST_LINK_LIB})
add_test(NAME test_structType COMMAND test_structType)

