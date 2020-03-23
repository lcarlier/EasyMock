#include "StructType.h"

StructType::StructType(const std::string p_name, bool p_is_embedded_in_other_type) :
StructType(p_name, ComposableField::Vector({}), p_is_embedded_in_other_type)
{
}

StructType::StructType(const std::string p_name, const std::string p_type_def_name, bool p_is_embedded_in_other_type) :
StructType(p_name, p_type_def_name, ComposableField::Vector({}), p_is_embedded_in_other_type)
{
}

StructType::StructType(const std::string p_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type) :
StructType(p_name, "", p_elem, p_is_embedded_in_other_type)
{
}

StructType::StructType(const std::string p_name, const std::string p_type_def_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type) :
ComposableType(p_name, p_type_def_name, p_elem, p_is_embedded_in_other_type)
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
