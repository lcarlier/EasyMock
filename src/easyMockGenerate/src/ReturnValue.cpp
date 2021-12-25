#include "ReturnValue.h"
#include "TypeItf.h"
#include "EasyMock_CType.h"
#include "StructType.h"
#include "Pointer.h"

#include <boost/functional/hash.hpp>

ReturnValue::ReturnValue(std::shared_ptr<TypeItf> type) :
Declarator(std::move(type))
{
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
  std::shared_ptr<TypeItf> curType = std::make_shared<CType>(p_type);
  if(p_isPointer)
  {
    curType = std::make_shared<Pointer>(std::move(curType));
  }
  ReturnValue rv = ReturnValue(std::move(curType));

  return rv;
}

ReturnValue StructReturnValue(std::shared_ptr<StructType> type, bool p_isPointer)
{
  std::shared_ptr<TypeItf> curType = std::move(type);
  if(p_isPointer)
  {
    curType = std::make_shared<Pointer>(std::move(curType));
  }

  return ReturnValue{std::move(curType)};
}

bool ReturnValue::operator==(const ReturnValue& other) const
{
  return this->isEqual(other);
}

bool ReturnValue::isEqual(const Declarator& other) const
{
  return Declarator::isEqual(other);
}

bool ReturnValue::operator!=(const ReturnValue& other) const
{
  return (*this == other) == false;
}
