#include <TypedefType.h>
#include <Pointer.h>

#include <boost/functional/hash.hpp>

TypedefType::TypedefType(std::string p_typedefName, std::shared_ptr<TypeItf> p_typeeType) :
TypeItf { std::move(p_typedefName), p_typeeType->getNamespace() },
m_typeeType { std::move(p_typeeType) },
m_cachedHash{0},
m_cachedRawHash{0}
{
  setTypedefType(true);
}

bool TypedefType::operator==(const TypeItf &other) const
{
  return isEqual(other);
}

bool TypedefType::operator!=(const TypeItf &other) const
{
  return !(*this == other);
}

std::size_t TypedefType::getHash() const noexcept
{
  if(m_cachedHash != 0)
  {
    return m_cachedHash;
  }
  std::size_t seed { TypeItf::getHash() };
  boost::hash_combine(seed, getRawHash());

  return seed;
}

void TypedefType::cacheHash() noexcept
{
  m_cachedRawHash = 0;
  m_cachedHash = 0;
  TypeItf::cacheHash();
  m_typeeType->cacheHash();
  // Since getHash calls getRawHash:
  // First cache the raw hash
  m_cachedRawHash = TypedefType::getRawHash();
  // Then cache the hash
  m_cachedHash = TypedefType::getHash();
}

std::size_t TypedefType::getRawHash() const noexcept
{
  if(m_cachedRawHash != 0)
  {
    return m_cachedRawHash;
  }
  return m_typeeType->getHash();
}

bool TypedefType::isEqual(const TypeItf &p_other) const
{
  bool parentEqual = TypeItf::isEqual(p_other);
  const TypedefType* other = dynamic_cast<const TypedefType*>(&p_other);
  if(!parentEqual || !other)
  {
    return false;
  }
  bool typeeEqual = *this->m_typeeType == *other->m_typeeType;

  return typeeEqual;
}

const TypeItf* TypedefType::getTypee() const
{
  return m_typeeType.get();
}

TypeItf* TypedefType::getTypee()
{
  return const_cast<TypeItf*>(static_cast<const TypedefType *>(this)->getTypee());
}

const TypeItf* TypedefType::getMostDefinedTypee() const
{
  const TypedefType* typeeTypedef = m_typeeType->asTypedefType();
  if(typeeTypedef)
  {
    return typeeTypedef->getMostDefinedTypee();
  }
  return m_typeeType.get();
}

TypeItf* TypedefType::getMostDefinedTypee()
{
  return const_cast<TypeItf*>(static_cast<const TypedefType*>(this)->getMostDefinedTypee());
}

std::string TypedefType::getDeclarationPrefix(bool) const
{
  return m_name;
}

TypedefType::~TypedefType()
{
}
