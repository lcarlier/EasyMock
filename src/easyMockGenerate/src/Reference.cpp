#include "Reference.h"

Reference::Reference(std::shared_ptr<TypeItf> p_type): Pointer(std::move(p_type))
{
  this->setPointer(false);
  this->setReference(true);
}

std::string Reference::getDeclarationPrefix(bool p_naked) const
{
  return m_pointedType->getDeclarationPrefix(p_naked) + std::string { "&" };
}

bool Reference::isEqual(const TypeItf& p_other) const
{
  bool parentEq = TypeItf::isEqual(p_other);
  if(!parentEq)
  {
    return false;
  }
  if(!p_other.isReference())
  {
    return false;
  }
  const Reference& other = static_cast<const Reference&>(p_other);

  bool typeEqual = *this->m_pointedType == *other.m_pointedType;

  return typeEqual;
}
