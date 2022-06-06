#include <Namespace.h>

Namespace::Namespace(std::string p_name):
    m_name{std::move(p_name)},
    m_parent{getGlobalNamespace()}
{
}

Namespace::Namespace(std::string p_name, std::shared_ptr<const Namespace> p_parent):
    m_name{std::move(p_name)},
    m_parent{std::move(p_parent)}
{
}

bool Namespace::isGlobal() const
{
  return m_parent == nullptr;
}

bool Namespace::operator==(const Namespace &other) const
{
  if(this == &other)
  {
    return true;
  }
  bool isNameSame = m_name == other.m_name;
  bool isParentSame = (m_parent == other.m_parent) ||
      (m_parent && other.m_parent && *m_parent == *other.m_parent);

  return isNameSame && isParentSame;
}

bool Namespace::operator!=(const Namespace &other) const
{
  return !(*this == other);
}

std::shared_ptr<const Namespace> getGlobalNamespace()
{
  static auto globalNamespace = std::make_shared<const Namespace>("::", nullptr);
  return globalNamespace;
}
