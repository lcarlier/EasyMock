set(TEST_PARAMETER_BINARY test_ParameterType)
add_executable(${TEST_PARAMETER_BINARY}
        ${EasyMock_SOURCE_DIR}/test/Parameter/test_Parameter.cpp
        )

set(STRUCT_TYPE_TEST_COMPILE_FLAGS ${TEST_COMPILE_FLAGS} -fno-access-control)
target_compile_options(${TEST_PARAMETER_BINARY} PRIVATE ${STRUCT_TYPE_TEST_COMPILE_FLAGS})
target_include_directories(${TEST_PARAMETER_BINARY} PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(${TEST_PARAMETER_BINARY} ${TEST_LINK_LIB} ${EASYMOCK_COMMON_OBJ})
add_test(NAME ${TEST_PARAMETER_BINARY} COMMAND ${TEST_PARAMETER_BINARY})
