#include "Function.h"

#include <boost/functional/hash.hpp>

Function::Function(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters):
m_name(p_functionName), m_parameters(p_functionParameters), m_returnType(p_functionReturnType), m_attributes{}, m_isVariadic(false), m_isInlined(false), m_isStatic{false}, m_originFile{}
{ }

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

bool Function::isStatic() const noexcept
{
  return m_isStatic;
}

void Function::setIsStatic(bool value) noexcept
{
  m_isStatic = value;
}

const std::string& Function::getOriginFile() const noexcept
{
  return m_originFile;
}

void Function::setOriginFile(std::string originFile) noexcept
{
  m_originFile = std::move(originFile);
}

void Function::setInlined(bool value)
{
  m_isInlined = value;
}

std::size_t Function::getHash() const
{
  std::size_t seed { 0 };
  boost::hash_combine(seed, m_isInlined);
  boost::hash_combine(seed, m_isVariadic);
  boost::hash_combine(seed, m_name);
  boost::hash_combine(seed, m_parameters);
  boost::hash_combine(seed, m_returnType);
  boost::hash_combine(seed, m_attributes);
  boost::hash_combine(seed, m_isStatic);

  return seed;
}

std::size_t Function::getRawHash() const noexcept
{
  std::size_t seed { 0 };
  boost::hash_combine(seed, m_isVariadic);
  boost::hash_combine(seed, m_name);
  for(const auto& param: m_parameters)
  {
    auto detypedTypedef = deTypeDef(*param->getType());
    boost::hash_combine(seed, detypedTypedef->getHash());
  }
  auto detypedTypedef = deTypeDef(*m_returnType.getType());
  boost::hash_combine(seed, detypedTypedef->getHash());

  return seed;
}

void Function::addAttribute(FunctionAttribute p_attribute)
{
  m_attributes.push_back(std::move(p_attribute));
}

const Function::AttributesList & Function::getAttributes() const
{
  return m_attributes;
}

bool Function::operator==(const Function& other) const
{
  const bool isInlineEq = this->m_isInlined == other.m_isInlined;
  const bool isVariadicEq = this->m_isVariadic == other.m_isVariadic;
  const bool nameEq = this->m_name == other.m_name;
  const bool paramEq = this->m_parameters == other.m_parameters;
  const bool returnTypeEq = this->m_returnType == other.m_returnType;
  const bool attributesEq = this->m_attributes == other.m_attributes;
  const bool isStaticEq = this->m_isStatic == other.m_isStatic;

  return isInlineEq && isVariadicEq && nameEq && paramEq && returnTypeEq && attributesEq && isStaticEq;
}

bool Function::operator!=(const Function& other) const
{
  return (*this == other) == false;
}

std::string Function::getFunctionPrototype() const
{
  std::string rv_funcProto;
  if(m_isStatic)
  {
    rv_funcProto.append("static ");
  }
  if(m_isInlined)
  {
    rv_funcProto.append("inline ");
  }
  for(const auto& attr : this->m_attributes)
  {
    rv_funcProto.append("__attribute__((");
    rv_funcProto.append(attr.getName());
    bool firstParam = true;
    const auto& attrParams = attr.getParameters();
    if(!attrParams.empty())
    {
      rv_funcProto.push_back('(');
      for(const auto& attrParam : attrParams)
      {
        if(!firstParam)
        {
          rv_funcProto.push_back(',');
        }
        rv_funcProto.append(attrParam);
        firstParam = false;
      }
      rv_funcProto.push_back(')');
    }
    rv_funcProto.append(")) ");
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
