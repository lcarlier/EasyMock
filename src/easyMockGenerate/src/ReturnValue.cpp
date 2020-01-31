#include "ReturnValue.h"
#include "TypeItf.h"
#include "CType.h"
#include "StructType.h"

ReturnValue::ReturnValue() :
ReturnValue(nullptr, false)
{
}

ReturnValue::ReturnValue(TypeItf* type) :
ReturnValue(type, false)
{ }

ReturnValue::ReturnValue(TypeItf* type, bool isPointer) :
Declarator(type, isPointer)
{
}

ReturnValue::ReturnValue(const ReturnValue& other) :
ReturnValue(other.m_type->clone(), other.m_isPointer)
{
}

ReturnValue::ReturnValue(ReturnValue&& other)
{
  swap(*this, other);
}

ReturnValue& ReturnValue::operator=(ReturnValue other)
{
  swap(*this, other);

  return *this;
}

void swap(ReturnValue &first, ReturnValue &second)
{
  swap(static_cast<Declarator &>(first), static_cast<Declarator &>(second));
}

ReturnValue::~ReturnValue()
{
}

ReturnValue VoidReturnValue (bool p_isPointer)
{
  ReturnValue rv = ReturnValue(new CType(CTYPE_VOID));
  rv.setPointer(p_isPointer);
  return rv;
}

ReturnValue TypedReturnValue(easyMock_cTypes_t p_type, bool p_isPointer)
{
  ReturnValue rv = ReturnValue(new CType(p_type));
  rv.setPointer(p_isPointer);
  return rv;
}

ReturnValue StructReturnValue(StructType *type, bool p_isPointer)
{
  ReturnValue rv = ReturnValue(type);
  rv.setPointer(p_isPointer);
  return rv;
}

bool ReturnValue::operator==(const ReturnValue& other) const
{
  return Declarator::operator==(other);
}

bool ReturnValue::operator!=(const ReturnValue& other) const
{
  return (*this == other) == false;
}

