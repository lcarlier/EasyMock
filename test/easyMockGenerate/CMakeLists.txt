set(TEST_INCLUDE_DIR ${EasyMock_SOURCE_DIR}/src/common/include
                     ${EasyMock_SOURCE_DIR}/src/easyMockFramework/include
                     ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src
                     ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src
                     ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/include
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR}/test)

set(TEST_COMMON_SRC_DIR
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/test_common.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CodeGeneratorCTemplate.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CodeParserItf.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/StructField.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/Parameter.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ReturnValue.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/Function.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ElementToMock.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/TypeItf.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CType.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/StructType.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/EasyMockGenerateTypes.cpp
)

set(TEST_LINK_LIB ${EASYMOCK_DEFAULT_LDFLAGS} ${LINK_LIB} gtest_main dl)

set(TEST_COMPILE_FLAGS ${EASYMOCK_DEFAULT_CFLAGS} -DPROJECT_ROOT_DIR="${PROJECT_SOURCE_DIR}")

add_executable(test_easyMockGenerate
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/test_structFunStruct.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/test_intFunIntInt.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/test_voidFunVoid.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/test_intFunVoid.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/test_moveCopy.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/test_equality.cpp
    ${TEST_COMMON_SRC_DIR})
target_compile_options(test_easyMockGenerate PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(test_easyMockGenerate PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_easyMockGenerate ${TEST_LINK_LIB})
add_test(NAME test_easyMockGenerate COMMAND test_easyMockGenerate)
