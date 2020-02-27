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
  return ElementToMock::operator==(other) && this->m_returnType == other.m_returnType;
}

bool Function::operator!=(const Function& other) const
{
  return (*this == other) == false;
}

const std::string Function::getFunctionPrototype() const
{
  std::string rv_funcProto;
  if(m_returnType.getType()->isStruct())
  {
    rv_funcProto.append("struct ");
  }
  rv_funcProto.append(m_returnType.getTypeName());
  if(m_returnType.isPointer())
  {
    rv_funcProto.push_back('*');
  }
  rv_funcProto.push_back(' ');
  rv_funcProto.append(m_name);
  rv_funcProto.push_back('(');
  for (Parameter::Vector::const_iterator it = m_parameters.begin(); it != m_parameters.end(); ++it)
  {
    if(it != m_parameters.begin())
    {
      rv_funcProto.append(", ");
    }
    const Parameter *fParam = *it;
    const TypeItf *type = fParam->getType();
    if(type->isStruct())
    {
      rv_funcProto.append("struct ");
    }
    const std::string &name = type->getName();
    const std::string &typedDefName = type->getTypedDefName();
    if(typedDefName.compare("") != 0)
    {
      rv_funcProto.append(typedDefName);
    }
    else
    {
      rv_funcProto.append(name);
    }
    if(fParam->isPointer())
    {
      rv_funcProto.push_back('*');
    }
    rv_funcProto.push_back(' ');
    rv_funcProto.append(fParam->getName());
  }
  rv_funcProto.push_back(')');

  return rv_funcProto;
}
