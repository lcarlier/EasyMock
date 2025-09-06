#include <ClassType.h>
#include <Namespace.h>

ClassType::ClassType(std::string p_name, bool p_is_embedded_in_other_type):
    ClassType(std::move(p_name), {}, p_is_embedded_in_other_type, getGlobalNamespace())
{}

ClassType::ClassType(std::string p_name, bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace):
    ClassType(std::move(p_name), {}, p_is_embedded_in_other_type, std::move(p_namespace))
{}

ClassType::ClassType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type):
ClassType(std::move(p_name), std::move(p_elem), p_is_embedded_in_other_type, getGlobalNamespace())
{
}

ClassType::ClassType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem,
                     bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace):
    ComposableType(std::move(p_name), std::move(p_elem), p_is_embedded_in_other_type, std::move(p_namespace))
{
  // A struct is a class
  setStruct(true);
}

const char *ClassType::getComposableTypeKeyword() const
{
  return "class";
}