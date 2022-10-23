#include <ClassType.h>

ClassType::ClassType(std::string p_name, bool p_is_embedded_in_other_type):
    ClassType(std::move(p_name), {}, p_is_embedded_in_other_type)
{}

ClassType::ClassType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem,
                     bool p_is_embedded_in_other_type):
    ComposableType(std::move(p_name), std::move(p_elem), std::move(p_is_embedded_in_other_type))
{
  // A struct is a class
  setStruct(true);
}

const char *ClassType::getComposableTypeKeyword() const
{
  return "class";
}