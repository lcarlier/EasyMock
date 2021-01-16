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
                     ${CMAKE_CURRENT_BINARY_DIR}/test
                     ${gtest_SOURCE_DIR}/include
                     ${CTEMPLATE_INCLUDEDIR}
)

set(TEST_LINK_LIB ${EASYMOCK_DEFAULT_FULL_LD_PARAM} gtest_main dl -rdynamic)

#We use the -fno-access-control ONLY to compile UT because sometime we want to check internal states of objects
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fno-access-control)
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
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/UnionFunUnionFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/UnionTypedDefFunUnionTypedDefFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/UnionCommonHelper.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/StructWithUnionFunStructWithUnionFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunStructWithEmbeddedStructFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunStructWithEmbeddedAnonymousStructFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/gtestPrintClasses.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunUnionWithEmbeddedUnionFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunUnionWithEmbeddedAnonymousUnionFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunStructWithAnonymousStructFieldFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunUnionWithAnonymousUnionFieldFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunStructWithFirstAnonymousStructFieldFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunUnionWithFirstAnonymousUnionFieldFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/ConstIntFunConstIntFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunStructWithTypedefStructFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunStructRecusNonTypedefFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/StructFileFromStdioFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/CompileTwoFunctionsFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VariadicFunctionsFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/MultipleDefinitionsFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/FunctionVaArgsFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunParamNoNameFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidOutFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/InlineVoidFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunFunPtrFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunTypedefFunPtrFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/FunPtrCommonHelper.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunEnumFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunPtrToPtrRecurStructFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunStructForwardDeclaredFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunTypeDefFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunTypeDefGenTypeFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/CrossDefinedFunCrossDefinedFactory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/Int128FunUint128Factory.cpp
    ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/commonClasses/VoidFunStructBitfieldFactory.cpp
)

set(EASYMOCK_TEST_LIBRARY easyMockTestLibrary)
add_library(${EASYMOCK_TEST_LIBRARY}
    ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/easyMock_matcher.cpp
)
target_link_libraries(${EASYMOCK_TEST_LIBRARY} ${EASYMOCK_FRAMEWORK_LIBRARY})

target_compile_options(${EASYMOCK_TEST_LIBRARY} PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(${EASYMOCK_TEST_LIBRARY} PRIVATE ${TEST_INCLUDE_DIR})

target_compile_options(${TEST_FACTORIES_COMMON_OBJ} PRIVATE ${TEST_COMPILE_FLAGS})
target_include_directories(${TEST_FACTORIES_COMMON_OBJ} PRIVATE ${TEST_INCLUDE_DIR})

add_subdirectory(cstring)
add_subdirectory(CType)
add_subdirectory(StructType)
add_subdirectory(ReturnValue)
add_subdirectory(Pointer)
add_subdirectory(FunctionPointer)
add_subdirectory(easyMockGenerate)
add_subdirectory(end2end)
