#include "IncompleteType.h"

IncompleteType::IncompleteType(const TypeItf& p_type)
: TypeItf(p_type.getName(), p_type.getTypedDefName())
{
  setIncompleteType(true);
  setCType(p_type.isCType());
  setConst(p_type.isConst());
  setEnum(p_type.isEnum());
  setFunction(p_type.isFunction());
  setImplicit(p_type.isImplicit());
  setPointer(p_type.isPointer());
  setStruct(p_type.isStruct());
  setUnion(p_type.isUnion());
}

IncompleteType* IncompleteType::clone() const
{
  return new IncompleteType(*this);
}

IncompleteType::~IncompleteType()
{}

