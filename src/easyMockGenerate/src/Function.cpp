#include "Function.h"

Function::Function(std::string functionName, ReturnValue functionReturnType, Parameter::Vector functionParameters) :
ElementToMock(functionName, functionParameters), m_returnTypeStr(functionReturnType) { }

Function* Function::clone() const
{
  return new Function(*this);
}

ElementToMock_Type Function::getMockType() const
{
  return ETS_function;
}

const ReturnValue* Function::getReturnType() const
{
  return &m_returnTypeStr;
}

bool Function::operator==(const Function& other) const
{
  return ElementToMock::operator==(other) && this->m_returnTypeStr == other.m_returnTypeStr;
}

bool Function::operator!=(const Function& other) const
{
  return (*this == other) == false;
}

