add_library(${LLVM_PARSER_OBJ}
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/LLVMParser/LLVMParser.cpp
)

#we must give -Wno-comment else LLVM fails to compile...
set(EASYMOCK_LLVM_FULL_CC_PARAM ${EASYMOCK_DEFAULT_FULL_CC_PARAM})
list(APPEND EASYMOCK_LLVM_FULL_CC_PARAM "-Wno-comment")
#we must give -Wno-strict-aliasing on debug build else LLVM headers fail to compile...
if(NOT CMAKE_BUILD_TYPE STREQUAL build_debug)
    list(APPEND EASYMOCK_LLVM_FULL_CC_PARAM "-Wno-strict-aliasing")
endif()

target_compile_options(${LLVM_PARSER_OBJ} PRIVATE ${EASYMOCK_LLVM_FULL_CC_PARAM})
target_link_libraries(${LLVM_PARSER_OBJ} ${EASYMOCK_COMMON_OBJ} ${EASYMOCK_DEFAULT_FULL_LD_PARAM})
target_include_directories(${LLVM_PARSER_OBJ} PRIVATE ${EASYMOCK_GEN_INCLUDE_DIR})
