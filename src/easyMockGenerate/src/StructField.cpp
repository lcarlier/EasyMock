#include "StructField.h"
#include "StructType.h"
#include "TypeItf.h"
#include "CType.h"

StructField::StructField(const easyMock_cTypes_t p_ctype, std::string p_name) :
StructField(new CType(p_ctype), p_name, {.isPointer = false, .isArray = false, .arraySize = 0, .isRecursiveTypeField = false})
{
}

StructField::StructField(TypeItf* p_type, std::string p_name) :
StructField(p_type, p_name, {.isPointer = false, .isArray = false, .arraySize = 0, .isRecursiveTypeField = false})
{ }

StructField::StructField(TypeItf* p_type, std::string p_name, StructField::attributes p_attrib) :
Declarator(nullptr, p_attrib.isPointer),
m_name(p_name),
m_recursiveType(nullptr),
m_isArray(p_attrib.isArray),
m_arraySize(p_attrib.arraySize)
{
  if(p_attrib.isRecursiveTypeField)
  {
    //If type is recursive, make a shadow copy that will not be deleted
    m_recursiveType = static_cast<const StructType*>(p_type);
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
  m_isArray = other.m_isArray;
  m_arraySize = other.m_arraySize;
}

void StructField::updateRecursiveTypePtr(const StructType* newPtr, const StructType* toReplace)
{
  if(m_recursiveType == toReplace)
  {
    m_recursiveType = newPtr;
  }
  else if(m_type && m_type->isStruct())
  {
    //I'm a friend of StructType :)
    static_cast<StructType*>(m_type)->correctRecursiveType(newPtr, toReplace);
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
  std::swap(first.m_isArray, second.m_isArray);
  std::swap(first.m_arraySize, second.m_arraySize);
}

/*
 * For recursive field, we consider them equal if they have the same
 * m_recursiveType attribute set. If we don't do that we get an
 * infinite loop when comparing the structure
 */
bool StructField::operator==(const StructField& other) const
{
  bool commonVal = Declarator::operator ==(other) &&
                   this->m_name == other.m_name &&
                   this->m_isArray == other.m_isArray &&
                   this->m_arraySize == other.m_arraySize;
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
    m_recursiveType = static_cast<const StructType*>(type);
  }
  else
  {
    Declarator::setType(type);
  }
}

bool StructField::isArray() const
{
  return m_isArray;
}

bool StructField::isBoundSpecifiedArray() const
{
  return m_isArray && m_arraySize > 0;
}

bool StructField::isUnboundSpecifiedArray() const
{
  return m_isArray && m_arraySize == 0;
}

bool StructField::setArray(bool value)
{
  m_isArray = value;
  m_arraySize = 0;

  return true;
}

bool StructField::setArraySize(uint64_t size)
{
  if(!m_isArray)
  {
    return false;
  }
  m_arraySize = size;

  return true;
}

uint64_t StructField::getArraySize() const
{
  if(!m_isArray)
  {
    return 0;
  }
  return m_arraySize;
}

StructField* StructField::clone() const
{
  return new StructField(*this);
}

StructField::~StructField()
{
}
