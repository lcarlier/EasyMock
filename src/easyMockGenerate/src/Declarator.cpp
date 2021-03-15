#include "Declarator.h"
#include "TypeItf.h"
#include "Pointer.h"
#include "FunctionType.h"

#include <utility>
#include <cstddef>

#include <boost/functional/hash.hpp>

Declarator::Declarator(TypeItf* typeItf) :
m_type { typeItf }, m_declaredString { "" }
{
  if(m_type)
  {
    m_declaredString = m_type->getDeclarationPrefix();
  }
}

Declarator::Declarator(const Declarator& other) :
m_type(other.m_type ? other.m_type->clone(): nullptr), m_declaredString(other.m_declaredString)
{
}

Declarator::Declarator(Declarator&& other) :
m_type { nullptr }, m_declaredString {}
{
  swap(*this, other);
}

void Declarator::updateDeclareString()
{
  if(m_type)
  {
    const TypeItf *mostPointedType = m_type;
    const Pointer* pointerType = mostPointedType->asPointer();
    if(pointerType)
    {
      mostPointedType = pointerType->getMostPointedType();
    }
    const FunctionType* ft = dynamic_cast<const FunctionType*>(mostPointedType);
    if(ft)
    {
      m_declaredString = ft->getDeclarationPrefix();
    }
    else
    {
      m_declaredString = m_type->getFullDeclarationName();
    }
  }
}

Declarator& Declarator::operator=(Declarator other)
{
  swap(*this, other);

  return *this;
}

Declarator::~Declarator()
{
  delete m_type;
}

TypeItf* Declarator::getType()
{
  return const_cast<TypeItf*>(static_cast<const Declarator &>(*this).getType());
}

const TypeItf* Declarator::getType() const
{
  return m_type;
}

void Declarator::setType(TypeItf* type)
{
  if(m_type)
  {
    delete m_type;
  }
  m_type = type;
  m_declaredString.clear();
  updateDeclareString();
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

Declarator* Declarator::clone() const
{
  return new Declarator(*this);
}

bool Declarator::operator==(const Declarator& other) const
{
  return this->isEqual(other);
}

std::size_t Declarator::getHash() const
{
  std::size_t seed { 0 };
  boost::hash_combine(seed, m_declaredString);
  boost::hash_combine(seed, *m_type);

  return seed;
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

void swap(Declarator &first, Declarator &second)
{
  std::swap(first.m_type, second.m_type);
  std::swap(first.m_declaredString, second.m_declaredString);
}
