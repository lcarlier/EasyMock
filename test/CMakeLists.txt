configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

set(TEST_INCLUDE_DIR ${EasyMock_SOURCE_DIR}/src/common/include
                     ${EasyMock_SOURCE_DIR}/src/easyMockFramework/include
                     ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src
                     ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/include
                     ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/include
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR}/test)

set(TEST_COMMON_SRC_DIR
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CodeParserItf.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/StructField.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/Parameter.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ReturnValue.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/Function.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ElementToMock.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/TypeItf.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CType.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/StructType.cpp
    ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/EasyMockGenerateTypes.cpp
)

set(TEST_LINK_LIB ${EASYMOCK_DEFAULT_FULL_LD_PARAM} gtest_main dl)

set(TEST_COMPILE_FLAGS ${EASYMOCK_DEFAULT_FULL_CC_PARAM} -DPROJECT_ROOT_DIR="${PROJECT_SOURCE_DIR}")

add_subdirectory(easyMockGenerate)
add_subdirectory(CType)
