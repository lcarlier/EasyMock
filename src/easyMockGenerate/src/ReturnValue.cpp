#include "ReturnValue.h"
#include "TypeItf.h"
#include "CType.h"
#include "StructType.h"

ReturnValue::ReturnValue() :
m_type(nullptr)
{
}

ReturnValue::ReturnValue(TypeItf* type) :
m_type(type)
{
}

ReturnValue::ReturnValue(const ReturnValue& other) :
m_type(other.m_type->clone())
{
}

ReturnValue::ReturnValue(ReturnValue&& other) :
m_type(nullptr)
{
  swap(*this, other);
}

ReturnValue& ReturnValue::operator=(ReturnValue other)
{
  swap(*this, other);

  return *this;
}

const TypeItf* ReturnValue::getType() const
{
  return m_type;
}

void ReturnValue::setType(TypeItf* type)
{
  m_type = type;
}


void swap(ReturnValue &first, ReturnValue &second)
{
  std::swap(first.m_type, second.m_type);
}

ReturnValue::~ReturnValue()
{
  delete m_type;
}

ReturnValue VoidReturnValue ()
{
  ReturnValue rv = ReturnValue(new CType(CTYPE_VOID));
  return rv;
}

ReturnValue TypedReturnValue(easyMock_cTypes_t p_type)
{
  ReturnValue rv = ReturnValue(new CType(p_type));
  return rv;
}

ReturnValue StructReturnValue(StructType *type)
{
  ReturnValue rv = ReturnValue(type);

  return rv;
}

bool ReturnValue::operator==(const ReturnValue& other) const
{
  if(this->m_type == nullptr && other.m_type == nullptr)
  {
    return true;
  }
  return this->m_type != nullptr && other.m_type != nullptr && *this->m_type == *other.m_type;
}

bool ReturnValue::operator!=(const ReturnValue& other) const
{
  return (*this == other) == false;
}

