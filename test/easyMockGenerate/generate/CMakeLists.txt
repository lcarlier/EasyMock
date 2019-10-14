add_executable(test_easyMockGenerate_generate
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_common.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_structFunStruct.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_intFunIntInt.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_voidFunVoid.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_intFunVoid.cpp
    ${TEST_COMMON_SRC_DIR})
target_compile_options(test_easyMockGenerate_generate PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(test_easyMockGenerate_generate PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_easyMockGenerate_generate ${TEST_LINK_LIB})
add_test(NAME test_easyMockGenerate_generate COMMAND test_easyMockGenerate_generate)
