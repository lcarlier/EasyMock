#include "FunctionType.h"

#include <boost/functional/hash.hpp>

#include <cassert>

FunctionType::FunctionType(ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters):
Function("", p_functionReturnType, p_functionParameters), TypeItf("")
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

std::string FunctionType::getDeclarationPrefix(bool p_naked) const
{
  return m_returnType.getType()->getDeclarationPrefix(p_naked) + std::string {"("};
}

std::string FunctionType::getDeclarationPostfix(bool p_naked) const
{
  std::string returnStr {")(" };
  bool firstParam = true;
  for(const Parameter *p : getFunctionsParameters())
  {
    if(!firstParam)
    {
      returnStr.append(", ");
    }
    returnStr.append(p->getDeclareString());
    firstParam = false;
  }
  returnStr.push_back(')');
  return returnStr;
}

std::size_t FunctionType::getHash() const
{
  std::size_t seed { Function::getHash() };
  /*
   * To keep in mind when reading this comment:
   * FunctionType inherits from Function and from TypeItf at the same time.
   *
   * I'm not very happy with hashing 2 numbers here but I can't see another
   * way to do it. If we try to do something like
   * boost::hash_combine(seed, *static_cast<const TypeItf*>(this));
   * we end up having a recursive inifinte loop of call
   * hash_value -> getHash() -> hash_value
   */
  boost::hash_combine(seed, TypeItf::getHash());

  return seed;
}

FunctionType* FunctionType::clone() const
{
  return new FunctionType(*this);
}


FunctionType::~FunctionType() {
}
