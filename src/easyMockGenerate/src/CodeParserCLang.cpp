#include "CodeParserCLang.h"

CodeParserCLang::CodeParserCLang(const std::string filename)
: CodeParserItf()
{ }

CodeParser_errCode CodeParserCLang::getElementToStub(ElementToStubVector& elem) const
{
  return cp_OK;
}

