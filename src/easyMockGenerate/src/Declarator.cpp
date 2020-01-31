#include "Declarator.h"
#include "TypeItf.h"

#include <utility>
#include <stddef.h>

Declarator::Declarator() :
Declarator(nullptr, false)
{
}

Declarator::Declarator(TypeItf* typeItf, bool isPointer) :
m_type(typeItf), m_isPointer(isPointer)
{
}

Declarator::Declarator(const Declarator& other) :
m_type(other.m_type ? other.m_type->clone(): nullptr), m_isPointer(other.m_isPointer)
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

bool Declarator::isPointer() const
{
  return m_isPointer;
}

bool Declarator::setPointer(bool value)
{
  m_isPointer = value;

  return true;
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
  return typeMatch && this->m_isPointer == other.m_isPointer;
}

bool Declarator::operator!=(const Declarator& other) const
{
  return (*this != other);
}

void swap(Declarator &first, Declarator &second)
{
  std::swap(first.m_type, second.m_type);
  std::swap(first.m_isPointer, second.m_isPointer);
}
