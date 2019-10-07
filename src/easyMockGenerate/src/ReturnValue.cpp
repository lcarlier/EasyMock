#include "ReturnValue.h"

ReturnValue VoidReturnValue ()
{
  ReturnValue rv;
  rv.isVoid = true;
  return rv;
}

ReturnValue TypedReturnValue(std::string p_type)
{
  ReturnValue rv = ReturnValue();
  rv.type = p_type;

  return rv;
};

ReturnValue StructReturnValue(std::string p_type)
{
  ReturnValue rv = ReturnValue();
  rv.type = p_type;
  rv.isStruct = true;

  return rv;
};

bool ReturnValue::operator==(const ReturnValue& other) const
{
  return this->isStruct == other.isStruct && this->isVoid == other.isVoid && this->type == other.type;
}

bool ReturnValue::operator!=(const ReturnValue& other) const
{
  return (*this == other) == false;
}

