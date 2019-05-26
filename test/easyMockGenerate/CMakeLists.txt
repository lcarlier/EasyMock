
add_executable(test_easyMockGenerate
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/test_voidFunVoid.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CodeGeneratorCTemplate.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/easyMock.cpp)
target_compile_options(test_easyMockGenerate PRIVATE -g -O0 -Werror -Wall -DPROJECT_ROOT_DIR="${PROJECT_SOURCE_DIR}")
target_include_directories(test_easyMockGenerate PRIVATE
                                           ${EasyMock_SOURCE_DIR}/src/easyMockFramework/include
                                           ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src
                                           ${CMAKE_CURRENT_BINARY_DIR}
                                           ${CMAKE_CURRENT_BINARY_DIR}/test)
target_link_libraries(test_easyMockGenerate ${LINK_LIB} gtest_main dl)

add_test(NAME test_easyMockGenerate COMMAND test_easyMockGenerate)
