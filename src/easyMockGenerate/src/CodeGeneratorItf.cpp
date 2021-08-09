#include <CodeGeneratorItf.h>

void CodeGeneratorItf::setMockOnlyFunction(MockOnlyList p_list)
{
  this->m_mockOnlyList = std::move(p_list);
}

void CodeGeneratorItf::setGenerateAttrList(GenerateAttrList p_list)
{
  this->m_generateAttrList = std::move(p_list);
}

void CodeGeneratorItf::setGenerateUsedType(bool p_value)
{
  this->m_generateUsedType = p_value;
}

bool CodeGeneratorItf::generateCode(const std::string& p_outDir, const std::string &p_fullPathToHeaderToMock, const ElementToMockContext& p_elem)
{
  return generateCodeImplementation(p_outDir, p_fullPathToHeaderToMock, p_elem);
}
