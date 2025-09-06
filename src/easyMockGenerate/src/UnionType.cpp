#include <UnionType.h>
#include <Namespace.h>

UnionType::UnionType(std::string p_name, bool p_is_embedded_in_other_type) :
UnionType(std::move(p_name), {}, p_is_embedded_in_other_type, getGlobalNamespace())
{
}

UnionType::UnionType(std::string p_name, bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace) :
UnionType(std::move(p_name), {}, p_is_embedded_in_other_type, std::move(p_namespace))
{
}

UnionType::UnionType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type):
UnionType(std::move(p_name), std::move(p_elem), p_is_embedded_in_other_type, getGlobalNamespace())
{
}

UnionType::UnionType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace):
ComposableType(std::move(p_name), std::move(p_elem), p_is_embedded_in_other_type, std::move(p_namespace))
{
  setUnion(true);
}

const char* UnionType::getComposableTypeKeyword() const
{
  return "union";
}

UnionType::~UnionType()
{
}
