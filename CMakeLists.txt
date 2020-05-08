cmake_minimum_required (VERSION 2.6)
project (EasyMock)

set(CMAKE_CXX_STANDARD 17)
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

set(EASYMOCK_DEFAULT_CFLAGS -fsanitize=address -fno-omit-frame-pointer -g -O0 -Werror -Wall)
set(EASYMOCK_DEFAULT_LDFLAGS -fsanitize=address)

set(LLVM_PATH llvm-${LLVM_VERSION}/lib) #relative to /usr/lib
set(LINK_LIB
  ${CTEMPLATE_LIBRARIES}
  ${LIBUNWIND_LIBRARIES}
  ${LIBDW_LIBRARIES}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  clangTooling
  clangFrontend
  clangSerialization
  LLVMBitReader
  LLVMOption
  clangParse
  clangDriver
  LLVMProfileData
  LLVMCore
  clangSema
  clangAnalysis
  clangAST
  clangBasic
  LLVMMCParser
  LLVMMC
  LLVMBinaryFormat
  clangEdit
  LLVMSupport
  pthread
  clangLex
  z
  curses
)

find_library(CLANG_LIBRARIES clang PATH_SUFFIXES ${LLVM_PATH})
if (NOT CLANG_LIBRARIES)
    message (FATAL_ERROR "libclang was not found in the system. /usr/lib/${LLVM_PATH} was consulted")
endif()

#execute_process(COMMAND ${LLVM} --cxxflags COMMAND cut -d " " -f 1 COMMAND tr -d "\n" OUTPUT_VARIABLE LLVM_CXXFLAGS)
execute_process(COMMAND ${LLVM} --includedir COMMAND tr -d "\n" OUTPUT_VARIABLE LLVM_INCLUDEDIR)
set(LLVM_CXXFLAGS -I${LLVM_INCLUDEDIR})
execute_process(COMMAND ${LLVM} --ldflags COMMAND tr -d "\n" OUTPUT_VARIABLE LLVM_LDFLAGS)
execute_process(COMMAND ${LLVM} --ldflags COMMAND cut -d "L" -f 2 COMMAND tr -d "\n" COMMAND tr -d " " OUTPUT_VARIABLE LLVM_LIBRARY_PATH)

message("-- LLVM: ${LLVM}")
message("-- LLVM_VERSION: ${LLVM_VERSION}")
message("-- LLVM_CXXFLAGS: ${LLVM_CXXFLAGS}")
message("-- LLVM_LDFLAGS: ${LLVM_LDFLAGS}")
message("-- LLVM_LIBRARY_PATH: ${LLVM_LIBRARY_PATH}")

set(EASYMOCK_DEFAULT_LINK_PATH "-L${LLVM_LIBRARY_PATH}")

set(EASYMOCK_DEFAULT_FULL_LD_PARAM ${EASYMOCK_DEFAULT_LDFLAGS} ${EASYMOCK_DEFAULT_LINK_PATH} ${LINK_LIB})
set(EASYMOCK_DEFAULT_FULL_CC_PARAM ${EASYMOCK_DEFAULT_CFLAGS} ${LLVM_CXXFLAGS})

message("-- EASYMOCK_DEFAULT_FULL_CC_PARAM: ${EASYMOCK_DEFAULT_FULL_CC_PARAM}")
message("-- EASYMOCK_DEFAULT_FULL_LD_PARAM: ${EASYMOCK_DEFAULT_FULL_LD_PARAM}")

set(LLVM_PARSER_OBJ llvmParser)
set(CTEMPLATE_GENERATE_OBJ ctemplateGenerate)
set(CXXOPTS_CMD_LINE_PARSER_OBJ cxxoptsCmdLineParser)
set(EASYMOCK_COMMON_OBJ easyMockCommonObj)

add_subdirectory(src)

include(CTest)
enable_testing()
add_subdirectory(test)

add_custom_target(check COMMAND GTEST_COLOR=1 ${CMAKE_CTEST_COMMAND} --output-on-failure --verbose)
