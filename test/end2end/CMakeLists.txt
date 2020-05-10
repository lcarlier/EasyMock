add_custom_command(OUTPUT ${EasyMock_BINARY_DIR}/test/end2end/easyMock_intFunIntInt.cpp
                   COMMAND ${EasyMock_BINARY_DIR}/src/easyMockGenerate/src/EasyMockGenerate ARGS -i ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/include/intFunIntInt.h -o ${EasyMock_BINARY_DIR}/test/end2end/
                   DEPENDS ${EasyMock_BINARY_DIR}/src/easyMockGenerate/src/EasyMockGenerate ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/include/intFunIntInt.h)

set(TEST_E2E_INTFUNINTINT test_end2endIntFunIntInt)

add_executable(${TEST_E2E_INTFUNINTINT}
    ${EasyMock_SOURCE_DIR}/test/end2end/intFunIntInt.cpp
    ${EasyMock_BINARY_DIR}/test/end2end/easyMock_intFunIntInt.cpp
)

target_link_libraries(${TEST_E2E_INTFUNINTINT} ${EASYMOCK_FRAMEWORK_LIBRARY} ${TEST_LINK_LIB})
target_include_directories(${TEST_E2E_INTFUNINTINT} PRIVATE
    ${EasyMock_SOURCE_DIR}/src/easyMockFramework/include
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/include
    ${EasyMock_BINARY_DIR}/test/end2end/
)

add_test(NAME ${TEST_E2E_INTFUNINTINT} COMMAND ${TEST_E2E_INTFUNINTINT})
