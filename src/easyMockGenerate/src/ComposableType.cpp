#include "ComposableType.h"

#include <boost/algorithm/string/replace.hpp>

size_t ComposableType::m_unique_hash = 0;
unsigned int ComposableType::m_number_of_anonymous_composable_type = 0;

ComposableType::ComposableType(const std::string p_name, bool p_is_embedded_in_other_type) :
ComposableType(p_name, ComposableFieldItf::Vector({}), p_is_embedded_in_other_type)
{
}

ComposableType::ComposableType(const std::string p_name, const std::string p_type_def_name, bool p_is_embedded_in_other_type) :
ComposableType(p_name, p_type_def_name, ComposableFieldItf::Vector({}), p_is_embedded_in_other_type)
{
}

ComposableType::ComposableType(const std::string p_name, const ComposableFieldItf::Vector p_elem, bool p_is_embedded_in_other_type) :
ComposableType(p_name, "", p_elem, p_is_embedded_in_other_type)
{
}

ComposableType::ComposableType(const std::string p_name, const std::string p_typed_def_name, const ComposableFieldItf::Vector p_elem, bool p_is_embedded_in_other_type) :
TypeItf(p_name, p_typed_def_name), m_elem(p_elem), m_is_declaration_embedded_in_other_type(p_is_embedded_in_other_type), m_anonymous_number(-1)
{
  if(this->isAnonymous())
  {
    assert(m_number_of_anonymous_composable_type >= 0);
    this->m_anonymous_number = m_number_of_anonymous_composable_type;
    m_number_of_anonymous_composable_type++;
  }
}

ComposableType::ComposableType(const ComposableType& other) :
TypeItf(other), m_elem(other.m_elem), m_is_declaration_embedded_in_other_type(other.m_is_declaration_embedded_in_other_type), m_anonymous_number(other.m_anonymous_number)
{}

ComposableType & ComposableType::operator=(const ComposableType& other)
{
  TypeItf::operator=(other);
  m_elem = other.m_elem;
  m_is_declaration_embedded_in_other_type = other.m_is_declaration_embedded_in_other_type;
  m_anonymous_number = other.m_anonymous_number;

  return *this;
}

ComposableType::ComposableType(ComposableType&& other) :
TypeItf(static_cast<TypeItf&&>(other))
{
  m_elem = std::move(other.m_elem);
  m_is_declaration_embedded_in_other_type = std::move(other.m_is_declaration_embedded_in_other_type);
  m_anonymous_number = std::move(other.m_anonymous_number);
}

void ComposableType::setFileHash(std::size_t hash)
{
  m_unique_hash = hash;
}

const std::string ComposableType::getUniqueName() const
{
  std::string uniqueName = this->getFullDeclarationName();
  /*
   * getFullDeclarationName is going to return 'struct ' or 'union ' if
   * the type is anonymous. So we replace the space with an underscore
   */
  boost::replace_all(uniqueName, " ", "_");

  if(this->isAnonymous())
  {
    uniqueName.append("_anonymous_type_in_file_");
    assert(m_unique_hash != 0);
    uniqueName.append(std::to_string(m_unique_hash));
    uniqueName.append("_number_");
    assert(m_anonymous_number >= 0);
    uniqueName.append(std::to_string(m_anonymous_number));
  }

  return uniqueName;
}

bool ComposableType::isDeclarationEmbeddedInOtherType() const
{
  return m_is_declaration_embedded_in_other_type;
}

bool ComposableType::operator==(const ComposableType& other) const
{
  return this->isEqual(other);
}

bool ComposableType::isEqual(const TypeItf& p_other) const
{
  bool parentEq = TypeItf::isEqual(p_other);
  if(!parentEq)
  {
    /*
     * If TypeItf is not equal returns false directly
     * It prevent the issue that if the other type is not a struct, i.e doesn't have elements,
     * we do not try to go out of bounds of the object memory to check the size
     * of the Autoclean vector which is not existing
     */
    return false;
  }
  const ComposableType& other = static_cast<const ComposableType&>(p_other);
  bool elemEq = this->m_elem == other.m_elem;
  bool embedEq = this->m_is_declaration_embedded_in_other_type == other.m_is_declaration_embedded_in_other_type;
  bool anonEq = this->m_anonymous_number == other.m_anonymous_number;
  return parentEq && elemEq && embedEq && anonEq;
}

bool ComposableType::operator!=(const ComposableType& other) const
{
  return (*this == other) == false;
}

ComposableFieldItf::Vector& ComposableType::getContainedFields()
{
  return const_cast<ComposableFieldItf::Vector &>(static_cast<const ComposableType &>(*this).getContainedFields());
}

const ComposableFieldItf::Vector& ComposableType::getContainedFields() const
{
  return m_elem;
}

void ComposableType::addField(ComposableFieldItf* newField)
{
  m_elem.push_back(newField);
}

ComposableType::~ComposableType() { }

