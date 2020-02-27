#ifndef CODEPARSER_H
#define CODEPARSER_H

#include <vector>
#include <string>

#include "CodeParserItf.h"
#include "CodeGeneratorItf.h"

class MainCodeGenerator
{
public:
  MainCodeGenerator(const std::string filename, CodeParserItf &codeParser, CodeGeneratorItf &codeGenerator);
  bool generateCode(const std::string &outDir);
private:
  std::string m_filename;
  CodeParserItf &m_codeParserItf;
  CodeGeneratorItf &m_codeGeneratorItf;
};

#endif /* CODEPARSER_H */

