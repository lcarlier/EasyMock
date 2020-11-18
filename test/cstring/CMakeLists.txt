set(TEST_CTYPE_EXECUTABLE test_cstring)
add_executable(${TEST_CTYPE_EXECUTABLE}
    ${EasyMock_SOURCE_DIR}/test/cstring/test_cstring.cpp
)
target_compile_options(${TEST_CTYPE_EXECUTABLE} PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(${TEST_CTYPE_EXECUTABLE} PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(${TEST_CTYPE_EXECUTABLE} ${TEST_LINK_LIB} ${EASYMOCK_FRAMEWORK_LIBRARY})
add_test(NAME ${TEST_CTYPE_EXECUTABLE} COMMAND ${TEST_CTYPE_EXECUTABLE})


