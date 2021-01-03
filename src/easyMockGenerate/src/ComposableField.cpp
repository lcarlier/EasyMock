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
Declarator(p_type),
m_name(p_name),
m_arraySize(p_attrib.arraySize)
{}

ComposableField::ComposableField(const ComposableField& other) :
Declarator(other)
{
  m_name = other.m_name;
  m_arraySize = other.m_arraySize;
}

ComposableField::ComposableField(ComposableField&& other):
Declarator(other)
{
  swap(*this, other);
}

bool ComposableField::isIncompleteTypeField() const
{
  return m_type->isIncompleteType();
}


ComposableField& ComposableField::operator=(ComposableField other)
{
  swap(*this, other);

  return *this;
}

void swap(ComposableField &first, ComposableField &second)
{
  swap(static_cast<Declarator&>(first), static_cast<Declarator&>(second));
  std::swap(first.m_name, second.m_name);
  std::swap(first.m_arraySize, second.m_arraySize);
}

bool ComposableField::operator==(const ComposableField& other) const
{
  const bool declaratorEqual = Declarator::operator ==(other);
  const bool nameEqual = this->m_name == other.m_name;
  const bool arraySizeEqual = this->m_arraySize == other.m_arraySize;

  return declaratorEqual && nameEqual && arraySizeEqual;
}

bool ComposableField::operator!=(const ComposableField& other) const
{
  return (*this == other) == false;
}

const std::string& ComposableField::getName() const
{
  return m_name;
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

bool ComposableField::isAnonymous() const
{
  return m_name.empty();
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
