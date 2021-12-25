#include "Pointer.h"
#include "QualifiedType.h"
#include "FunctionType.h"

#include <boost/functional/hash.hpp>

Pointer::Pointer(std::shared_ptr<TypeItf> p_type):
TypeItf{""},
m_pointedType{std::move(p_type)},
m_cachedHash{0}
{
  this->setPointer(true);
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
  return m_pointedType.get();
}

TypeItf* Pointer::getPointedType()
{
  return const_cast<TypeItf*>(static_cast<const Pointer &>(*this).getPointedType());
}

bool Pointer::setPointedType(std::shared_ptr<TypeItf> newPointedType)
{
  m_pointedType = std::move(newPointedType);
  return true;
}

std::size_t Pointer::getHash() const noexcept
{
  if(m_cachedHash != 0)
  {
    return m_cachedHash;
  }
  std::size_t seed { TypeItf::getHash() };
  boost::hash_combine(seed, *m_pointedType);

  return seed;
}

void Pointer::cacheHash() noexcept
{
  m_cachedHash = 0;
  TypeItf::cacheHash();
  m_pointedType->cacheHash();
  m_cachedHash = Pointer::getHash();
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
  return m_pointedType.get();
}

Pointer::~Pointer()
{
}
