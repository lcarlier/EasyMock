#include "ReturnValue.h"
#include "TypeItf.h"
#include "CType.h"
#include "StructType.h"
#include "Pointer.h"

ReturnValue::ReturnValue() :
ReturnValue(nullptr)
{
}

ReturnValue::ReturnValue(TypeItf* type) :
Declarator(type)
{
}

ReturnValue::ReturnValue(const ReturnValue& other) :
Declarator(other)
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
  return TypedReturnValue(CTYPE_VOID, p_isPointer);
}

ReturnValue TypedReturnValue(easyMock_cTypes_t p_type, bool p_isPointer)
{
  TypeItf *curType = new CType(p_type);
  if(p_isPointer)
  {
    curType = new Pointer(curType);
  }

  ReturnValue rv = ReturnValue(curType);

  return rv;
}

ReturnValue StructReturnValue(StructType *type, bool p_isPointer)
{
  TypeItf *curType = type;
  if(p_isPointer)
  {
    curType = new Pointer(type);
  }

  ReturnValue rv = ReturnValue(curType);

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

