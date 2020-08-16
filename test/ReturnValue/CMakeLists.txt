add_executable(test_returnValue
    ${EasyMock_SOURCE_DIR}/test/ReturnValue/test_ReturnValue.cpp
)

set(STRUCT_TYPE_TEST_COMPILE_FLAGS ${TEST_COMPILE_FLAGS} -fno-access-control)
target_compile_options(test_returnValue PRIVATE ${STRUCT_TYPE_TEST_COMPILE_FLAGS})
target_include_directories(test_returnValue PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_returnValue ${TEST_LINK_LIB} ${EASYMOCK_COMMON_OBJ})
add_test(NAME test_returnValue COMMAND test_returnValue)

