#Do not use list append because it does not supports parent scope
set(EASYMOCK_GEN_SOURCE_FILE
  ${EASYMOCK_GEN_SOURCE_FILE}
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/LLVMParser/LLVMParser.cpp
  PARENT_SCOPE
)
