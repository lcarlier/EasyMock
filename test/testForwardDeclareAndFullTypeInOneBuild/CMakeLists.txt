add_test(NAME test_forwardDeclareAndFullTypeInOneBuild
        COMMAND test/testForwardDeclareAndFullTypeInOneBuild/runTest.sh
        ${CMAKE_BINARY_DIR}/${EASYMOCK_GEN}
        ${EasyMock_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        )
