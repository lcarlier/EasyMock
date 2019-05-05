cmake_minimum_required (VERSION 2.6)
project (EasyMock)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EASYMOCK_GEN EasyMockGenerate)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CTEMPLATE REQUIRED libctemplate>=2.3)
pkg_check_modules(LIBUNWIND REQUIRED libunwind>=1.21)
pkg_check_modules(LIBDW REQUIRED libdw>=0.170)

find_package(Boost 1.65 REQUIRED)

set(LLVM_VERSION 7)

find_program(LLVM NAMES llvm-config-${LLVM_VERSION})
if (NOT LLVM)
    message (FATAL_ERROR "llvm-config-${LLVM_VERSION} command not found")
endif()

set(LLVM_PATH llvm-${LLVM_VERSION}/lib) #relative to /usr/lib
set(LINK_LIB ${CTEMPLATE_LIBRARIES} ${LIBUNWIND_LIBRARIES} ${LIBDW_LIBRARIES} ${LIBBOOST_LIBRARIES})

find_library(CLANG_LIBRARIES clang PATH_SUFFIXES ${LLVM_PATH})
if (NOT CLANG_LIBRARIES)
    message (FATAL_ERROR "libclang was not found in the system. /usr/lib/${LLVM_PATH} was consulted")
endif()

execute_process(COMMAND ${LLVM} --cxxflags COMMAND cut -d " " -f 1 COMMAND tr -d "\n" OUTPUT_VARIABLE LLVM_CXXFLAGS)
execute_process(COMMAND ${LLVM} --ldflags COMMAND tr -d "\n" OUTPUT_VARIABLE LLVM_LDFLAGS)
execute_process(COMMAND ${LLVM} --ldflags COMMAND cut -d "L" -f 2 COMMAND tr -d "\n" OUTPUT_VARIABLE LLVM_LIBRARY_PATH)

message("-- LLVM_CXXFLAGS: ${LLVM_CXXFLAGS}")
message("-- LLVM_LDFLAGS: ${LLVM_LDFLAGS}")

add_executable(${EASYMOCK_GEN}
  src/easyMockGenerate/src/main.cpp
  src/easyMockGenerate/src/MainCodeGenerator.cpp
  src/easyMockGenerate/src/CodeGeneratorCTemplate.cpp
  src/easyMockGenerate/src/CodeParserCLang.cpp
)
target_compile_options(${EASYMOCK_GEN} PRIVATE -g -O0 -Werror -Wall ${LLVM_CXXFLAGS})
#Dirty trick to append link option. From cmake 3.13 there is a command for that

target_link_libraries(${EASYMOCK_GEN} ${LINK_LIB})
target_link_libraries(${EASYMOCK_GEN} "-L${LLVM_LIBRARY_PATH} -lclang")

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

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(example
    test/test.cpp src/easyMockGenerate/src/CodeGeneratorCTemplate.cpp
    src/easyMockFramework/src/easyMock.cpp)
target_compile_options(example PRIVATE -g -O0 -Werror -Wall -DPROJECT_ROOT_DIR="${PROJECT_SOURCE_DIR}")
target_include_directories(example PRIVATE src/easyMockFramework/include
                                           src/easyMockGenerate/src
                                           ${CMAKE_CURRENT_BINARY_DIR}
                                           ${CMAKE_CURRENT_BINARY_DIR}/test)
target_link_libraries(example ${LINK_LIB} gtest_main dl)

include(CTest)
add_test(NAME example_test COMMAND example)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)