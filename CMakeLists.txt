cmake_minimum_required (VERSION 3.10)
project (EasyMock)

# There is only one debug build. If this changes, check test/end2end/CMakeList.txt because an assumption is made
# on that over there.
set(build_debug "Debug")
set(build_release "Release")
set(build_release_with_test "ReleaseWithTest")
set(default_build_type ${build_release})

function(printallvar)
    get_cmake_property(_variableNames VARIABLES)
    list (SORT _variableNames)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endfunction()

function(ljoin VALUES GLUE OUTPUT)
    string (REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")
    string (REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
    set (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()

set(BUILD_TARGET_ARCH "" CACHE STRING "The target build architecture")
message(STATUS "CMAKE_HOST_SYSTEM_PROCESSOR : ${CMAKE_HOST_SYSTEM_PROCESSOR}")
if(BUILD_TARGET_ARCH STREQUAL "")
    if(CMAKE_HOST_SYSTEM_PROCESSOR  STREQUAL "arm"
        OR CMAKE_HOST_SYSTEM_PROCESSOR  STREQUAL "arm64"
        OR CMAKE_HOST_SYSTEM_PROCESSOR  STREQUAL "aarch64"
    )
        set(BUILD_TARGET_ARCH "arm")
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR  STREQUAL "x86_64")
        set(BUILD_TARGET_ARCH "x86")
    else()
        message(FATAL_ERROR "Architecture ${CMAKE_HOST_SYSTEM_PROCESSOR} not supported")
    endif()
endif()

set(BUILD_TARGET_ARCH_LIST "arm|x86")
if(NOT "${BUILD_TARGET_ARCH}" MATCHES "^(${BUILD_TARGET_ARCH_LIST})$")
    message(FATAL_ERROR "BUILD_TARGET_ARCH='${BUILD_TARGET_ARCH}' is not in '${BUILD_TARGET_ARCH_LIST}'")
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    set(default_build_type ${build_debug})
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/.hg")
    set(default_build_type ${build_debug})
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
      ${build_debug} ${build_release} ${build_release_with_test})
endif()

message(STATUS "Building for ${CMAKE_BUILD_TYPE}.")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENABLE_ASAN "" CACHE BOOL "Enable address sanitizer")
message(STATUS "BUILD_TARGET_ARCH: ${BUILD_TARGET_ARCH}")
if(CMAKE_BUILD_TYPE STREQUAL build_debug AND ENABLE_ASAN STREQUAL "")
    set(ENABLE_ASAN false)
    if(BUILD_TARGET_ARCH STREQUAL "arm" AND APPLE)
        message(STATUS "Address sanitizer is disabled on ARM Apple Silicon because it is not officially supported")
    else()
        set(ENABLE_ASAN true)
    endif()
endif()
if(ENABLE_ASAN STREQUAL "")
    set(ENABLE_ASAN false)
endif()
message(STATUS "ENABLE_ASAN: ${ENABLE_ASAN}")

find_package(PkgConfig REQUIRED)
pkg_check_modules(CTEMPLATE QUIET libctemplate>=2.3)
message(STATUS "CTEMPLATE_FOUND: ${CTEMPLATE_FOUND}")
if(NOT CTEMPLATE_FOUND)
    set(CTEMPLATE_LIB_INSTALL "" CACHE PATH "Path to where libctemplate has been installed")
    set(CTEMPLATE_INCLUDEDIR ${CTEMPLATE_LIB_INSTALL}/include)
    set(CTEMPLATE_LIBRARIES ctemplate)
    set(CTEMPLATE_LIBRARY_DIRS ${CTEMPLATE_LIB_INSTALL}/lib)
    set(CTEMPLATE_LDFLAGS -L${CTEMPLATE_LIBRARY_DIRS};-Wl,-search_paths_first;-l${CTEMPLATE_LIBRARIES})
endif()
set(CTEMPLATE_LIB_HEADER ${CTEMPLATE_INCLUDEDIR}/ctemplate/template.h)
if(NOT EXISTS ${CTEMPLATE_LIB_HEADER})
    message(FATAL_ERROR "libctemplate not found (${CTEMPLATE_LIB_HEADER}). Please install libctemplate or use -DCTEMPLATE_LIB_INSTALL=<pathToLibCtemplateInstall>")
endif()
pkg_check_modules(LIBUNWIND QUIET libunwind>=1.21)
pkg_check_modules(LIBDW QUIET libdw>=0.170)
set(BACKTRACE_SUPPORT false)
if(LIBUNWIND_FOUND AND LIBDW_FOUND)
    message(STATUS "BACKTRACE_SUPPORT is enabled")
    set(BACKTRACE_SUPPORT true)
