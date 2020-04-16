#include "ComposableField.h"
#include "ComposableType.h"
#include "TypeItf.h"
#include "CType.h"
#include "Pointer.h"

#include <cassert>

ComposableField::ComposableField(const easyMock_cTypes_t p_ctype, std::string p_name) :
ComposableField(new CType(p_ctype), p_name, ComposableField::attributes(
{
  .isArray = false,
  .arraySize = 0,
  .isRecursiveTypeField = false
}))
{
}

ComposableField::ComposableField(TypeItf* p_type, std::string p_name) :
ComposableField(p_type, p_name, {.isArray = false, .arraySize = 0, .isRecursiveTypeField = false})
{
}

ComposableField::ComposableField(TypeItf* p_type, std::string p_name, ComposableField::attributes p_attrib) :
Declarator(nullptr), //is set later
m_name(p_name),
m_recursiveType(nullptr),
m_isArray(p_attrib.isArray),
m_arraySize(p_attrib.arraySize)
{
  if(p_attrib.isRecursiveTypeField)
  {
    //If type is recursive, keep it's pointer only. It doesn't need to be deleted
    m_recursiveType = dynamic_cast<Pointer*>(p_type);
    if(!m_recursiveType)
    {
      fprintf(stderr, "Error in calling building ComposableField with non Pointer type and recursive attribute");
      assert(false);
    }
    m_recursiveType->setDeletePointedTypeOnDelete(false);
  }
  else
  {
    Declarator::setType(p_type);
  }
}

ComposableField::ComposableField(const ComposableField& other) :
Declarator(other)
{
  m_name = other.m_name;
  m_recursiveType = other.m_recursiveType ? other.m_recursiveType->clone() : nullptr;
  m_isArray = other.m_isArray;
  m_arraySize = other.m_arraySize;
}

ComposableField::ComposableField(ComposableField&& other):
m_recursiveType(nullptr)
{
  swap(*this, other);
}

void ComposableField::updateRecursiveTypePtr(ComposableType* newPtr, const ComposableType* toReplace)
{
  if(m_recursiveType && m_recursiveType->getPointedType() == toReplace)
  {
    if(!m_recursiveType->setPointedType(newPtr))
    {
      fprintf(stderr, "BUG IN EASYMOCK. Contact the owner for the bug fix");
      assert(false);
    }
  }
  else if(m_type && m_type->isComposableType())
  {
    //I'm a friend of ComposableType :)
    static_cast<ComposableType*>(m_type)->correctRecursiveType(newPtr, toReplace);
  }
}

bool ComposableField::isRecursiveTypeField() const
{
  return m_recursiveType != nullptr;
}


ComposableField& ComposableField::operator=(ComposableField other)
{
  swap(*this, other);

  return *this;
}

void swap(ComposableField &first, ComposableField &second)
{
  swap(static_cast<Declarator&>(first), static_cast<Declarator&>(second));
  std::swap(first.m_name, second.m_name);
  std::swap(first.m_recursiveType, second.m_recursiveType);
  std::swap(first.m_isArray, second.m_isArray);
  std::swap(first.m_arraySize, second.m_arraySize);
}

/*
 * For recursive field, we consider them equal if they have the pointed
 * type name is the same. If we don't do that we get an
 * infinite loop when comparing the ComposableField object
 */
bool ComposableField::operator==(const ComposableField& other) const
{
  bool commonVal = Declarator::operator ==(other) &&
                   this->m_name == other.m_name &&
                   this->m_isArray == other.m_isArray &&
                   this->m_arraySize == other.m_arraySize;
  if(m_recursiveType)
  {
    return commonVal && other.m_recursiveType && m_recursiveType->getPointedType()->getName() == other.m_recursiveType->getPointedType()->getName();
  }
  else
  {
    //We know here this->m_recursiveType == nullptr
    return commonVal && other.m_recursiveType == nullptr;
  }
}

bool ComposableField::operator!=(const ComposableField& other) const
{
  return (*this == other) == false;
}

const std::string& ComposableField::getName() const
{
  return m_name;
}

TypeItf* ComposableField::getType()
{
  return const_cast<TypeItf*>(static_cast<const ComposableField &>(*this).getType());
}

const TypeItf* ComposableField::getType() const
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

void ComposableField::setType(TypeItf* p_type)
{
  if(m_recursiveType)
  {
    delete m_recursiveType;
    m_recursiveType = dynamic_cast<Pointer*>(p_type);
    if(!m_recursiveType)
    {
      fprintf(stderr, "Error in calling setType with non Pointer type and recursive attribute");
      assert(false);
    }
    m_recursiveType->setDeletePointedTypeOnDelete(false);
  }
  else
  {
    Declarator::setType(p_type);
  }
}

bool ComposableField::isArray() const
{
  return m_isArray;
}

bool ComposableField::isBoundSpecifiedArray() const
{
  return m_isArray && m_arraySize > 0;
}

bool ComposableField::isUnboundSpecifiedArray() const
{
  return m_isArray && m_arraySize == 0;
}

bool ComposableField::isAnonymous() const
{
  return m_name.empty();
}

bool ComposableField::setArray(bool value)
{
  m_isArray = value;
  m_arraySize = 0;

  return true;
}

bool ComposableField::setArraySize(uint64_t size)
{
  if(!m_isArray)
  {
    return false;
  }
  m_arraySize = size;

  return true;
}

uint64_t ComposableField::getArraySize() const
{
  if(!m_isArray)
  {
    return 0;
  }
  return m_arraySize;
}

ComposableField* ComposableField::clone() const
{
  return new ComposableField(*this);
}

ComposableField::~ComposableField()
{
  if(m_recursiveType)
  {
    delete m_recursiveType;
  }
}
