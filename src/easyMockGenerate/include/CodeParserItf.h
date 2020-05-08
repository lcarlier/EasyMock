#ifndef CODEPARSERITF_H
#define CODEPARSERITF_H

#include <string>
#include <vector>
#include <functional>

#include "ElementToMock.h"
#include "ComposableType.h"

enum CodeParser_errCode
{
  cp_OK
};

using ParserExtraArgs = std::vector<std::string>;

class CodeParserItf
{
public:
  CodeParserItf() :
  m_filename(""), m_flags({}) {}
  CodeParserItf(std::string& filename, ParserExtraArgs& flags) :
  m_filename(filename), m_flags(flags)
  {}

  //setFilename is also going to initilise the hash type for anonymous name of the structs and unions comparator functions
  void setFilename(const std::string& filename) { m_filename = filename; ComposableType::setFileHash(std::hash<std::string>{}(filename)); }
  void setFlags(const ParserExtraArgs& flags) { m_flags = flags; }
  virtual CodeParser_errCode getElementToStub(ElementToMock::Vector &elem) const = 0;
protected:
  std::string m_filename;
  ParserExtraArgs m_flags;
};

#endif /* CODEPARSERITF_H */

