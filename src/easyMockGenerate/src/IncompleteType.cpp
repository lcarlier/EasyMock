#include "IncompleteType.h"

IncompleteType::IncompleteType(const TypeItf& p_type, Type p_typeType)
: TypeItf(p_type.getName(), p_type.getTypedDefName()), m_type(p_typeType)
{
  setIncompleteType(true);
  setCType(p_type.isCType());
  setEnum(p_type.isEnum());
  setFunction(p_type.isFunction());
  setImplicit(p_type.isImplicit());
  setPointer(p_type.isPointer());
  setStruct(p_type.isStruct());
  setUnion(p_type.isUnion());
}

const char* IncompleteType::getComposableTypeKeyword() const
{
  switch(m_type)
  {
    case Type::STRUCT:
      return "struct";
    case Type::UNION:
      return "union";
  }
  return "error IncompleteType::getComposableTypeKeyword()";
}

IncompleteType* IncompleteType::clone() const
{
  return new IncompleteType(*this);
}

IncompleteType::~IncompleteType()
{}

