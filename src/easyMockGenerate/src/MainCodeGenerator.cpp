#include "MainCodeGenerator.h"

#include <cstdio>

MainCodeGenerator::MainCodeGenerator(const std::string p_filename, CodeParserItf &p_codeParser, CodeGeneratorItf &p_codeGenerator)
: m_filename(std::move(p_filename)), m_codeParserItf(p_codeParser), m_codeGeneratorItf(p_codeGenerator)
{
}


bool MainCodeGenerator::generateCode(const std::string &outDir, bool ignoreParserError)
{
  ElementToMockContext ctxt;
  m_codeParserItf.setFilename(m_filename);
  if(m_codeParserItf.getElementToMockContext(ctxt) != cp_OK && !ignoreParserError)
  {
    fprintf(stderr, "Parsing of %s failed.\n\r", m_filename.c_str());
    return false;
  }
  m_codeGeneratorItf.generateCode(outDir, m_filename, ctxt);
  return true;
}
