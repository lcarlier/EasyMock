add_test(NAME test_forwardDeclareAndFullTypeInOneBuild
        COMMAND test/testForwardDeclareAndFullTypeInOneBuild/runTest.sh
        ${CMAKE_BINARY_DIR}/${EASYMOCK_GEN}
        ${EasyMock_SOURCE_DIR}
        $<TARGET_FILE_DIR:${EASYMOCK_FRAMEWORK_LIBRARY}>
        $<TARGET_FILE_NAME:${EASYMOCK_FRAMEWORK_LIBRARY}>
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_C_COMPILER}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        )
set_tests_properties(test_forwardDeclareAndFullTypeInOneBuild PROPERTIES TIMEOUT 7200
        FAIL_REGULAR_EXPRESSION "ERROR;runtime error"
        ENVIRONMENT UBSAN_OPTIONS=print_stacktrace=1)