#ifndef LLVMPARSER_H
#define LLVMPARSER_H

#include "CodeParserItf.h"

class LLVMParser : public CodeParserItf
{
public:
  LLVMParser();
  LLVMParser(std::string &filename, ParserExtraArgs& flags);
  CodeParser_errCode getElementToStub(ElementToMock::Vector& elem) const;
  virtual ~LLVMParser();
private:
};

#endif /* LLVMPARSER_H */

