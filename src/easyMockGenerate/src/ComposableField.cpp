#include "ComposableField.h"
#include "ComposableType.h"
#include "TypeItf.h"
#include "CType.h"
#include "Pointer.h"

#include <cassert>

namespace
{
  Pointer* recurClonePointer(Pointer* p)
  {
    p->setRecursivePointer(true);
    TypeItf *pointedType = p->getPointedType();
    p->setPointedType(pointedType->clone());
    if(pointedType->isPointer())
    {
      Pointer *ptrToPtr = dynamic_cast<Pointer *>(pointedType);
      recurClonePointer(ptrToPtr);
      delete(ptrToPtr);
    }
    return p;
  }
}

ComposableField::ComposableField(const easyMock_cTypes_t p_ctype, std::string p_name) :
ComposableField(new CType(p_ctype), p_name, ComposableField::attributes(
{
  .arraySize = -1,
  .isRecursiveTypeField = false
}))
{
}

ComposableField::ComposableField(TypeItf* p_type, std::string p_name) :
ComposableField(p_type, p_name, {.arraySize = -1, .isRecursiveTypeField = false})
{
}

ComposableField::ComposableField(TypeItf* p_type, std::string p_name, ComposableField::attributes p_attrib) :
Declarator(nullptr), //is set later
m_name(p_name),
m_recursiveType(nullptr),
m_arraySize(p_attrib.arraySize)
{
  if(p_attrib.isRecursiveTypeField)
  {
    if(!p_type->isPointer())
    {
      fprintf(stderr, "Error in calling building ComposableField with non Pointer type and recursive attribute");
      assert(false);
    }
    /*
     * We keep the pointer object but we make a copy of the pointed type.
     * This means that the pointed object must at least contains the type name
     * and its typed def if any. This is not the purpose that we can go
     * recursively to the pointed type fields via this attribute.
     *
     * TODO: use a more specific class to store m_recursiveType
     */
    Pointer *p = dynamic_cast<Pointer*>(p_type);
    TypeItf *pointedType = p->getPointedType();
    m_recursiveType = recurClonePointer(p);
    Declarator::setDeclareString(m_recursiveType->getFullDeclarationName());
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
  m_arraySize = other.m_arraySize;
}

ComposableField::ComposableField(ComposableField&& other):
Declarator(other),
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
    m_recursiveType->setRecursivePointer(false);
  }
  else
  {
    Declarator::setType(p_type);
  }
}

bool ComposableField::isArray() const
{
  return !(m_arraySize < 0);
}

bool ComposableField::isBoundSpecifiedArray() const
{
  return isArray() && m_arraySize > 0;
}

bool ComposableField::isUnboundSpecifiedArray() const
{
  return isArray() && m_arraySize == 0;
}

bool ComposableField::isAnonymous() const
{
  return m_name.empty();
}

bool ComposableField::setArraySize(uint64_t size)
{
  m_arraySize = size;

  return true;
}

int64_t ComposableField::getArraySize() const
{
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
