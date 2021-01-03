add_executable(test_structType
    ${EasyMock_SOURCE_DIR}/test/StructType/test_StructType.cpp
)

target_compile_options(test_structType PRIVATE ${STRUCT_TYPE_TEST_COMPILE_FLAGS})
target_include_directories(test_structType PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(test_structType ${TEST_LINK_LIB} ${EASYMOCK_COMMON_OBJ})
add_test(NAME test_structType COMMAND test_structType)

