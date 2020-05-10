#ifndef CODEGENERATORITF_H
#define CODEGENERATORITF_H

#include <string>
#include <unordered_set>
#include "ElementToMock.h"

using MockOnlyList = std::unordered_set<std::string>;

class CodeGeneratorItf {
public:
  virtual bool generateCode(const std::string& outDir, const std::string &headerToMock, const ElementToMock::Vector& elem) = 0;
  void setMockOnlyFunction(MockOnlyList list);
protected:
  MockOnlyList m_mockOnlyList;
};

#endif /* CODEGENERATORITF_H */

