#include "ComposableType.h"

#include <boost/algorithm/string/replace.hpp>

size_t ComposableType::m_unique_hash = 0;
unsigned int ComposableType::m_number_of_anonymous_composable_type = 0;

ComposableType::ComposableType(const std::string p_name, bool p_is_embedded_in_other_type) :
ComposableType(p_name, ComposableField::Vector({}), p_is_embedded_in_other_type)
{
}

ComposableType::ComposableType(const std::string p_name, const std::string p_type_def_name, bool p_is_embedded_in_other_type) :
ComposableType(p_name, p_type_def_name, ComposableField::Vector({}), p_is_embedded_in_other_type)
{
}

ComposableType::ComposableType(const std::string p_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type) :
ComposableType(p_name, "", p_elem, p_is_embedded_in_other_type)
{
}

ComposableType::ComposableType(const std::string p_name, const std::string p_typed_def_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type) :
TypeItf(p_name, p_typed_def_name), m_elem(p_elem), m_is_embedded_in_other_type(p_is_embedded_in_other_type), m_anonymous_number(-1)
{
  if(this->isAnonymous())
  {
    this->m_anonymous_number = m_number_of_anonymous_composable_type;
    m_number_of_anonymous_composable_type++;
  }
}

ComposableType::ComposableType(const ComposableType& other) :
TypeItf({.name = other.m_name, .typed_def_name = other.m_typed_def_name,
        .isCType = other.m_isCType, .isStruct = other.m_isStruct, .isUnion = other.m_isUnion
        }),
        m_elem(other.m_elem), m_is_embedded_in_other_type(other.m_is_embedded_in_other_type), m_anonymous_number(other.m_anonymous_number)
{
  correctRecursiveType(this, &other);
}

ComposableType & ComposableType::operator=(const ComposableType& other)
{
  TypeItf::operator=(other);
  m_elem = other.m_elem;
  m_is_embedded_in_other_type = other.m_is_embedded_in_other_type;
  m_anonymous_number = other.m_anonymous_number;
  correctRecursiveType(this, &other);

  return *this;
}

ComposableType::ComposableType(ComposableType&& other) :
TypeItf(static_cast<TypeItf&&>(other))
{
  m_elem = std::move(other.m_elem);
  m_is_embedded_in_other_type = std::move(other.m_is_embedded_in_other_type);
  m_anonymous_number = std::move(other.m_anonymous_number);
  correctRecursiveType(this, &other);
}

const std::string ComposableType::getUniqueName() const
{
  std::string uniqueName = this->getFullDeclarationName();
  boost::replace_all(uniqueName, " ", ""); //Remove the ' ' character if any

  if(this->isAnonymous())
  {
    uniqueName.append("_anonymous_type_in_file_");
    uniqueName.append(std::to_string(m_unique_hash));
    uniqueName.append("_number_");
    uniqueName.append(std::to_string(m_number_of_anonymous_composable_type));
  }

  return uniqueName;
}

bool ComposableType::isAnonymous() const
{
  return this->getName().empty() && this->getTypedDefName().empty();
}

bool ComposableType::isEmbeddedInOtherType() const
{
  return m_is_embedded_in_other_type;
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
  bool embedEq = this->m_is_embedded_in_other_type == other.m_is_embedded_in_other_type;
  bool anonEq = this->m_anonymous_number == other.m_anonymous_number;
  return parentEq && elemEq && embedEq && anonEq;
}

bool ComposableType::operator!=(const ComposableType& other) const
{
  return (*this == other) == false;
}

ComposableField::Vector& ComposableType::getContainedFields()
{
  return const_cast<ComposableField::Vector &>(static_cast<const ComposableType &>(*this).getContainedFields());
}

const ComposableField::Vector& ComposableType::getContainedFields() const
{
  return m_elem;
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

