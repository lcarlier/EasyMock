#include "StructType.h"

StructType::StructType(const std::string p_name) :
StructType(p_name, {})
{
}

StructType::StructType(const std::string p_name, const StructField::Vector p_elem) :
TypeItf(p_name), m_elem(p_elem)
{
}

StructType::StructType(const StructType& other) :
StructType(other.m_name, other.m_elem)
{
  correctRecursiveType(this);
}

StructType & StructType::operator=(const StructType& other)
{
  TypeItf::operator=(other);
  m_elem = other.m_elem;
  correctRecursiveType(this);

  return *this;
}

StructType::StructType(StructType&& other) :
TypeItf(static_cast<TypeItf&&>(other))
{
  m_elem = std::move(other.m_elem);
  correctRecursiveType(this);
}

bool StructType::operator==(const StructType& other) const
{
  return this->isEqual(other);
}

bool StructType::isEqual(const TypeItf& p_other) const
{
  const StructType& other = static_cast<const StructType&>(p_other);
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

bool StructType::operator!=(const StructType& other) const
{
  return (*this == other) == false;
}

StructType* StructType::clone() const
{
  return new StructType(*this);
}

const StructField::Vector* StructType::getContainedFields() const
{
  return &m_elem;
}

void StructType::addStructField(StructField* newField)
{
  m_elem.push_back(newField);
}


bool StructType::isStruct() const
{
  return true;
}

void StructType::correctRecursiveType(StructType *type)
{
  for (StructField::Vector::iterator it = m_elem.begin(); it != m_elem.end(); ++it)
  {
    StructField *curField = *it;
    curField->updateRecursiveTypePtr(type);
  }
}

StructType::~StructType() { }

