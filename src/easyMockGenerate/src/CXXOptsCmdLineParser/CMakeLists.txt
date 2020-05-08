add_library(${CXXOPTS_CMD_LINE_PARSER_OBJ}
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CXXOptsCmdLineParser/CXXOptsCmdLineParser.cpp
)

target_compile_options(${CXXOPTS_CMD_LINE_PARSER_OBJ} PRIVATE ${EASYMOCK_DEFAULT_FULL_CC_PARAM})
target_include_directories(${CXXOPTS_CMD_LINE_PARSER_OBJ} PRIVATE ${EASYMOCK_GEN_INCLUDE_DIR})
