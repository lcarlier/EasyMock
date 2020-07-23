add_library(${CMD_LINE_PARSER_OBJ}
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CmdLineParser/CmdLineParser.cpp
)

target_compile_options(${CMD_LINE_PARSER_OBJ} PRIVATE ${EASYMOCK_DEFAULT_FULL_CC_PARAM})
target_include_directories(${CMD_LINE_PARSER_OBJ} PRIVATE ${EASYMOCK_GEN_INCLUDE_DIR})
