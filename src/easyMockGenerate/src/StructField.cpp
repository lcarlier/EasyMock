#include "StructField.h"
#include "StructType.h"
#include "TypeItf.h"
#include "CType.h"

StructField::StructField(const easyMock_cTypes_t p_ctype, std::string p_name) :
StructField(new CType(p_ctype), p_name, false)
{
}

StructField::StructField(TypeItf* p_type, std::string p_name) :
StructField(p_type, p_name, false)
{ }

StructField::StructField(TypeItf* p_type, std::string p_name, bool p_recursiveTypeField) :
Declarator(nullptr, false),
m_name(p_name),
m_recursiveType(nullptr)
{
  if(p_recursiveTypeField)
  {
    m_recursiveType = p_type;
  }
  else
  {
    Declarator::setType(p_type);
  }
}

StructField::StructField(const StructField& other) :
Declarator(other)
{
  m_name = other.m_name;
  m_recursiveType = other.m_recursiveType;
}

void StructField::updateRecursiveTypePtr(StructType* ptr)
{
  if(m_recursiveType)
  {
    m_recursiveType = ptr;
  }
  else if(m_type && m_type->isStruct())
  {
    //I'm a friend of StructType :)
    static_cast<StructType*>(m_type)->correctRecursiveType(ptr);
  }
}

bool StructField::isRecursiveTypeField() const
{
  return m_recursiveType != nullptr;
}


StructField& StructField::operator=(StructField other)
{
  swap(*this, other);

  return *this;
}

StructField::StructField(StructField&& other)
{
  swap(*this, other);
}

void swap(StructField &first, StructField &second)
{
  swap(static_cast<Declarator&>(first), static_cast<Declarator&>(second));
  std::swap(first.m_name, second.m_name);
  std::swap(first.m_recursiveType, second.m_recursiveType);
}

/*
 * For recursive field, we consider them equal if they have the same
 * m_recursiveType attribute set. If we don't do that we get an
 * infinite loop when comparing the structure
 */
bool StructField::operator==(const StructField& other) const
{
  bool commonVal = Declarator::operator ==(other) && this->m_name == other.m_name;
  if(m_recursiveType)
  {
    return commonVal && other.m_recursiveType && m_recursiveType->getName() == other.m_recursiveType->getName();
  }
  else
  {
    //We know here this->m_recursiveType == nullptr
    return commonVal && other.m_recursiveType == nullptr;
  }
}

bool StructField::operator!=(const StructField& other) const
{
  return (*this == other) == false;
}

const std::string& StructField::getName() const
{
  return m_name;
}

const TypeItf* StructField::getType() const
{
  if(m_recursiveType)
  {
    return m_recursiveType;
  }
  else
  {
    return Declarator::getType();
  }
}

void StructField::setType(TypeItf* type)
{
  if(m_recursiveType)
  {
    m_recursiveType = type;
  }
  else
  {
    Declarator::setType(type);
  }
}

StructField* StructField::clone() const
{
  return new StructField(*this);
}

StructField::~StructField()
{
}
