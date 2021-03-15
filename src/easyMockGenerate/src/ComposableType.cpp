#include "ComposableType.h"

#include <boost/algorithm/string/replace.hpp>
#include <boost/functional/hash.hpp>

ComposableType::ComposableType(const std::string p_name, bool p_is_embedded_in_other_type) :
ComposableType(p_name, ComposableFieldItf::Vector({}), p_is_embedded_in_other_type)
{
}

ComposableType::ComposableType(const std::string p_name, const ComposableFieldItf::Vector p_elem, bool p_is_embedded_in_other_type) :
TypeItf(p_name), m_elem(p_elem), m_is_declaration_embedded_in_other_type(p_is_embedded_in_other_type)
{
}

ComposableType::ComposableType(const ComposableType& other) :
TypeItf(other), m_elem(other.m_elem), m_is_declaration_embedded_in_other_type(other.m_is_declaration_embedded_in_other_type)
{}

ComposableType & ComposableType::operator=(const ComposableType& other)
{
  TypeItf::operator=(other);
  m_elem = other.m_elem;
  m_is_declaration_embedded_in_other_type = other.m_is_declaration_embedded_in_other_type;

  return *this;
}

ComposableType::ComposableType(ComposableType&& other) :
TypeItf(static_cast<TypeItf&&>(other))
{
  m_elem = std::move(other.m_elem);
  m_is_declaration_embedded_in_other_type = std::move(other.m_is_declaration_embedded_in_other_type);
}

bool ComposableType::isDeclarationEmbeddedInOtherType() const
{
  return m_is_declaration_embedded_in_other_type;
}

std::size_t ComposableType::getHash() const
{
  std::size_t seed { TypeItf::getHash() };
  boost::hash_combine(seed, m_elem);
  boost::hash_combine(seed, m_is_declaration_embedded_in_other_type);

  return seed;
}

bool ComposableType::operator==(const TypeItf& other) const
{
  return this->isEqual(other);
}

bool ComposableType::isEqual(const TypeItf& p_other) const
{
  bool parentEq = TypeItf::isEqual(p_other);
  const ComposableType* other = static_cast<const ComposableType*>(&p_other);
  if(!parentEq || !other)
  {
    return false;
  }
  bool elemEq = this->m_elem == other->m_elem;
  bool embedEq = this->m_is_declaration_embedded_in_other_type == other->m_is_declaration_embedded_in_other_type;
  return parentEq && elemEq && embedEq;
}

std::string ComposableType::getDeclarationPrefix(bool p_naked) const
{
  std::string toReturn { getComposableTypeKeyword() + std::string { " " } + m_name };
  while(toReturn.back() == ' ')
  {
    toReturn.pop_back();
  }
  return toReturn;
}

bool ComposableType::operator!=(const TypeItf& other) const
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
