#include <CodeGeneratorItf.h>

void CodeGeneratorItf::setMockOnlyFunction(const MockOnlyList& list)
{
  this->m_mockOnlyList = list;
}

void CodeGeneratorItf::setGenerateUsedType(bool value)
{
  this->m_generateUsedType = value;
}
