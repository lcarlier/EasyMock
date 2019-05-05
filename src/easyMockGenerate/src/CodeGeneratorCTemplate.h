#ifndef CODEGENERATORCTEMPLATE_H
#define CODEGENERATORCTEMPLATE_H

#include "CodeGeneratorCTemplate.h"
#include "CodeGeneratorItf.h"

class CodeGeneratorCTemplate : public CodeGeneratorItf
{
public:
  bool generateCode(const std::string& outDir, const std::string &headerToMock, const ElementToStubVector& elem) const;

};

#endif /* CODEGENERATORCTEMPLATE_H */

