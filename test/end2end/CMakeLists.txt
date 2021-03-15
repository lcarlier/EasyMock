#TEST INTFUNINTINT

set(END_2_END_DEBUG 0)
if(CMAKE_BUILD_TYPE STREQUAL build_debug)
    set(END_2_END_DEBUG 1)
endif()

add_test(NAME test_end2endIntFunIntInt COMMAND
        ${EasyMock_SOURCE_DIR}/test/end2end/runTest.sh
        ${CMAKE_BINARY_DIR}/${EASYMOCK_GEN}
        ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/include/intFunIntInt.h
        ${EasyMock_SOURCE_DIR}/test/end2end/intFunIntInt.cpp
        " "
        ${gtest_SOURCE_DIR}
        ${gtest_BINARY_DIR}
        ${EasyMock_SOURCE_DIR}
        ${EasyMock_BINARY_DIR}
        ${END_2_END_DEBUG}
        )

#TEST STDIO

add_test(NAME test_end2endStdio COMMAND
        ${EasyMock_SOURCE_DIR}/test/end2end/runTest.sh
        ${CMAKE_BINARY_DIR}/${EASYMOCK_GEN}
        ${SDKROOT}/usr/include/stdio.h
        ${EasyMock_SOURCE_DIR}/test/end2end/funStdio.cpp
        "--mock-only fopen --mock-only fread --mock-only fwrite"
        ${gtest_SOURCE_DIR}
        ${gtest_BINARY_DIR}
        ${EasyMock_SOURCE_DIR}
        ${EasyMock_BINARY_DIR}
        ${END_2_END_DEBUG}
        )
