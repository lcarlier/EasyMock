#ifndef CODEPARSERCLANG_H
#define CODEPARSERCLANG_H

#include "CodeParserItf.h"

class CodeParserCLang : public CodeParserItf
{
public:
  CodeParserCLang(const std::string filename);
  CodeParser_errCode getElementToStub(ElementToMock::Vector& elem) const;
};

#endif /* CODEPARSERCLANG_H */

