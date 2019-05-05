#ifndef CODEGENERATORITF_H
#define CODEGENERATORITF_H

#include <string>
#include "CodeGeneratorItf.h"
#include "CodeParserItf.h"

class CodeGeneratorItf {
public:
  virtual bool generateCode(const std::string& outDir, const std::string &headerToMock, const ElementToStubVector& elem) const = 0;
};

#endif /* CODEGENERATORITF_H */

