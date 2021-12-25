#include "FunctionDeclaration.h"

#include <boost/functional/hash.hpp>

FunctionDeclaration::FunctionDeclaration(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters):
Function{std::move(p_functionName), std::move(p_functionReturnType), std::move(p_functionParameters)},
ElementToMock{},
m_doesThisDeclarationHasBody{false},
m_cachedHash{0}
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

  return seed;
}

void FunctionDeclaration::cacheHash() noexcept
{
  m_cachedHash = 0;
  Function::cacheHash();
  ElementToMock::cacheHash();
  m_cachedHash = FunctionDeclaration::getHash();
}

bool FunctionDeclaration::operator==(const FunctionDeclaration& other) const
{
  bool funEqual = Function::operator==(other);
  /*
   * ElementToMock doesn't have any operator==() function because it
   * doesn't have any members.
   */
  bool doesThisDeclEqual = this->m_doesThisDeclarationHasBody == other.m_doesThisDeclarationHasBody;

  return funEqual && doesThisDeclEqual;
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
