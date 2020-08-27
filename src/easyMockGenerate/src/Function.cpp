#include "Function.h"
#include "TypeItf.h"

Function::Function(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters):
m_name(p_functionName), m_parameters(p_functionParameters), m_returnType(p_functionReturnType), m_isVariadic(false), m_isInlined(false) { }

Function* Function::clone() const
{
  return new Function(*this);
}

const std::string* Function::getName() const
{
  return &m_name;
}

const Parameter::Vector& Function::getFunctionsParameters() const
{
  return m_parameters;
}

Parameter::Vector& Function::getFunctionsParameters()
{
  return const_cast<Parameter::Vector&>(static_cast<const Function &>(*this).getFunctionsParameters());
}

const ReturnValue* Function::getReturnType() const
{
  return &m_returnType;
}

bool Function::isVariadic() const
{
  return m_isVariadic;
}

void Function::setVariadic(bool value)
{
  m_isVariadic = value;
}

bool Function::isInlined() const
{
  return m_isInlined;
}

void Function::setInlined(bool value)
{
  m_isInlined = value;
}

bool Function::operator==(const Function& other) const
{
  const bool nameEq = this->m_name == other.m_name;
  const bool paramEq = this->m_parameters == other.m_parameters;
  const bool isVariadicEq = this->m_isVariadic == other.m_isVariadic;
  const bool isInlineEq = this->m_isInlined == other.m_isInlined;
  const bool returnTypeEq = this->m_returnType == other.m_returnType;

  return nameEq && paramEq && isVariadicEq && isInlineEq && returnTypeEq;
}

bool Function::operator!=(const Function& other) const
{
  return (*this == other) == false;
}

std::string Function::getFunctionPrototype() const
{
  std::string rv_funcProto;
  if(m_isInlined)
  {
      rv_funcProto.append("inline ");
  }
  rv_funcProto.append(m_returnType.getDeclareString());
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
    rv_funcProto.append(fParam->getDeclareString());
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