else()
    message(STATUS "BACKTRACE_SUPPORT is disabled")
    message(STATUS "LIBUNWIND_FOUND:  ${LIBUNWIND_FOUND}")
    message(STATUS "LIBDW_FOUND: ${LIBDW_FOUND}")
endif()
pkg_check_modules(LIBNCURSES REQUIRED ncurses>=5)
message(STATUS "LIBNCURSES_LIBRARIES: ${LIBNCURSES_LIBRARIES}")
message(STATUS "LIBNCURSES_INCLUDE_DIRS: ${LIBNCURSES_INCLUDE_DIRS}")
message(STATUS "LIBNCURSES_INCLUDEDIR: ${LIBNCURSES_INCLUDEDIR}")
message(STATUS "LIBNCURSES_LIBRARY_DIRS: ${LIBNCURSES_LIBRARY_DIRS}")
message(STATUS "LIBNCURSES_LDFLAGS: ${LIBNCURSES_LDFLAGS}")

find_package(Boost 1.65 REQUIRED system filesystem)

set(LLVM_DEFAULT_VERSION 10)

message(STATUS "LLVM_PATH: ${LLVM_PATH}")
if(EXISTS ${LLVM_PATH})
    message(STATUS "Forcing finding llvm-config in ${LLVM_PATH}")
    find_program(LLVM_CONFIG NAMES llvm-config-${LLVM_DEFAULT_VERSION} llvm-config PATHS ${LLVM_PATH}/bin NO_DEFAULT_PATH)
else()
    find_program(LLVM_CONFIG NAMES llvm-config-${LLVM_DEFAULT_VERSION} llvm-config PATHS ${LLVM_PATH})
endif()
if (NOT LLVM_CONFIG OR NOT EXISTS ${LLVM_CONFIG})
    message (FATAL_ERROR "llvm-config command not found (${LLVM_CONFIG}). Please install llvm-config-${LLVM_DEFAULT_VERSION} or use -DLLVM_PATH=<path-to_llvm-install>")
else()
    message (STATUS "llvm-config found --> ${LLVM_CONFIG}")
endif()

find_package (Python COMPONENTS Interpreter)

