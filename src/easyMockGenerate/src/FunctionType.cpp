#include "FunctionType.h"

FunctionType::FunctionType(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters):
Function(p_functionName, p_functionReturnType, p_functionParameters), TypeItf("function")
{
  setFunction(true);
}

bool FunctionType::operator==(const FunctionType& other) const
{
  bool funEqual = Function::operator==(other);
  bool typeEqual = TypeItf::operator ==(other);

  return funEqual && typeEqual;
}

bool FunctionType::operator!=(const FunctionType& other) const
{
  return !(*this == other);
}


FunctionType* FunctionType::clone() const
{
  return new FunctionType(*this);
}


FunctionType::~FunctionType() {
}

