add_test(NAME test_ignoreParserError
        COMMAND test/IgnoreParserError/runTest.sh
        ${CMAKE_BINARY_DIR}/${EASYMOCK_GEN}
        ${EasyMock_BINARY_DIR}
        ${EasyMock_SOURCE_DIR}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        )
