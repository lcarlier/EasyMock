#include "FunctionDeclaration.h"

FunctionDeclaration::FunctionDeclaration(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters):
Function(p_functionName, p_functionReturnType, p_functionParameters), ElementToMock()
{
}

bool FunctionDeclaration::operator==(const FunctionDeclaration& other) const
{
  bool funEqual = Function::operator==(other);
  /*
   * ElementToMock doesn't have any operator==() function because it
   * doesn't have any members.
   */

  return funEqual;
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

