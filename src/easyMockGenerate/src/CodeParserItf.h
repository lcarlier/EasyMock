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
  CodeParserItf() {}
  void setFilename(const std::string filename) { m_filename = filename; }
  virtual CodeParser_errCode getElementToStub(ElementToMock::Vector &elem) const = 0;
protected:
  std::string m_filename;
};

#endif /* CODEPARSERITF_H */

