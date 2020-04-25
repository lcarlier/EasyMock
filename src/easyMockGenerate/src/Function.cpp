#include "Function.h"
#include "TypeItf.h"

Function::Function(std::string functionName, ReturnValue functionReturnType, Parameter::Vector functionParameters) :
ElementToMock(functionName, functionParameters), m_returnType(functionReturnType) { }

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
  return &m_returnType;
}

bool Function::operator==(const Function& other) const
{
  return ElementToMock::operator==(other) &&
          this->m_returnType == other.m_returnType;
}

bool Function::operator!=(const Function& other) const
{
  return (*this == other) == false;
}

const std::string Function::getFunctionPrototype() const
{
  std::string rv_funcProto;
  rv_funcProto.append(m_returnType.getType()->getFullDeclarationName());
  rv_funcProto.push_back(' ');
  rv_funcProto.append(m_name);
  rv_funcProto.push_back('(');
  bool firstElem = true;
  for(Parameter *fParam: m_parameters)
  {
    if(!firstElem)
    {
      rv_funcProto.append(", ");
    }
    rv_funcProto.append(fParam->getType()->getFullDeclarationName());
    rv_funcProto.push_back(' ');
    rv_funcProto.append(fParam->getName());
    firstElem = false;
  }
  if(m_isVariadic)
  {
    if(!firstElem)
    {
      rv_funcProto.append(", ");
    }
    rv_funcProto.append("...");
  }
  rv_funcProto.push_back(')');

  return rv_funcProto;
}