if(NOT EXISTS ${LLVM_PATH})
    # We've got llvm-config right so <path-to-llvm-config>/../.. == LLVM_PATH
    # llvm-config-x can be symlink so we must resolve it first i.e. realpath(realpath({LLVM_CONFIG}))
    execute_process(COMMAND python3 -c "import os; print(os.path.realpath(os.path.realpath('${LLVM_CONFIG}')+'/../..'))" OUTPUT_VARIABLE LLVM_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

message(STATUS "LLVM_PATH: ${LLVM_PATH}")
find_library(CLANG_LIBRARIES NAMES clang PATHS ${LLVM_PATH} PATH_SUFFIXES lib)

if (NOT CLANG_LIBRARIES OR NOT EXISTS ${CLANG_LIBRARIES})
    message (FATAL_ERROR "libclang not found. CLANG_LIBRARIES=${CLANG_LIBRARIES}")
endif()

find_library(ZLIB_LIBRARIES NAMES z PATHS PATH_SUFFIXES lib)
if (NOT ZLIB_LIBRARIES)
    message (FATAL_ERROR "zlib not found.")
endif()

# set the C_IMPLICIT_INCLUDE_DIRECTORIES macro variable used in LLVMParser.cpp
ljoin("${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES}" ":" C_IMPLICIT_INCLUDE_DIRECTORIES)
set(EASYMOCK_DEFAULT_CFLAGS -Wall -Werror -DC_IMPLICIT_INCLUDE_DIRECTORIES="${C_IMPLICIT_INCLUDE_DIRECTORIES}")

if(CMAKE_BUILD_TYPE STREQUAL build_debug)
    set(EASYMOCK_DEFAULT_CFLAGS ${EASYMOCK_DEFAULT_CFLAGS} -g -O0)
    if(${ENABLE_ASAN})
        set(EASYMOCK_DEFAULT_CFLAGS ${EASYMOCK_DEFAULT_CFLAGS} -fsanitize=address -fno-omit-frame-pointer)
    endif()
else()
    set(EASYMOCK_DEFAULT_CFLAGS ${EASYMOCK_DEFAULT_CFLAGS} -O3)
endif()
message(STATUS "Setting extra debug flags (${EASYMOCK_DEFAULT_CFLAGS})")
if(${BACKTRACE_SUPPORT})
  set(EASYMOCK_DEFAULT_CFLAGS ${EASYMOCK_DEFAULT_CFLAGS} -DBACKTRACE_SUPPORT)
endif()

set(EASYMOCK_DEFAULT_LDFLAGS)
if(CMAKE_BUILD_TYPE STREQUAL build_debug)
    if(${ENABLE_ASAN})
        set(EASYMOCK_DEFAULT_LDFLAGS ${EASYMOCK_DEFAULT_LDFLAGS} -fsanitize=address)
    endif()
    message(STATUS "Setting extra link flags (${EASYMOCK_DEFAULT_LDFLAGS})")
endif()

# In the following list, some of the libraries are repeated on purpose because
# the linker discards too soon some symbols used by subsequent libraries and then
# fails with undefined symbol. By repeating the libraries, the linker is able to
# find the symbols it has missed the first time.
set(LINK_LIB
  ${CTEMPLATE_LIBRARIES}
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
  LLVMRemarks
  LLVMBitstreamReader
  LLVMFrontendOpenMP
  LLVMCore
  LLVMDemangle
  pthread
  clangLex
  z
  curses
)
if(${BACKTRACE_SUPPORT})
    set(LINK_LIB
    ${LINK_LIB}
    ${LIBUNWIND_LIBRARIES}
    ${LIBDW_LIBRARIES}
)
endif()

execute_process(COMMAND ${LLVM_CONFIG} --version COMMAND cut -d "." -f 1 OUTPUT_VARIABLE LLVM_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --includedir COMMAND tr -d "\n" OUTPUT_VARIABLE LLVM_INCLUDEDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
set(LLVM_CXXFLAGS -I${LLVM_INCLUDEDIR})
execute_process(COMMAND ${LLVM_CONFIG} --ldflags COMMAND tr -d "\n" OUTPUT_VARIABLE LLVM_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --ldflags COMMAND cut -d "L" -f 2 COMMAND tr -d "\n" COMMAND tr -d " " OUTPUT_VARIABLE LLVM_LIBRARY_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "LVM_VERSION: ${LLVM_VERSION}")
message(STATUS "LVM_CONFIG: ${LLVM_CONFIG}")
message(STATUS "LVM_CXXFLAGS: ${LLVM_CXXFLAGS}")
message(STATUS "LVM_LDFLAGS: ${LLVM_LDFLAGS}")
message(STATUS "LVM_LIBRARY_PATH: ${LLVM_LIBRARY_PATH}")

message(STATUS "Boost_INCLUDE_DIR: ${Boost_INCLUDE_DIR}")

set(EASYMOCK_DEFAULT_FULL_LD_PARAM ${EASYMOCK_DEFAULT_LDFLAGS} ${LLVM_LDFLAGS} ${LIBNCURSES_LDFLAGS} ${CTEMPLATE_LDFLAGS} ${LINK_LIB})
set(EASYMOCK_DEFAULT_FULL_CC_PARAM ${EASYMOCK_DEFAULT_CFLAGS} ${LLVM_CXXFLAGS})

message(STATUS "EASYMOCK_DEFAULT_FULL_CC_PARAM: ${EASYMOCK_DEFAULT_FULL_CC_PARAM}")
message(STATUS "EASYMOCK_DEFAULT_FULL_LD_PARAM: ${EASYMOCK_DEFAULT_FULL_LD_PARAM}")

set(LLVM_PARSER_OBJ llvmParser)
set(CTEMPLATE_GENERATE_OBJ ctemplateGenerate)
set(CMD_LINE_PARSER_OBJ cmdLineParser)
set(EASYMOCK_COMMON_OBJ easyMockCommonObj)
set(EASYMOCK_FRAMEWORK_LIBRARY EasyMockFramework)
set(EASYMOCK_GEN_INCLUDE_DIR ${EasyMock_SOURCE_DIR}/src/common/include
                             ${EasyMock_SOURCE_DIR}/src/easyMockFramework/include
                             ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/include
                             ${Boost_INCLUDE_DIR}
                             ${CTEMPLATE_INCLUDEDIR}
)
if(APPLE)
    execute_process(COMMAND xcrun --sdk macosx --show-sdk-path OUTPUT_VARIABLE SDKROOT OUTPUT_STRIP_TRAILING_WHITESPACE)
elseif(UNIX)
    set(SDKROOT "")
endif()
message(STATUS "SDKROOT: ${SDKROOT}")

set(EASYMOCK_GEN EasyMockGenerate)

add_subdirectory(src)

if(CMAKE_BUILD_TYPE STREQUAL build_debug OR CMAKE_BUILD_TYPE STREQUAL build_release_with_test)
    find_program(DOXYGEN_VAR doxygen)
    if(NOT DOXYGEN_VAR)
        message(FATAL_ERROR "Doxygen not found")
    endif()
    include(CTest)
    enable_testing()
    add_subdirectory(test)

    add_custom_target(check COMMAND GTEST_COLOR=1 ${CMAKE_CTEST_COMMAND} --output-on-failure)
endif()
