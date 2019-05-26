set(EASYMOCK_GEN EasyMockGenerate)

add_executable(${EASYMOCK_GEN}
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/main.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/MainCodeGenerator.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CodeGeneratorCTemplate.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockGenerate/src/CodeParserCLang.cpp
)
target_compile_options(${EASYMOCK_GEN} PRIVATE -g -O0 -Werror -Wall ${LLVM_CXXFLAGS})
#Dirty trick to append link option. From cmake 3.13 there is a command for that

target_link_libraries(${EASYMOCK_GEN} ${LINK_LIB})
target_link_libraries(${EASYMOCK_GEN} "-L${LLVM_LIBRARY_PATH} -lclang")
