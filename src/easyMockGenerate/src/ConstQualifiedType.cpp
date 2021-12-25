#include <ConstQualifiedType.h>

#include <boost/functional/hash.hpp>

#include <cassert>

ConstQualifiedType::ConstQualifiedType(std::shared_ptr<TypeItf> p_type) :
QualifiedType { std::move(p_type) },
m_cachedHash{0}
{
  if(p_type)
  {
    assert(!p_type->isConst());
  }
}

bool ConstQualifiedType::isConst() const
{
  return true;
}

const char* ConstQualifiedType::getQualifierString() const
{
  return "const";
}

std::size_t ConstQualifiedType::getHash() const noexcept
{
  if(m_cachedHash != 0)
  {
    return m_cachedHash;
  }
  std::size_t seed { QualifiedType::getHash() };
  boost::hash_combine(seed, std::string{"const"});
  return seed;
}

void ConstQualifiedType::cacheHash() noexcept
{
  m_cachedHash = 0;
  QualifiedType::cacheHash();
  m_cachedHash = ConstQualifiedType::getHash();
}

bool ConstQualifiedType::operator==(const TypeItf& p_other) const
{
  return isEqual(p_other);
}

bool ConstQualifiedType::operator!=(const TypeItf& p_other) const
{
  return !(*this == p_other);
}

bool ConstQualifiedType::isEqual(const TypeItf& p_other) const
{
  bool parentEq = QualifiedType::isEqual(p_other);
  const ConstQualifiedType* otherConstQualifiedType = dynamic_cast<const ConstQualifiedType*>(&p_other);

  return parentEq && otherConstQualifiedType != nullptr;
}
