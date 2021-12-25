#include "FunctionType.h"

#include <boost/functional/hash.hpp>

FunctionType::FunctionType(ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters):
Function{"", std::move(p_functionReturnType), std::move(p_functionParameters)},
TypeItf{""},
m_cachedHash{0}
{
  setFunction(true);
}

bool FunctionType::operator==(const FunctionType& p_other) const
{
  return isEqual(p_other);
}

bool FunctionType::operator!=(const FunctionType& p_other) const
{
  return !(*this == p_other);
}

std::string FunctionType::getDeclarationPrefix(bool p_naked) const
{
  return m_returnType.getType()->getDeclarationPrefix(p_naked) + std::string {"("};
}

std::string FunctionType::getDeclarationPostfix(bool p_naked) const
{
  std::string returnStr {")(" };
  bool firstParam = true;
  const auto& funParam = getFunctionsParameters();
  for(const auto& p: funParam)
  {
    if(!firstParam)
    {
      returnStr.append(", ");
    }
    returnStr.append(p.getDeclareString());
    firstParam = false;
  }
  returnStr.push_back(')');
  return returnStr;
}

std::size_t FunctionType::getHash() const noexcept
{
  if(m_cachedHash != 0)
  {
    return m_cachedHash;
  }
  std::size_t seed { Function::getHash() };
  /*
   * To keep in mind when reading this comment:
   * FunctionType inherits from Function and from TypeItf at the same time.
   *
   * I'm not very happy with hashing 2 numbers here, but I can't see another
   * way to do it. If we try to do something like
   * boost::hash_combine(seed, *static_cast<const TypeItf*>(this));
   * we end up having a recursive infinite loop of call
   * hash_value -> getHash() -> hash_value
   */
  boost::hash_combine(seed, TypeItf::getHash());

  return seed;
}

void FunctionType::cacheHash() noexcept
{
  m_cachedHash = 0;
  Function::cacheHash();
  TypeItf::cacheHash();
  m_cachedHash = FunctionType::getHash();
}

bool FunctionType::isEqual(const TypeItf &p_other) const
{
  const Function *function = dynamic_cast<const Function*>(&p_other);
  if(function == nullptr)
  {
    return false;
  }
  bool funEqual = Function::operator==(*function);
  bool typeEqual = TypeItf::isEqual(p_other);

  return funEqual && typeEqual;
}

FunctionType::~FunctionType() {
}
