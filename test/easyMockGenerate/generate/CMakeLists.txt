set(EASYMOCK_GENERATE_TEST_BINARY test_easyMockGenerate_generate)

# We do not use ${EASYMOCK_TEST_LIBRARY} (i.e. libEasyMockFramework) in target_link_libraries because for the need of the unit test
# test_common.cpp directly includes easyMock.cpp. That will create 2 instances of the EasyMock class
# which is initialised via __attribute ((init_priority(101))) and create issues where the error message
# can be inserted in the wrong instance of the EasyMock class.
# Because libEasyMockFramework also contains other symbols needed by this UT, we compile them in by putting them in the
# add_executable rule bellow
add_executable(${EASYMOCK_GENERATE_TEST_BINARY}
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_common.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_structFunStruct.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_intFunIntInt.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_voidFunVoid.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_intFunVoid.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_genGenerate.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_genGenerateClass.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_genGenerateOutputPtr.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_voidFunStructPtr.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_intFunStructPtrIntCharPtr.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_generateVoidFunStructWithArray.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_structSubStructRecursiveType.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_voidFunComposableTypeWithComposableType.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/generate/test_compileOnly.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/easyMock_matcher.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/cstring.c
    ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/MockedFunction.c
    ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/easyMock_glueStdlib.c
)

target_compile_options(${EASYMOCK_GENERATE_TEST_BINARY} PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(${EASYMOCK_GENERATE_TEST_BINARY} PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(${EASYMOCK_GENERATE_TEST_BINARY} ${CTEMPLATE_GENERATE_OBJ} ${TEST_LINK_LIB} ${TEST_FACTORIES_COMMON_OBJ} ${EASYMOCK_COMMON_OBJ})
add_test(NAME ${EASYMOCK_GENERATE_TEST_BINARY} COMMAND ${EASYMOCK_GENERATE_TEST_BINARY})
set_tests_properties(${EASYMOCK_GENERATE_TEST_BINARY} PROPERTIES TIMEOUT 7200
        FAIL_REGULAR_EXPRESSION "ERROR;runtime error"
        ENVIRONMENT UBSAN_OPTIONS=print_stacktrace=1)
