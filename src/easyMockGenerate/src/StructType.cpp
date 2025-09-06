#include "StructType.h"
#include "Namespace.h"

StructType::StructType(std::string p_name, bool p_is_embedded_in_other_type) :
StructType(std::move(p_name), {}, p_is_embedded_in_other_type, getGlobalNamespace())
{
}

StructType::StructType(std::string p_name, bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace) :
StructType(std::move(p_name), {}, p_is_embedded_in_other_type, std::move(p_namespace))
{
}

StructType::StructType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type):
StructType(std::move(p_name), std::move(p_elem), p_is_embedded_in_other_type, getGlobalNamespace())
{
}

StructType::StructType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace) :
ComposableType(std::move(p_name), std::move(p_elem), p_is_embedded_in_other_type, std::move(p_namespace))
{
  setStruct(true);
}

const char* StructType::getComposableTypeKeyword() const
{
  return "struct";
}
