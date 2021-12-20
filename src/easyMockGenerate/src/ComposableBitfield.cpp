#include <ComposableBitfield.h>

#include <EasyMock_CType.h>
#include <TypedefType.h>

#include <boost/functional/hash.hpp>
#include <cassert>

ComposableBitfield::ComposableBitfield(easyMock_cTypes_t p_type, std::string p_name, uint8_t p_size) :
ComposableBitfield(std::make_shared<CType>(p_type), std::move(p_name), p_size)
{
}

ComposableBitfield::ComposableBitfield(std::shared_ptr<TypeItf> p_type, std::string p_name, uint8_t p_size) :
ComposableFieldItf(std::move(p_type), std::move(p_name)), m_size(p_size)
{
  TypeItf* typeItf = getType();
  assert(typeItf);
  TypedefType* typedefType = typeItf->asTypedefType();
  if(typedefType)
  {
    assert(typedefType->getMostDefinedTypee()->isCType());
  }
  else
  {
    assert(typeItf->isCType());
  }
}

bool ComposableBitfield::operator==(const ComposableBitfield &other) const
{
  return this->isEqual(other);
}

std::size_t ComposableBitfield::getHash() const noexcept
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

ComposableBitfield::~ComposableBitfield()
{
}
