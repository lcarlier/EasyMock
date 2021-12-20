#include <TypedefType.h>
#include <Pointer.h>

#include <boost/functional/hash.hpp>

TypedefType::TypedefType(std::string p_typedefName, std::shared_ptr<TypeItf> p_typeeType) :
TypeItf { std::move(p_typedefName) }, m_typeeType { std::move(p_typeeType) }
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
  std::size_t seed { TypeItf::getHash() };
  boost::hash_combine(seed, getRawHash());

  return seed;
}

std::size_t TypedefType::getRawHash() const noexcept
{
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

void TypedefType::swap(TypedefType &first, TypedefType &second)
{
  std::swap(first.m_typeeType, second.m_typeeType);
}

TypedefType::~TypedefType()
{
}
