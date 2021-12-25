#include "IncompleteType.h"

#include <boost/functional/hash.hpp>

IncompleteType::IncompleteType(const TypeItf& p_type, Type p_typeType)
: TypeItf{p_type.getName()},
m_type{p_typeType},
m_cachedHash{0}
{
  setIncompleteType(true);
  setCType(p_type.isCType());
  setEnum(p_type.isEnum());
  setFunction(p_type.isFunctionType());
  setImplicit(p_type.isImplicit());
  setPointer(p_type.isPointer());
  setStruct(p_type.isStruct());
  setUnion(p_type.isUnion());
}

const char* IncompleteType::getComposableTypeKeyword() const
{
  switch(m_type)
  {
    case Type::STRUCT:
      return "struct";
    case Type::UNION:
      return "union";
  }
  return "error IncompleteType::getComposableTypeKeyword()";
}

std::string IncompleteType::getDeclarationPrefix(bool) const
{
  std::string toReturn { getComposableTypeKeyword() + std::string{ " " } + m_name};
  while(toReturn.back() == ' ')
  {
    toReturn.pop_back();
  }
  return toReturn;
}

std::size_t IncompleteType::getHash() const noexcept
{
  if(m_cachedHash != 0)
  {
    return m_cachedHash;
  }
  std::size_t seed { TypeItf::getHash() };
  boost::hash_combine(seed, static_cast<uint32_t>(m_type));

  return seed;
}

void IncompleteType::cacheHash() noexcept
{
  m_cachedHash = 0;
  TypeItf::cacheHash();
  m_cachedHash = IncompleteType::getHash();
}

IncompleteType::~IncompleteType()
{}
