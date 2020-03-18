#include "ComposableType.h"

ComposableType::ComposableType(const std::string p_name) :
ComposableType(p_name, ComposableField::Vector({}))
{
}

ComposableType::ComposableType(const std::string p_name, const std::string p_type_def_name) :
ComposableType(p_name, p_type_def_name, {})
{
}

ComposableType::ComposableType(const std::string p_name, const ComposableField::Vector p_elem) :
ComposableType(p_name, "", p_elem)
{
}

ComposableType::ComposableType(const std::string p_name, const std::string p_typed_def_name, const ComposableField::Vector p_elem) :
TypeItf(p_name, p_typed_def_name), m_elem(p_elem)
{
}

ComposableType::ComposableType(const ComposableType& other) :
TypeItf({.name = other.m_name, .typed_def_name = other.m_typed_def_name,
        .isCType = other.m_isCType, .isStruct = other.m_isStruct, .isUnion = other.m_isUnion
        }),
        m_elem(other.m_elem)
{
  correctRecursiveType(this, &other);
}

ComposableType & ComposableType::operator=(const ComposableType& other)
{
  TypeItf::operator=(other);
  m_elem = other.m_elem;
  correctRecursiveType(this, &other);

  return *this;
}

ComposableType::ComposableType(ComposableType&& other) :
TypeItf(static_cast<TypeItf&&>(other))
{
  m_elem = std::move(other.m_elem);
  correctRecursiveType(this, &other);
}

bool ComposableType::operator==(const ComposableType& other) const
{
  return this->isEqual(other);
}

bool ComposableType::isEqual(const TypeItf& p_other) const
{
  const ComposableType& other = static_cast<const ComposableType&>(p_other);
  bool parentEq = TypeItf::isEqual(p_other);
  if(!parentEq)
  {
    /*
     * If parent is not equal returns false directly
     * It prevent also issue that if the other struct doesn't have elements,
     * we do not try to go out of bounds of the object memory to check the size
     * of the Autoclean vector
     */
    return false;
  }
  bool elemEq = this->m_elem == other.m_elem;
  return parentEq && elemEq;
}

bool ComposableType::operator!=(const ComposableType& other) const
{
  return (*this == other) == false;
}

const ComposableField::Vector* ComposableType::getContainedFields() const
{
  return &m_elem;
}

void ComposableType::addStructField(ComposableField* newField)
{
  m_elem.push_back(newField);
}

void ComposableType::correctRecursiveType(const ComposableType *newPtr, const ComposableType* toReplace)
{
  for (ComposableField::Vector::iterator it = m_elem.begin(); it != m_elem.end(); ++it)
  {
    ComposableField *curField = *it;
    curField->updateRecursiveTypePtr(newPtr, toReplace);
  }
}

ComposableType::~ComposableType() { }

