#include "Enum.h"

Enum::Enum(const std::string p_name):
Enum { p_name, "" }
{
}

Enum::Enum(const std::string p_name, const std::string p_typed_def_name):
TypeItf { p_name, p_typed_def_name }
{
  setEnum(true);
}

void Enum::addEnumValue(int64_t p_value, const std::string& p_enumStr)
{
  m_listOfValues.emplace(p_value, p_enumStr);
}

const Enum::listOfValuesType& Enum::getValues() const
{
  return m_listOfValues;
}

bool Enum::isEqual(const TypeItf& p_other) const
{
  bool parentEqual = TypeItf::isEqual(p_other);
  const Enum *otherEnum = dynamic_cast<const Enum*>(&p_other);
  if(!otherEnum || !parentEqual)
  {
    return false;
  }
  bool listOfValueEqual = m_listOfValues == otherEnum->m_listOfValues;

  return parentEqual && listOfValueEqual;
}

Enum *Enum::clone() const
{
  return new Enum(*this);
}

Enum::~Enum() {
}

