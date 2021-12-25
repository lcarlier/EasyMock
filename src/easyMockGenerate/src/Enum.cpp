#include "Enum.h"

#include <boost/functional/hash.hpp>
#include <boost/type_index/type_index_facade.hpp>

Enum::Enum(const std::string p_name):
TypeItf { p_name },
m_cachedHash{0}
{
  setEnum(true);
}

void Enum::addEnumValue(int64_t p_value, const std::string& p_enumStr)
{
  m_listOfValues.emplace(p_value, p_enumStr);
}

const Enum::listOfValuesType& Enum::getValues() const
{
  return m_listOfValues;
}

bool Enum::isEqual(const TypeItf& p_other) const
{
  bool parentEqual = TypeItf::isEqual(p_other);
  const Enum *otherEnum = dynamic_cast<const Enum*>(&p_other);
  if(!otherEnum || !parentEqual)
  {
    return false;
  }
  bool listOfValueEqual = m_listOfValues == otherEnum->m_listOfValues;

  return parentEqual && listOfValueEqual;
}

std::string Enum::getDeclarationPrefix(bool) const
{
  std::string toReturn { std::string {"enum "} + m_name };
  while(toReturn.back() == ' ')
  {
    toReturn.pop_back();
  }
  return toReturn;
}

std::size_t Enum::getHash() const noexcept
{
  if(m_cachedHash != 0)
  {
    return m_cachedHash;
  }
  std::size_t seed { TypeItf::getHash() };
  boost::hash_combine(seed, boost::hash_range(this->m_listOfValues.begin(), this->m_listOfValues.end()));

  return seed;
}

void Enum::cacheHash() noexcept
{
  m_cachedHash = 0;
  TypeItf::cacheHash();
  m_cachedHash = Enum::getHash();
}
