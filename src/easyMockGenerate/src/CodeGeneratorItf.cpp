#include <CodeGeneratorItf.h>

void CodeGeneratorItf::setMockOnlyFunction(const MockOnlyList& list)
{
  this->m_mockOnlyList = list;
}

void CodeGeneratorItf::setGenerateUsedType(bool value)
{
  this->m_generateUsedType = value;
}

bool CodeGeneratorItf::generateCode(const std::string& p_outDir, const std::string &p_fullPathToHeaderToMock, const ElementToMockContext& p_elem)
{
  return generateCodeImplementation(p_outDir, p_fullPathToHeaderToMock, p_elem);
}
