#TEST INTFUNINTINT

add_custom_command(OUTPUT ${EasyMock_BINARY_DIR}/test/end2end/easyMock_intFunIntInt.c
                   COMMAND ${EASYMOCK_GEN} ARGS -i ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/include/intFunIntInt.h -o ${EasyMock_BINARY_DIR}/test/end2end/
                   DEPENDS ${EASYMOCK_GEN} ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/include/intFunIntInt.h)

set(TEST_E2E_INTFUNINTINT test_end2endIntFunIntInt)

add_executable(${TEST_E2E_INTFUNINTINT}
    ${EasyMock_SOURCE_DIR}/test/end2end/intFunIntInt.cpp
    ${EasyMock_BINARY_DIR}/test/end2end/easyMock_intFunIntInt.c
)

target_link_libraries(${TEST_E2E_INTFUNINTINT} ${EASYMOCK_FRAMEWORK_LIBRARY} ${TEST_LINK_LIB})
target_include_directories(${TEST_E2E_INTFUNINTINT} PRIVATE
    ${EasyMock_SOURCE_DIR}/src/easyMockFramework/include
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/include
    ${EasyMock_BINARY_DIR}/test/end2end/
)

add_test(NAME ${TEST_E2E_INTFUNINTINT} COMMAND ${TEST_E2E_INTFUNINTINT})

#TEST STDIO

add_custom_command(OUTPUT ${EasyMock_BINARY_DIR}/test/end2end/easyMock_stdio.c
                   COMMAND ${EASYMOCK_GEN} ARGS -i ${SDKROOT}/usr/include/stdio.h -o ${EasyMock_BINARY_DIR}/test/end2end/ --mock-only fopen --mock-only fread --mock-only fwrite
                   DEPENDS ${EASYMOCK_GEN} ${SDKROOT}/usr/include/stdio.h)

set(TEST_E2E_STDIO test_end2endStdio)

add_executable(${TEST_E2E_STDIO}
    ${EasyMock_SOURCE_DIR}/test/end2end/funStdio.cpp
    ${EasyMock_BINARY_DIR}/test/end2end/easyMock_stdio.c
)

target_link_libraries(${TEST_E2E_STDIO} ${EASYMOCK_FRAMEWORK_LIBRARY} ${TEST_LINK_LIB})
target_include_directories(${TEST_E2E_STDIO} PRIVATE
    ${EasyMock_SOURCE_DIR}/src/easyMockFramework/include
    ${EasyMock_BINARY_DIR}/test/end2end/
)

add_test(NAME ${TEST_E2E_STDIO} COMMAND ${TEST_E2E_STDIO})
