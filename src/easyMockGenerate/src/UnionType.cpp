#include <UnionType.h>

UnionType::UnionType(const std::string p_name, bool p_is_embedded_in_other_type) :
UnionType(p_name, ComposableFieldItf::Vector({}), p_is_embedded_in_other_type)
{
}

UnionType::UnionType(const std::string p_name, const std::string p_type_def_name, bool p_is_embedded_in_other_type) :
UnionType(p_name, p_type_def_name, ComposableFieldItf::Vector({}), p_is_embedded_in_other_type)
{
}

UnionType::UnionType(const std::string p_name, const ComposableFieldItf::Vector p_elem, bool p_is_embedded_in_other_type) :
UnionType(p_name, "", p_elem, p_is_embedded_in_other_type)
{
}

UnionType::UnionType(const std::string p_name, const std::string p_type_def_name, const ComposableFieldItf::Vector p_elem, bool p_is_embedded_in_other_type) :
ComposableType(p_name, p_type_def_name, p_elem, p_is_embedded_in_other_type)
{
  setUnion(true);
}

UnionType* UnionType::clone() const
{
  return new UnionType(*this);
}

UnionType::~UnionType()
{
}

