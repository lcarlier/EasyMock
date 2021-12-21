add_test(NAME test_generateStructComparatorForceAll
        COMMAND test/generateStructComparatorForceAll/runTest.sh
        ${CMAKE_BINARY_DIR}/${EASYMOCK_GEN}
        ${EasyMock_BINARY_DIR}
        ${EasyMock_SOURCE_DIR}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        )
