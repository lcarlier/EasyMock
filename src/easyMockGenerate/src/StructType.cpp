#include "StructType.h"

StructType::StructType(std::string p_name, bool p_is_embedded_in_other_type) :
StructType(std::move(p_name), {}, p_is_embedded_in_other_type)
{
}

StructType::StructType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type) :
ComposableType(std::move(p_name), std::move(p_elem), p_is_embedded_in_other_type)
{
  setStruct(true);
}

const char* StructType::getComposableTypeKeyword() const
{
  return "struct";
}
