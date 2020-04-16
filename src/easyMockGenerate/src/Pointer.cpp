#include "Pointer.h"

Pointer::Pointer(TypeItf *type, bool isConst):
m_pointedType(type), m_deletePointedTypeOnDelete(true)
{
  this->setConst(isConst);
  this->setPointer(true);
}

Pointer::Pointer(const Pointer& other):
TypeItf(other)
{
  if(other.m_pointedType && other.m_deletePointedTypeOnDelete)
  {
    m_pointedType = other.m_pointedType->clone();
  }
  else
  {
    m_pointedType = other.m_pointedType;
  }
  m_deletePointedTypeOnDelete = other.m_deletePointedTypeOnDelete;
}

Pointer::Pointer(Pointer &&other):
m_pointedType(nullptr), m_deletePointedTypeOnDelete(true)
{
  swap(*this, other);
}

Pointer& Pointer::operator=(Pointer other)
{
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
  if(m_deletePointedTypeOnDelete)
  {
    return false;
  }
  m_pointedType = newPointedType;
  return true;
}

void Pointer::setDeletePointedTypeOnDelete(bool value)
{
  m_deletePointedTypeOnDelete = value;
}

void Pointer::swap(Pointer &first, Pointer &second)
{
  std::swap(first.m_pointedType, second.m_pointedType);
  std::swap(first.m_deletePointedTypeOnDelete, second.m_deletePointedTypeOnDelete);
}

bool Pointer::isEqual(const TypeItf& p_other) const
{
  if(!p_other.isPointer())
  {
    return false;
  }
  const Pointer& other = static_cast<const Pointer&>(p_other);
  bool deletePointedTypeEqual = this->m_deletePointedTypeOnDelete == other.m_deletePointedTypeOnDelete;
  if(!deletePointedTypeEqual)
  {
    return false;
  }
  bool typeEqual;
  if(this->m_deletePointedTypeOnDelete)
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
  if(m_deletePointedTypeOnDelete)
  {
    delete m_pointedType;
  }
}

