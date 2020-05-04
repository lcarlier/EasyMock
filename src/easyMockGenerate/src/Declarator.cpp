#include "Declarator.h"
#include "TypeItf.h"

#include <utility>
#include <stddef.h>

Declarator::Declarator() :
Declarator(nullptr)
{
}

Declarator::Declarator(TypeItf* typeItf) :
m_type(typeItf), m_declaredString("")
{
  if(m_type)
  {
    m_declaredString = typeItf->getFullDeclarationName();
  }
}

Declarator::Declarator(const Declarator& other) :
m_type(other.m_type ? other.m_type->clone(): nullptr), m_declaredString(other.m_declaredString)
{
}

Declarator::Declarator(Declarator&& other)
{
  swap(*this, other);
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
  m_type = type;
  m_declaredString.clear();
  if(m_type)
  {
    m_declaredString = m_type->getFullDeclarationName();
  }
}

const std::string& Declarator::getTypeName() const
{
  return m_type->getName();
}

void Declarator::setDeclareString(const std::string& newString)
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
}

const std::string& Declarator::getDeclareString() const
{
  return m_declaredString;
}

bool Declarator::operator==(const Declarator& other) const
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
  return (*this != other);
}

void swap(Declarator &first, Declarator &second)
{
  std::swap(first.m_type, second.m_type);
  std::swap(first.m_declaredString, second.m_declaredString);
}
