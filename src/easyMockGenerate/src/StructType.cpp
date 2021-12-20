#include "StructType.h"

StructType::StructType(const std::string p_name, bool p_is_embedded_in_other_type) :
StructType(p_name, {}, p_is_embedded_in_other_type)
{
}

StructType::StructType(const std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type) :
ComposableType(p_name, std::move(p_elem), p_is_embedded_in_other_type)
{
  setStruct(true);
}

const char* StructType::getComposableTypeKeyword() const
{
  return "struct";
}

StructType::~StructType()
{
}
