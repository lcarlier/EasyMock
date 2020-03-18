#include "StructType.h"

StructType::StructType(const std::string p_name) :
StructType(p_name, ComposableField::Vector({}))
{
}

StructType::StructType(const std::string p_name, const std::string p_type_def_name) :
StructType(p_name, p_type_def_name, {})
{
}

StructType::StructType(const std::string p_name, const ComposableField::Vector p_elem) :
StructType(p_name, "", p_elem)
{
}

StructType::StructType(const std::string p_name, const std::string p_type_def_name, const ComposableField::Vector p_elem) :
ComposableType(p_name, p_type_def_name, p_elem)
{
  m_isStruct = true;
}

StructType* StructType::clone() const
{
  return new StructType(*this);
}

StructType::~StructType()
{
}
