#include "MainCodeGenerator.h"

MainCodeGenerator::MainCodeGenerator(const std::string p_filename, CodeParserItf &p_codeParser, CodeGeneratorItf &p_codeGenerator)
: m_filename(p_filename), m_codeParserItf(p_codeParser), m_codeGeneratorItf(p_codeGenerator)
{
}


bool MainCodeGenerator::generateCode(const std::string &outDir)
{
  ElementToMockContext ctxt;
  m_codeParserItf.setFilename(m_filename);
  if(m_codeParserItf.getElementToMockContext(ctxt) != cp_OK)
  {
    return false;
  }
  m_codeGeneratorItf.generateCode(outDir, m_filename, ctxt);
  return true;
}
