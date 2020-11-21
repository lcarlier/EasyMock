add_custom_command(OUTPUT ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/includeCommonClasses/TestTypesInclude.h
                   COMMAND ${EasyMock_SOURCE_DIR}/tools/generateTestTypesInclude/generateTestTypesInclude.py ARGS --path-to-test-type-header ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/includeCommonClasses/TestTypes.h --out-directory ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/includeCommonClasses/
                   DEPENDS ${EasyMock_SOURCE_DIR}/tools/generateTestTypesInclude/generateTestTypesInclude.py ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/includeCommonClasses/TestTypes.h)

add_custom_target(
    generateTestInclude ALL
    DEPENDS ${EasyMock_SOURCE_DIR}/test/easyMockGenerate/includeCommonClasses/TestTypesInclude.h
    )

add_subdirectory(CommandLineParser)
add_subdirectory(common)
add_subdirectory(parser)
add_subdirectory(generate)
