#include "Pointer.h"
#include "QualifiedType.h"
#include "FunctionType.h"

#include <cassert>

Pointer::Pointer(TypeItf *p_type):
TypeItf(""), m_pointedType(p_type)
{
  this->setPointer(true);
}

Pointer::Pointer(const Pointer& other):
TypeItf(other)
{
  m_pointedType = other.m_pointedType->clone();
}

Pointer::Pointer(Pointer &&other):
TypeItf(other), m_pointedType(nullptr)
{
  swap(*this, other);
}

Pointer& Pointer::operator=(Pointer other)
{
  TypeItf::operator=(other);
  swap(*this, other);

  return *this;
}

bool Pointer::operator==(const TypeItf& other) const
{
  return this->isEqual(other);
}

bool Pointer::operator!=(const TypeItf& other) const
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
  if(m_pointedType)
  {
    delete m_pointedType;
    m_pointedType = nullptr;
  }
  m_pointedType = newPointedType;
  return true;
}

void Pointer::swap(Pointer &first, Pointer &second)
{
  std::swap(first.m_pointedType, second.m_pointedType);
}

std::size_t Pointer::getHash() const
{
  std::size_t seed { TypeItf::getHash() };
  boost::hash_combine(seed, *m_pointedType);

  return seed;
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

  bool typeEqual = *this->m_pointedType == *other.m_pointedType;

  return typeEqual;
}

std::string Pointer::getDeclarationPrefix(bool p_naked) const
{
  return m_pointedType->getDeclarationPrefix(p_naked) + std::string { "*" };
}

TypeItf* Pointer::getMostPointedType() const
{
  const Pointer* ptrType = m_pointedType->asPointer();
  if(ptrType)
  {
    return ptrType->getMostPointedType();
  }
  return m_pointedType;
}

Pointer* Pointer::clone() const
{
  return new Pointer(*this);
}

Pointer::~Pointer()
{
  delete m_pointedType;
}
