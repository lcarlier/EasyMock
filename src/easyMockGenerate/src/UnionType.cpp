#include <UnionType.h>

UnionType::UnionType(std::string p_name, bool p_is_embedded_in_other_type) :
UnionType(std::move(p_name), {}, p_is_embedded_in_other_type)
{
}

UnionType::UnionType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type) :
ComposableType(std::move(p_name), std::move(p_elem), p_is_embedded_in_other_type)
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
