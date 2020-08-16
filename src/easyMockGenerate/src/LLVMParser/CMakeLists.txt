add_library(${LLVM_PARSER_OBJ}
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/LLVMParser/LLVMParser.cpp
)

set(EASYMOCK_LLVM_FULL_CC_PARAM ${EASYMOCK_DEFAULT_FULL_CC_PARAM})
#If the LLVM object is not compiled with optimisation, the address sanitiser
#creates an error. So we replace -O0 by -O1 just for this object
#In my cmake version, TRANSFORM is not yet supported
list(REMOVE_ITEM EASYMOCK_LLVM_FULL_CC_PARAM "-O0")
list(APPEND EASYMOCK_LLVM_FULL_CC_PARAM "-O1")
#we must also give -Wno-comment...
list(APPEND EASYMOCK_LLVM_FULL_CC_PARAM "-Wno-comment")
message(STATUS "---- for LLVM EASYMOCK_DEFAULT_FULL_CC_PARAM: ${EASYMOCK_DEFAULT_FULL_CC_PARAM} --> EASYMOCK_LLVM_FULL_CC_PARAM: ${EASYMOCK_LLVM_FULL_CC_PARAM}")
target_compile_options(${LLVM_PARSER_OBJ} PRIVATE ${EASYMOCK_LLVM_FULL_CC_PARAM})
target_link_libraries(${LLVM_PARSER_OBJ} ${EASYMOCK_COMMON_OBJ} ${EASYMOCK_DEFAULT_FULL_LD_PARAM})
target_include_directories(${LLVM_PARSER_OBJ} PRIVATE ${EASYMOCK_GEN_INCLUDE_DIR})
