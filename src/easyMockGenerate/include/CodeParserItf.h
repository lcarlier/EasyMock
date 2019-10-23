#ifndef CODEPARSERITF_H
#define CODEPARSERITF_H

#include <string>
#include "ElementToMock.h"

enum CodeParser_errCode
{
  cp_OK
};

class CodeParserItf
{
public:
  CodeParserItf() :
  m_filename(""), m_flags("") {}
  CodeParserItf(std::string& filename, std::string& flags) :
  m_filename(filename), m_flags(flags)
  {}
  void setFilename(const std::string& filename) { m_filename = filename; }
  void setFlags(const std::string& flags) { m_flags = flags; }
  virtual CodeParser_errCode getElementToStub(ElementToMock::Vector &elem) const = 0;
protected:
  std::string m_filename;
  std::string m_flags;
};

#endif /* CODEPARSERITF_H */

