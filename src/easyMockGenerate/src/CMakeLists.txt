set(EASYMOCK_GEN EasyMockGenerate)
set(EASYMOCK_GEN_INCLUDE_DIR ${EasyMock_SOURCE_DIR}/src/common/include
                             ${EasyMock_SOURCE_DIR}/src/easyMockFramework/include
                             ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/include)

set(EASYMOCK_GEN_SOURCE_FILE
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/main.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/MainCodeGenerator.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CodeParserItf.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CodeParserCLang.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/TypeItf.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CType.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/StructType.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/StructField.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ReturnValue.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/Function.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/ElementToMock.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/EasyMockGenerateTypes.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/Parameter.cpp
)

add_subdirectory(CTemplateGenerator)
add_subdirectory(LLVMParser)

add_executable(${EASYMOCK_GEN}
  ${EASYMOCK_GEN_SOURCE_FILE}
)
target_compile_options(${EASYMOCK_GEN} PRIVATE ${EASYMOCK_DEFAULT_FULL_CC_PARAM})
#Dirty trick to append link option. From cmake 3.13 there is a command for that

target_link_libraries(${EASYMOCK_GEN} ${EASYMOCK_DEFAULT_FULL_LD_PARAM})
target_include_directories(${EASYMOCK_GEN} PRIVATE ${EASYMOCK_GEN_INCLUDE_DIR})
#target_link_libraries(${EASYMOCK_GEN} "-L${LLVM_LIBRARY_PATH}")
