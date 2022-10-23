#include <Namespace.h>

#include <boost/functional/hash.hpp>

Namespace::Namespace(std::string p_name):
    Namespace(std::move(p_name), getGlobalNamespace())
{
}

Namespace::Namespace(std::string p_name, std::shared_ptr<const Namespace> p_parent):
    m_name{std::move(p_name)},
    m_parent{std::move(p_parent)},
    m_cachedHash{0}
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

std::size_t Namespace::getHash() const noexcept
{
  if(m_cachedHash)
  {
    return m_cachedHash;
  }
  std::size_t seed = m_parent ? m_parent->getHash() : 0;
  boost::hash_combine(seed, m_name);

  return seed;
}

void Namespace::cacheHash() noexcept
{
  m_cachedHash = getHash();
}

namespace boost
{
  std::size_t hash_value(Namespace const& p_namespace)
  {
    return p_namespace.getHash();
  }
}
