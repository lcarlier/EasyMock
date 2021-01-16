#include "ComposableField.h"
#include "ComposableType.h"
#include "TypeItf.h"
#include "EasyMock_CType.h"
#include "Pointer.h"

#include <cassert>

ComposableField::ComposableField(const easyMock_cTypes_t p_ctype, std::string p_name) :
ComposableField(new CType(p_ctype), p_name)
{
}

ComposableField::ComposableField(TypeItf* p_type, std::string p_name) :
ComposableField(p_type, p_name, {.arraySize = -1})
{
}

ComposableField::ComposableField(TypeItf* p_type, std::string p_name, ComposableField::attributes p_attrib) :
ComposableFieldItf(p_type, p_name),
m_arraySize(p_attrib.arraySize)
{}

bool ComposableField::isIncompleteTypeField() const
{
  return m_type->isIncompleteType();
}

bool ComposableField::operator==(const ComposableField& other) const
{
  return this->isEqual(other);
}

bool ComposableField::isEqual(const Declarator& p_other) const
{
  const bool parentEq = ComposableFieldItf::isEqual(p_other);
  const ComposableField* otherField = dynamic_cast<const ComposableField*>(&p_other);
  if(!otherField)
  {
    return false;
  }
  const bool arraySizeEqual = this->m_arraySize == otherField->m_arraySize;

  return parentEq && arraySizeEqual;
}

bool ComposableField::operator!=(const ComposableField& other) const
{
  return (*this == other) == false;
}

bool ComposableField::isComposableField() const
{
  return true;
}

bool ComposableField::isArray() const
{
  return !(m_arraySize < 0);
}

bool ComposableField::isBoundSpecifiedArray() const
{
  return isArray() && m_arraySize > 0;
}

bool ComposableField::isUnboundSpecifiedArray() const
{
  return isArray() && m_arraySize == 0;
}

bool ComposableField::setArraySize(uint64_t size)
{
  m_arraySize = size;

  return true;
}

int64_t ComposableField::getArraySize() const
{
  return m_arraySize;
}

ComposableField* ComposableField::clone() const
{
  return new ComposableField(*this);
}

ComposableField::~ComposableField()
{}
