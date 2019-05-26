#include "MainCodeGenerator.h"

MainCodeGenerator::MainCodeGenerator(const std::string filename, CodeParserItf &codeParser, const CodeGeneratorItf &codeGenerator)
: m_filename(filename), m_codeParserItf(codeParser), m_codeGeneratorItf(codeGenerator)
{
}


bool MainCodeGenerator::generateCode(const std::string &outDir)
{
  ElementToMockVector elem;
  m_codeParserItf.setFilename(m_filename);
  m_codeParserItf.getElementToStub(elem);
  m_codeGeneratorItf.generateCode(outDir, m_filename, elem);
  return true;
}
