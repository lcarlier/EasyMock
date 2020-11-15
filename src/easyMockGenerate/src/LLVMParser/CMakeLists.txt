add_library(${LLVM_PARSER_OBJ}
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/LLVMParser/LLVMParser.cpp
)

target_compile_options(${LLVM_PARSER_OBJ} PRIVATE ${EASYMOCK_DEFAULT_FULL_CC_PARAM})
target_link_libraries(${LLVM_PARSER_OBJ} ${EASYMOCK_COMMON_OBJ} ${EASYMOCK_DEFAULT_FULL_LD_PARAM})
target_include_directories(${LLVM_PARSER_OBJ} PRIVATE ${EASYMOCK_GEN_INCLUDE_DIR})
