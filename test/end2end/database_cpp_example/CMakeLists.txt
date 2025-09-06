set(END_2_END_DEBUG 0)
if(CMAKE_BUILD_TYPE STREQUAL build_debug)
    set(END_2_END_DEBUG 1)
endif()

add_test(NAME test_end2endDatabaseExample COMMAND
        ${EasyMock_SOURCE_DIR}/test/end2end/database_cpp_example/runTest.sh
        ${CMAKE_BINARY_DIR}/${EASYMOCK_GEN}
        ${gtest_SOURCE_DIR}
        ${EasyMock_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        ${EasyMock_SOURCE_DIR}
        ${EasyMock_BINARY_DIR}
        ${END_2_END_DEBUG}
        ${CMAKE_CXX_COMPILER}
        ${CMAKE_CXX_STANDARD}
)
set_tests_properties(test_end2endDatabaseExample PROPERTIES TIMEOUT 7200
        FAIL_REGULAR_EXPRESSION "ERROR;runtime error"
        ENVIRONMENT UBSAN_OPTIONS=print_stacktrace=1)