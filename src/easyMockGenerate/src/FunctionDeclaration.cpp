#include "FunctionDeclaration.h"
#include "Namespace.h"
#include "StructType.h"

#include <boost/functional/hash.hpp>

FunctionDeclaration::FunctionDeclaration(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters):
FunctionDeclaration{std::move(p_functionName), std::move(p_functionReturnType), std::move(p_functionParameters), getGlobalNamespace(), {}}
{
}

FunctionDeclaration::FunctionDeclaration(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters, std::shared_ptr<const Namespace> p_namespace, std::weak_ptr<const ComposableType> p_parentData):
    Function{std::move(p_functionName), std::move(p_functionReturnType), std::move(p_functionParameters), std::move(p_parentData)},
    ElementToMock{},
    m_doesThisDeclarationHasBody{false},
    m_cachedHash{0},
    m_namespace{std::move(p_namespace)}
{
}

bool FunctionDeclaration::doesThisDeclarationHasABody() const noexcept
{
  return m_doesThisDeclarationHasBody;
}

void FunctionDeclaration::setDoesThisDeclarationHasABody(bool val) noexcept
{
  m_doesThisDeclarationHasBody = val;
}

size_t FunctionDeclaration::getHash() const noexcept
{
  if(m_cachedHash != 0)
  {
    return m_cachedHash;
  }
  size_t seed{Function::getHash()};
  boost::hash_combine(seed, ElementToMock::getHash());
  boost::hash_combine(seed, m_doesThisDeclarationHasBody);
  boost::hash_combine(seed, *m_namespace);

  return seed;
}

void FunctionDeclaration::cacheHash() noexcept
{
  m_cachedHash = 0;
  Function::cacheHash();
  ElementToMock::cacheHash();
  m_cachedHash = FunctionDeclaration::getHash();
}

std::shared_ptr<const Namespace> FunctionDeclaration::getNamespace() const
{
  return m_namespace;
}

bool FunctionDeclaration::operator==(const FunctionDeclaration& other) const
{
  bool funEqual = Function::operator==(other);
  /*
   * ElementToMock doesn't have any operator==() function because it
   * doesn't have any members.
   */
  bool doesThisDeclEqual = this->m_doesThisDeclarationHasBody == other.m_doesThisDeclarationHasBody;
  bool namespaceEqual = *this->m_namespace == *other.m_namespace;

  return funEqual && doesThisDeclEqual && namespaceEqual;
}

bool FunctionDeclaration::operator!=(const FunctionDeclaration& other) const
{
  return !(*this == other);
}


ElementToMock_Type FunctionDeclaration::getMockType() const
{
  return ETS_function;
}

FunctionDeclaration::~FunctionDeclaration() {
}
