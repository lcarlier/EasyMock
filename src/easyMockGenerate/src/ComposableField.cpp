#include "ComposableField.h"
#include "ComposableType.h"
#include "TypeItf.h"
#include "CType.h"
#include "Pointer.h"

#include <cassert>

namespace
{
  Pointer* cloneMostDereferencedPointer(Pointer* p)
  {
    p->setIncompleteTypePointer(true);
    TypeItf *pointedType = p->getPointedType();
    p->setPointedType(pointedType->clone());
    if(pointedType->isPointer())
    {
      Pointer *ptrToPtr = dynamic_cast<Pointer *>(pointedType);
      cloneMostDereferencedPointer(ptrToPtr);
      delete(ptrToPtr);
    }
    return p;
  }
}

ComposableField::ComposableField(const easyMock_cTypes_t p_ctype, std::string p_name) :
ComposableField(new CType(p_ctype), p_name, ComposableField::attributes(
{
  .arraySize = -1,
  .isIncompleteTypeField = false
}))
{
}

ComposableField::ComposableField(TypeItf* p_type, std::string p_name) :
ComposableField(p_type, p_name, {.arraySize = -1, .isIncompleteTypeField = false})
{
}

ComposableField::ComposableField(TypeItf* p_type, std::string p_name, ComposableField::attributes p_attrib) :
Declarator(nullptr), //is set later
m_name(p_name),
m_incompleteType(nullptr),
m_arraySize(p_attrib.arraySize)
{
  if(p_attrib.isIncompleteTypeField)
  {
    if(!p_type->isPointer())
    {
      fprintf(stderr, "Error in calling building ComposableField with non Pointer type and incomplete attribute");
      assert(false);
    }
    /*
     * We keep the pointer object but we make a copy of the pointed type.
     * This means that the pointed object must at least contains the type name
     * and its typed def if any. This is not the purpose that we can go
     * recursively to the pointed type fields via this attribute.
     *
     * TODO: use a more specific class to store m_incompleteType
     */
    Pointer *p = dynamic_cast<Pointer*>(p_type);
    m_incompleteType = cloneMostDereferencedPointer(p);
    Declarator::setDeclareString(m_incompleteType->getFullDeclarationName());
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
  m_incompleteType = other.m_incompleteType ? other.m_incompleteType->clone() : nullptr;
  m_arraySize = other.m_arraySize;
}

ComposableField::ComposableField(ComposableField&& other):
Declarator(other),
m_incompleteType(nullptr)
{
  swap(*this, other);
}

void ComposableField::updateIncompleteTypePtr(ComposableType* newPtr, const ComposableType* toReplace)
{
  if(m_incompleteType && m_incompleteType->getPointedType() == toReplace)
  {
    if(!m_incompleteType->setPointedType(newPtr))
    {
      fprintf(stderr, "BUG IN EASYMOCK. Contact the owner for the bug fix");
      assert(false);
    }
  }
  else if(m_type && m_type->isComposableType())
  {
    //I'm a friend of ComposableType :)
    static_cast<ComposableType*>(m_type)->correctIncompleteType(newPtr, toReplace);
  }
}

bool ComposableField::isIncompleteTypeField() const
{
  return m_incompleteType != nullptr;
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
  std::swap(first.m_incompleteType, second.m_incompleteType);
  std::swap(first.m_arraySize, second.m_arraySize);
}

/*
 * For incomplete field, we consider them equal if they have the pointed
 * type name is the same. If we don't do that we could get an
 * infinite loop when comparing the ComposableField object because the
 * the field could refer to a type which contains itself
 */
bool ComposableField::operator==(const ComposableField& other) const
{
  bool commonVal = Declarator::operator ==(other) &&
                   this->m_name == other.m_name &&
                   this->m_arraySize == other.m_arraySize;
  if(m_incompleteType)
  {
    return commonVal && other.m_incompleteType && m_incompleteType->getPointedType()->getName() == other.m_incompleteType->getPointedType()->getName();
  }
  else
  {
    //We know here this->m_incompleteType == nullptr
    return commonVal && other.m_incompleteType == nullptr;
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
  if(m_incompleteType)
  {
    return m_incompleteType;
  }
  else
  {
    return Declarator::getType();
  }
}

void ComposableField::setType(TypeItf* p_type)
{
  if(m_incompleteType)
  {
    delete m_incompleteType;
    m_incompleteType = dynamic_cast<Pointer*>(p_type);
    if(!m_incompleteType)
    {
      fprintf(stderr, "Error in calling setType with non Pointer type and incomplete attribute");
      assert(false);
    }
    m_incompleteType->setIncompleteTypePointer(false);
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
  if(m_incompleteType)
  {
    delete m_incompleteType;
  }
}
