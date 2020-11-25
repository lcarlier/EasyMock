#include "MainCodeGenerator.h"

MainCodeGenerator::MainCodeGenerator(const std::string p_filename, CodeParserItf &p_codeParser, CodeGeneratorItf &p_codeGenerator)
: m_filename(p_filename), m_codeParserItf(p_codeParser), m_codeGeneratorItf(p_codeGenerator)
{
}


bool MainCodeGenerator::generateCode(const std::string &outDir)
{
  ElementToMock::Vector elem;
  m_codeParserItf.setFilename(m_filename);
  m_codeParserItf.getElementToStub(elem);
  m_codeGeneratorItf.generateCode(outDir, m_filename, elem);
  return true;
}
