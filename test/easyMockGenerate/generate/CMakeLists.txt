add_executable(test_easyMockGenerate_generate
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_common.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_structFunStruct.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_intFunIntInt.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_voidFunVoid.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_intFunVoid.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_genGenerate.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_genGenerateOutputPtr.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_voidFunStructPtr.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_intFunStructPtrIntCharPtr.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_generateVoidFunStructWithArray.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_structSubStructRecursiveType.cpp
)

target_compile_options(test_easyMockGenerate_generate PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(test_easyMockGenerate_generate PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_easyMockGenerate_generate ${CTEMPLATE_GENERATE_OBJ} ${TEST_LINK_LIB} ${EASYMOCK_TEST_LIBRARY} ${TEST_FACTORIES_COMMON_OBJ} ${EASYMOCK_COMMON_OBJ})
add_test(NAME test_easyMockGenerate_generate COMMAND test_easyMockGenerate_generate)
