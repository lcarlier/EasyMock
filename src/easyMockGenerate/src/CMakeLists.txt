add_library(${EASYMOCK_COMMON_OBJ}
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CodeParserItf.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/TypeItf.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/EasyMock_CType.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/StructType.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ComposableField.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ReturnValue.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/Function.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ElementToMock.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/EasyMockGenerateTypes.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/Parameter.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/Declarator.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/UnionType.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ComposableType.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/Pointer.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CodeGeneratorItf.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/FunctionDeclaration.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/FunctionType.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/Enum.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/IncompleteType.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ElementToMockContext.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ComposableBitfield.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ComposableFieldItf.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/QualifiedType.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ConstQualifiedType.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/TypedefType.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/PrintObjects.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/MacroDefinition.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/FunctionAttribute.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/Namespace.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ClassType.cpp
)

set(EASYMOCK_GEN_SOURCE_FILE
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/main.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/MainCodeGenerator.cpp
)

add_subdirectory(CTemplateGenerator)
add_subdirectory(LLVMParser)
add_subdirectory(CmdLineParser)

add_executable(${EASYMOCK_GEN}
  ${EASYMOCK_GEN_SOURCE_FILE}
)
set_target_properties(${EASYMOCK_GEN} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_compile_options(${EASYMOCK_COMMON_OBJ} PRIVATE  ${EASYMOCK_DEFAULT_FULL_CC_PARAM})
target_compile_options(${EASYMOCK_GEN} PRIVATE ${EASYMOCK_DEFAULT_FULL_CC_PARAM})

#Dirty trick to append link option ${EASYMOCK_DEFAULT_FULL_LD_PARAM}. From cmake 3.13 there is a command for that
target_link_libraries(${EASYMOCK_GEN} ${EASYMOCK_COMMON_OBJ} ${LLVM_PARSER_OBJ} ${CTEMPLATE_GENERATE_OBJ} ${CMD_LINE_PARSER_OBJ} ${CTEMPLATE_GENERATE_OBJ} ${EASYMOCK_DEFAULT_FULL_LD_PARAM})
target_include_directories(${EASYMOCK_GEN} PRIVATE ${EASYMOCK_GEN_INCLUDE_DIR})
target_include_directories(${EASYMOCK_COMMON_OBJ} PRIVATE ${EASYMOCK_GEN_INCLUDE_DIR})
#target_link_libraries(${EASYMOCK_GEN} "-L${LLVM_LIBRARY_PATH}")
