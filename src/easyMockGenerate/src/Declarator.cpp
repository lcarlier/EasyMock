#include "Declarator.h"
#include "TypeItf.h"

#include <utility>
#include <stddef.h>

Declarator::Declarator() :
Declarator(nullptr)
{
}

Declarator::Declarator(TypeItf* typeItf) :
m_type(typeItf)
{
}

Declarator::Declarator(const Declarator& other) :
m_type(other.m_type ? other.m_type->clone(): nullptr)
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
}

const std::string& Declarator::getTypeName() const
{
  return m_type->getName();
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
  return typeMatch;
}

bool Declarator::operator!=(const Declarator& other) const
{
  return (*this != other);
}

void swap(Declarator &first, Declarator &second)
{
  std::swap(first.m_type, second.m_type);
}
