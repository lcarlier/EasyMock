cmake_minimum_required (VERSION 2.6)
project (EasyMock)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CTEMPLATE REQUIRED libctemplate>=2.3)
pkg_check_modules(LIBUNWIND REQUIRED libunwind>=1.21)
pkg_check_modules(LIBDW REQUIRED libdw>=0.170)

find_package(Boost 1.65 REQUIRED system filesystem)

set(LLVM_VERSION 7)

find_program(LLVM NAMES llvm-config-${LLVM_VERSION})
if (NOT LLVM)
    message (FATAL_ERROR "llvm-config-${LLVM_VERSION} command not found")
endif()

set(LLVM_PATH llvm-${LLVM_VERSION}/lib) #relative to /usr/lib
set(LINK_LIB ${CTEMPLATE_LIBRARIES} ${LIBUNWIND_LIBRARIES} ${LIBDW_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

find_library(CLANG_LIBRARIES clang PATH_SUFFIXES ${LLVM_PATH})
if (NOT CLANG_LIBRARIES)
    message (FATAL_ERROR "libclang was not found in the system. /usr/lib/${LLVM_PATH} was consulted")
endif()

execute_process(COMMAND ${LLVM} --cxxflags COMMAND cut -d " " -f 1 COMMAND tr -d "\n" OUTPUT_VARIABLE LLVM_CXXFLAGS)
execute_process(COMMAND ${LLVM} --ldflags COMMAND tr -d "\n" OUTPUT_VARIABLE LLVM_LDFLAGS)
execute_process(COMMAND ${LLVM} --ldflags COMMAND cut -d "L" -f 2 COMMAND tr -d "\n" OUTPUT_VARIABLE LLVM_LIBRARY_PATH)

message("-- LLVM_CXXFLAGS: ${LLVM_CXXFLAGS}")
message("-- LLVM_LDFLAGS: ${LLVM_LDFLAGS}")

add_subdirectory(src)

include(CTest)
enable_testing()
add_subdirectory(test)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)
