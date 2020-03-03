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
                     ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/includeCommonClasses
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR}/test)

set(TEST_LINK_LIB ${EASYMOCK_DEFAULT_FULL_LD_PARAM} gtest_main dl)

set(TEST_COMPILE_FLAGS ${EASYMOCK_DEFAULT_FULL_CC_PARAM} -DPROJECT_ROOT_DIR="${PROJECT_SOURCE_DIR}")

set(TEST_FACTORIES_COMMON_OBJ testFactoriesCommonObj)

add_library(${TEST_FACTORIES_COMMON_OBJ}
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunVoidFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/CharFunCharFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/IntFunVoidFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/DoubleFunDoubleFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/IntFunIntIntFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/LongDoubleFunLongDoubleFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/LongFunLongFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/LongLongFunLongLongFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/StructFunStructFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/UnsCharFunUnsCharFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/UnsIntFunUnsIntIntFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/UnsIntFunVoidFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/UnsLongFunUnsLongFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/UnsLongLongFunUnsLongLongFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/FloatFunFloatFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/UnsShortFunUnsShortFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/ShortFunShortFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunStructPtrFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/EasyMockStructHelper.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/StructCommonHelper.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/IntFunStructPtrIntCharPtrFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/StructRecursiveMemberPtrTypeFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunStructWithArrayFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunIntArrayFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/StructSubStructRecursiveTypeFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/StructTypedDefFunStructTypedDefFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/StructAnonymousTypedDefFunStructAnonymousTypedDefFactory.cpp
)

set(EASYMOCK_TEST_LIBRARY easyMockTestLibrary)
add_library(easyMockTestLibrary
    ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/easyMock_matcher.cpp
)

target_compile_options(${EASYMOCK_TEST_LIBRARY} PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(${EASYMOCK_TEST_LIBRARY} PRIVATE ${TEST_INCLUDE_DIR})

target_compile_options(${TEST_FACTORIES_COMMON_OBJ} PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(${TEST_FACTORIES_COMMON_OBJ} PRIVATE ${TEST_INCLUDE_DIR} ${gtest_SOURCE_DIR}/include)

add_subdirectory(easyMockGenerate)
add_subdirectory(CType)
add_subdirectory(StructType)
