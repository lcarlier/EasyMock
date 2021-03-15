#include <ComposableBitfield.h>

#include <EasyMock_CType.h>

#include <boost/functional/hash.hpp>

ComposableBitfield::ComposableBitfield(easyMock_cTypes_t p_type, std::string p_name, uint8_t p_size) :
ComposableBitfield(new CType(p_type), p_name, p_size)
{
}

ComposableBitfield::ComposableBitfield(CType* p_type, std::string p_name, uint8_t p_size) :
ComposableFieldItf(p_type, p_name), m_size(p_size)
{
}

bool ComposableBitfield::operator==(const ComposableBitfield &other) const
{
  return this->isEqual(other);
}

std::size_t ComposableBitfield::getHash() const
{
  std::size_t seed { ComposableFieldItf::getHash() };
  boost::hash_combine(seed, m_size);

  return seed;
}

bool ComposableBitfield::isEqual(const Declarator& p_other) const
{
  const bool declaratorEqual = ComposableFieldItf::isEqual(p_other);
  const ComposableBitfield* otherBitfield = dynamic_cast<const ComposableBitfield*>(&p_other);
  if(!otherBitfield)
  {
    return false;
  }
  const bool sizeEqual = this->m_size == otherBitfield->m_size;

  return declaratorEqual && sizeEqual;
}

bool ComposableBitfield::operator!=(const ComposableBitfield &other) const
{
  return !(*this == other);
}

bool ComposableBitfield::isComposableBitfield() const
{
  return true;
}

uint8_t ComposableBitfield::getSize() const
{
  return m_size;
}

ComposableBitfield* ComposableBitfield::clone() const
{
  return new ComposableBitfield(*this);
}

ComposableBitfield::~ComposableBitfield()
{
}
