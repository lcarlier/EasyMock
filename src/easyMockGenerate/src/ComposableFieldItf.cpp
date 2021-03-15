#include <ComposableFieldItf.h>

#include <boost/functional/hash.hpp>

ComposableFieldItf::ComposableFieldItf(TypeItf* p_type, std::string& p_name) :
Declarator(p_type), m_name(p_name)
{
}

bool ComposableFieldItf::isComposableField() const
{
  return false;
}

bool ComposableFieldItf::isComposableBitfield() const
{
  return false;
}

bool ComposableFieldItf::isAnonymous() const
{
  return m_name.empty();
}

const std::string& ComposableFieldItf::getName() const
{
  return m_name;
}

std::size_t ComposableFieldItf::getHash() const
{
  std::size_t seed { Declarator::getHash() };
  boost::hash_combine(seed, m_name);

  return seed;
}

bool ComposableFieldItf::isEqual(const Declarator& p_other) const
{
  bool parentEq = Declarator::isEqual(p_other);
  const ComposableFieldItf* o_composableField = dynamic_cast<const ComposableFieldItf*>(&p_other);
  if(!o_composableField)
  {
    return false;
  }
  bool nameEq = m_name == o_composableField->m_name;
  return parentEq && nameEq;
}
