add_executable(test_ctype
    ${EasyMock_SOURCE_DIR}/test/CType/test_CType.cpp
)
target_compile_options(test_ctype PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(test_ctype PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_ctype ${TEST_LINK_LIB}  ${EASYMOCK_COMMON_OBJ})
add_test(NAME test_ctype COMMAND test_ctype)

