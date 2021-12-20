#include <ComposableFieldItf.h>
#include <ComposableBitfield.h>
#include <ComposableField.h>

#include <boost/functional/hash.hpp>

ComposableFieldItf::ComposableFieldItf(std::shared_ptr<TypeItf> p_type, std::string p_name) :
Declarator(std::move(p_type)), m_name(std::move(p_name))
{
}

bool ComposableFieldItf::isComposableField() const
{
  return false;
}

const ComposableField* ComposableFieldItf::asComposableField() const
{
  if(!isComposableBitfield())
  {
    return nullptr;
  }
  return static_cast<const ComposableField*>(this);
}

ComposableField* ComposableFieldItf::asComposableField()
{
  return const_cast<ComposableField*>(static_cast<const ComposableFieldItf*>(this)->asComposableField());
}

bool ComposableFieldItf::isComposableBitfield() const
{
  return false;
}

const ComposableBitfield* ComposableFieldItf::asComposableBitfield() const
{
  if(!isComposableBitfield())
  {
    return nullptr;
  }
  return static_cast<const ComposableBitfield*>(this);
}

ComposableBitfield* ComposableFieldItf::asComposableBitfield()
{
  return const_cast<ComposableBitfield*>(static_cast<const ComposableFieldItf*>(this)->asComposableBitfield());
}

bool ComposableFieldItf::isAnonymous() const
{
  return m_name.empty();
}

const std::string& ComposableFieldItf::getName() const
{
  return m_name;
}

std::size_t ComposableFieldItf::getHash() const noexcept
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
