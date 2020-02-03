add_library(${CTEMPLATE_GENERATE_OBJ}
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CTemplateGenerator/CodeGeneratorCTemplate.cpp
)

target_compile_options(${CTEMPLATE_GENERATE_OBJ} PRIVATE ${EASYMOCK_DEFAULT_FULL_CC_PARAM})
target_include_directories(${CTEMPLATE_GENERATE_OBJ} PRIVATE ${EASYMOCK_GEN_INCLUDE_DIR})