#include "Pointer.h"

Pointer::Pointer(TypeItf *p_type, bool p_isConst):
Pointer(p_type, "", p_isConst)
{
}

Pointer::Pointer(TypeItf *p_type,  const std::string p_type_def_name, bool p_isConst):
TypeItf("", p_type_def_name), m_pointedType(p_type), m_isIncompletePointerType(false)
{
  this->setConst(p_isConst);
  this->setPointer(true);
}

Pointer::Pointer(const Pointer& other):
TypeItf(other)
{
  m_pointedType = other.m_pointedType->clone();
  m_isIncompletePointerType = other.m_isIncompletePointerType;
}

Pointer::Pointer(Pointer &&other):
TypeItf(other), m_pointedType(nullptr), m_isIncompletePointerType(false)
{
  swap(*this, other);
}

Pointer& Pointer::operator=(Pointer other)
{
  TypeItf::operator=(other);
  swap(*this, other);

  return *this;
}

bool Pointer::operator==(const Pointer& other) const
{
  return this->isEqual(other);
}

bool Pointer::operator!=(const Pointer& other) const
{
  return !(*this == other);
}

const TypeItf* Pointer::getPointedType() const
{
  return m_pointedType;
}

TypeItf* Pointer::getPointedType()
{
  return const_cast<TypeItf*>(static_cast<const Pointer &>(*this).getPointedType());
}

bool Pointer::setPointedType(TypeItf* newPointedType)
{
  if(m_pointedType && !m_isIncompletePointerType)
  {
    delete m_pointedType;
    m_pointedType = nullptr;
  }
  m_pointedType = newPointedType;
  return true;
}

void Pointer::setIncompleteTypePointer(bool value)
{
  m_isIncompletePointerType = value;
}

void Pointer::swap(Pointer &first, Pointer &second)
{
  std::swap(first.m_pointedType, second.m_pointedType);
  std::swap(first.m_isIncompletePointerType, second.m_isIncompletePointerType);
}

bool Pointer::isEqual(const TypeItf& p_other) const
{
  bool parentEq = TypeItf::isEqual(p_other);
  if(!parentEq)
  {
    return false;
  }
  if(!p_other.isPointer())
  {
    return false;
  }
  const Pointer& other = static_cast<const Pointer&>(p_other);
  bool deletePointedTypeEqual = this->m_isIncompletePointerType == other.m_isIncompletePointerType;
  if(!deletePointedTypeEqual)
  {
    return false;
  }
  bool typeEqual;
  if(!this->m_isIncompletePointerType)
  {
    typeEqual = *this->m_pointedType == *other.m_pointedType;
  }
  else
  {
    typeEqual = this->getPointedType()->getMostDefinedName() == other.getPointedType()->getMostDefinedName();
  }

  return deletePointedTypeEqual && typeEqual;
}

Pointer* Pointer::clone() const
{
  return new Pointer(*this);
}

Pointer::~Pointer()
{
  delete m_pointedType;
}
