#include "Function.h"

#include <boost/functional/hash.hpp>

Function::Function(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters, std::weak_ptr<const ComposableType> p_parentData):
    m_name{p_functionName},
    m_parameters{std::move(p_functionParameters)},
    m_returnType{std::move(p_functionReturnType)},
    m_attributes{},
    m_isVariadic{false},
    m_isInlined{false},
    m_isStatic{false},
    m_originFile{},
    m_parentData{std::move(p_parentData)},
    m_accessSpecifier{FunctionAccessSpecifier::NA},
    m_isClassConst{false},
    m_cachedHash{0},
    m_cachedRawHash{0}
{ }

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

const ReturnValue* Function::getReturnValue() const
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

FunctionAccessSpecifier Function::getAccessSpecifier() const noexcept
{
  return m_accessSpecifier;
}

const std::string &Function::getAccessSpecifierStr() const noexcept
{
  static std::string publicStr{"public"};
  static std::string protectedStr{"protected"};
  static std::string privateStr{"private"};
  static std::string naStr{"na"};
  switch (m_accessSpecifier)
  {
    case FunctionAccessSpecifier::NA:
      return naStr;
    case FunctionAccessSpecifier::PROTECTED:
      return protectedStr;
    case FunctionAccessSpecifier::PRIVATE:
      return privateStr;
    case FunctionAccessSpecifier::PUBLIC:
      return publicStr;
  }
  // Gcc isn't seeing that this code is actually unreachable -_-'
#ifdef __GNUC__
  return naStr;
#endif
}

void Function::setAccessSpecifier(FunctionAccessSpecifier p_accessSpecifier) noexcept
{
  m_accessSpecifier = std::move(p_accessSpecifier);
}

void Function::setClassConst(bool value) noexcept
{
  m_isClassConst = value;
}

bool Function::isClassConst() const noexcept
{
  return m_isClassConst;
}

std::size_t Function::getHash() const noexcept
{
  if(m_cachedHash != 0)
  {
    return m_cachedHash;
  }
  std::size_t seed { 0 };
  boost::hash_combine(seed, m_isInlined);
  boost::hash_combine(seed, m_isVariadic);
  boost::hash_combine(seed, m_name);
  boost::hash_combine(seed, m_parameters);
  boost::hash_combine(seed, m_returnType);
  boost::hash_combine(seed, m_attributes);
  boost::hash_combine(seed, m_isStatic);
  /*if(m_parentData)
  {
    boost::hash_combine(seed, *m_parentData);
  }*/
  boost::hash_combine(seed, m_accessSpecifier);
  boost::hash_combine(seed, m_isClassConst);

  return seed;
}

std::shared_ptr<const ComposableType> Function::getParentData() const
{
  return m_parentData.lock();
}

bool Function::isMemberClass() const
{
  return m_parentData.lock() != nullptr;
}


void Function::cacheHash() noexcept
{
  m_cachedHash = 0;
  m_cachedRawHash = 0;
  for(auto& param : m_parameters)
  {
    param.cacheHash();
  }
  for(auto& attr : m_attributes)
  {
    attr.cacheHash();
  }
  m_returnType.cacheHash();
  m_cachedHash = Function::getHash();
  m_cachedRawHash = Function::getRawHash();
}

std::size_t Function::getRawHash() const noexcept
{
  if(m_cachedRawHash != 0)
  {
    return m_cachedRawHash;
  }
  std::size_t seed { 0 };
  boost::hash_combine(seed, m_isVariadic);
  boost::hash_combine(seed, m_name);
  for(const auto& param: m_parameters)
  {
    const TypeItf* typeItf = param.getType();
    boost::hash_combine(seed, typeItf->getRawHash());
  }
  const TypeItf* typeItf = m_returnType.getType();
  boost::hash_combine(seed, typeItf->getRawHash());

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
  bool parentEqual = true;
  auto thisLockedParent = m_parentData.lock();
  auto otherLockedParent = other.m_parentData.lock();
  if(thisLockedParent.operator bool() != otherLockedParent.operator bool())
  {
    parentEqual = false;
  }
  if(parentEqual && thisLockedParent)
  {
    parentEqual = *thisLockedParent == *otherLockedParent;
  }
  const bool visibilityEq = this->m_accessSpecifier == other.m_accessSpecifier;
  const bool isConstEq = this->m_isClassConst == other.m_isClassConst;

  return isInlineEq && isVariadicEq && nameEq && paramEq && returnTypeEq && attributesEq && isStaticEq && parentEqual && visibilityEq && isConstEq;
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
  auto lockedParentData = m_parentData.lock();
  if(lockedParentData)
  {
    rv_funcProto.append(lockedParentData->getName());
    rv_funcProto.push_back(':');
    rv_funcProto.push_back(':');
  }
  rv_funcProto.append(m_name);
  rv_funcProto.push_back('(');
  bool firstElem = true;
  for(const auto& fParam: m_parameters)
  {
    if(!firstElem)
    {
      rv_funcProto.append(", ");
    }
    rv_funcProto.append(fParam.getDeclareString());
    rv_funcProto.push_back(' ');
    rv_funcProto.append(fParam.getName());
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

  if(m_isClassConst)
  {
    rv_funcProto.append(" const");
  }

  return rv_funcProto;
}
