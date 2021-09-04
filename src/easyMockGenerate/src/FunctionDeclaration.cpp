#include "FunctionDeclaration.h"

FunctionDeclaration::FunctionDeclaration(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters):
Function(p_functionName, p_functionReturnType, p_functionParameters), ElementToMock(), m_doesThisDeclarationHasBody{false}
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

size_t FunctionDeclaration::getHash() const
{
  size_t seed{0};
  boost::hash_combine(seed, Function::getHash());
  boost::hash_combine(seed, ElementToMock::getHash());
  boost::hash_combine(seed, m_doesThisDeclarationHasBody);

  return seed;
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


FunctionDeclaration* FunctionDeclaration::clone() const
{
  return new FunctionDeclaration(*this);
}


FunctionDeclaration::~FunctionDeclaration() {
}

