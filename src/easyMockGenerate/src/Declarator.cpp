#include "Declarator.h"
#include "TypeItf.h"
#include "Pointer.h"
#include "FunctionType.h"

#include <utility>
#include <cstddef>

#include <boost/functional/hash.hpp>

Declarator::Declarator(std::shared_ptr<TypeItf> typeItf) :
m_type { std::move(typeItf) },
m_declaredString { "" },
m_cachedHash{0}
{
  if(m_type)
  {
    m_declaredString = m_type->getDeclarationPrefix();
  }
}

Declarator::~Declarator()
{
}

TypeItf* Declarator::getType()
{
  return const_cast<TypeItf*>(static_cast<const Declarator &>(*this).getType());
}

const TypeItf* Declarator::getType() const noexcept
{
  return m_type.get();
}

Declarator& Declarator::setDeclareString(const std::string& newString)
{
  if(!newString.empty())
  {
    this->m_declaredString = newString;
  }
  /*
   * This case is for anonymous type. LLVM returns an empty string.
   */
  else if(this->m_type)
  {
    this->m_declaredString = this->m_type->getFullDeclarationName();
  }

  return *this;
}

std::string Declarator::getDeclareString() const
{
  if (!m_declaredString.empty())
  {
    return m_declaredString;
  }
  if (m_type)
  {
    return m_type->getDeclarationPrefix();
  }
  return "";
}

bool Declarator::operator==(const Declarator& other) const
{
  return this->isEqual(other);
}

std::size_t Declarator::getHash() const noexcept
{
  if(m_cachedHash != 0)
  {
    return m_cachedHash;
  }
  std::size_t seed { 0 };
  boost::hash_combine(seed, m_declaredString);
  boost::hash_combine(seed, *m_type);

  return seed;
}

void Declarator::cacheHash() noexcept
{
  m_cachedHash = 0;
  m_type->cacheHash();
  m_cachedHash = Declarator::getHash();
}

bool Declarator::isEqual(const Declarator& other) const
{
  bool typeMatch = false;
  if(this->m_type == nullptr && other.m_type == nullptr)
  {
    typeMatch = true;
  }
  else if(this->m_type == nullptr)
  {
    typeMatch = false;
  }
  else if(other.m_type == nullptr)
  {
    typeMatch = false;
  }
  else if(*this->m_type == *other.m_type)
  {
    typeMatch = true;
  }
  bool declareStringMatch = this->m_declaredString == other.m_declaredString;
  return typeMatch && declareStringMatch;
}

bool Declarator::operator!=(const Declarator& other) const
{
  return !(*this == other);
}
