#include <UnionType.h>

UnionType::UnionType(const std::string p_name) :
UnionType(p_name, ComposableField::Vector({}))
{
}

UnionType::UnionType(const std::string p_name, const std::string p_type_def_name) :
UnionType(p_name, p_type_def_name, {})
{
}

UnionType::UnionType(const std::string p_name, const ComposableField::Vector p_elem) :
UnionType(p_name, "", p_elem)
{
}

UnionType::UnionType(const std::string p_name, const std::string p_type_def_name, const ComposableField::Vector p_elem) :
ComposableType(p_name, p_type_def_name, p_elem)
{
  m_isUnion = true;
}

UnionType* UnionType::clone() const
{
  return new UnionType(*this);
}

UnionType::~UnionType()
{
}

