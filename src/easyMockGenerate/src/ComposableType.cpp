#include "ComposableType.h"
#include "FunctionDeclaration.h"

#include <boost/functional/hash.hpp>

ComposableType::ComposableType(std::string p_name, bool p_is_embedded_in_other_type) :
ComposableType{std::move(p_name), {}, p_is_embedded_in_other_type}
{
}

ComposableType::ComposableType(std::string p_name, ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type) :
TypeItf{std::move(p_name)},
m_elem{std::move(p_elem)},
m_is_declaration_embedded_in_other_type{p_is_embedded_in_other_type},
m_is_forward_declared{false},
m_cachedHash{0}
{
}

bool ComposableType::isDeclarationEmbeddedInOtherType() const
{
  return m_is_declaration_embedded_in_other_type;
}

bool ComposableType::isForwardDeclared() const
{
  return m_is_forward_declared;
}

void ComposableType::setForwardDecl(bool p_value)
{
  m_is_forward_declared = p_value;
}

std::size_t ComposableType::getHash() const noexcept
{
  if(m_cachedHash != 0)
  {
    return m_cachedHash;
  }
  std::size_t seed { TypeItf::getHash() };
  boost::hash_combine(seed, *getComposableTypeKeyword());
  boost::hash_combine(seed, m_elem);
  boost::hash_combine(seed, m_is_declaration_embedded_in_other_type);
  boost::hash_combine(seed, m_is_forward_declared);
  for(const auto& function : m_functions)
  {
    //const auto f_ptr = function.lock();
    boost::hash_combine(seed, *function);
  }

  return seed;
}

void ComposableType::cacheHash() noexcept
{
  m_cachedHash = 0;
  TypeItf::cacheHash();
  for(auto& v_elem : m_elem)
  {
    std::visit([](auto& elem)
    {
      elem.cacheHash();
    },
    v_elem);
  }
  m_cachedHash = ComposableType::getHash();
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
  // The composable type keyword is a static const char* so it is correct to just compare their addresses
  bool typeEq = this->getComposableTypeKeyword() == other->getComposableTypeKeyword();
  bool elemEq = this->m_elem == other->m_elem;
  bool embedEq = this->m_is_declaration_embedded_in_other_type == other->m_is_declaration_embedded_in_other_type;
  bool isForwardDecl = this->m_is_forward_declared == other->m_is_forward_declared;
  if(m_functions.size() != other->m_functions.size())
  {
    return false;
  }
  for(size_t funIdx = 0; funIdx < m_functions.size(); ++funIdx)
  {
    auto f1 = m_functions[funIdx];
    auto f2 = other->m_functions[funIdx];
    if(f1->getFunctionPrototype() != f2->getFunctionPrototype())
    {
      return false;
    }
  }
  return typeEq && parentEq && elemEq && embedEq && isForwardDecl;
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

ComposableType::ComposableFieldTypeVector& ComposableType::getContainedFields()
{
  return const_cast<std::vector<ComposableFieldType> &>(static_cast<const ComposableType &>(*this).getContainedFields());
}

const ComposableType::ComposableFieldTypeVector& ComposableType::getContainedFields() const
{
  return m_elem;
}

void ComposableType::addField(ComposableType::ComposableFieldType newField)
{
  m_elem.emplace_back(std::move(newField));
}

void ComposableType::addFunction(ComposableType::ComposableMethodType newFunction)
{
  m_functions.emplace_back(std::move(newFunction));
}

const ComposableType::ComposableMethodVector &ComposableType::getFunctions() const
{
  return m_functions;
}

ComposableType::~ComposableType() { }

namespace boost
{
  std::size_t hash_value(const ComposableType& p_composableType)
  {
    return p_composableType.getHash();
  }
}
