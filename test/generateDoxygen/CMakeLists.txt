add_test(NAME test_generateDoxygen
        COMMAND test/generateDoxygen/runTest.sh
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        )
set_tests_properties(test_generateDoxygen PROPERTIES TIMEOUT 7200
        FAIL_REGULAR_EXPRESSION "ERROR;runtime error"
        ENVIRONMENT UBSAN_OPTIONS=print_stacktrace=1)