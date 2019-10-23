#ifndef CODEGENERATORITF_H
#define CODEGENERATORITF_H

#include <string>
#include "ElementToMock.h"

class CodeGeneratorItf {
public:
  virtual bool generateCode(const std::string& outDir, const std::string &headerToMock, const ElementToMock::Vector& elem) const = 0;
};

#endif /* CODEGENERATORITF_H */

