#include <ConstQualifiedType.h>

#include <boost/functional/hash.hpp>

#include <cassert>

ConstQualifiedType::ConstQualifiedType(std::shared_ptr<TypeItf> p_type) :
QualifiedType { std::move(p_type) }
{
  if(p_type)
  {
    assert(!p_type->isConst());
  }
}

bool ConstQualifiedType::isConst() const
{
  return true;
}

const char* ConstQualifiedType::getQualifierString() const
{
  return "const";
}

std::size_t ConstQualifiedType::getHash() const noexcept
{
  std::size_t seed { QualifiedType::getHash() };
  return seed;
}

bool ConstQualifiedType::operator==(const TypeItf& p_other) const
{
  return isEqual(p_other);
}

bool ConstQualifiedType::operator!=(const TypeItf& p_other) const
{
  return !(*this == p_other);
}

void swap(ConstQualifiedType& first, ConstQualifiedType& second)
{
  swap(dynamic_cast<QualifiedType&>(first), dynamic_cast<QualifiedType&>(second));
}

bool ConstQualifiedType::isEqual(const TypeItf& p_other) const
{
  bool parentEq = QualifiedType::isEqual(p_other);
  const ConstQualifiedType* otherConstQualifiedType = dynamic_cast<const ConstQualifiedType*>(&p_other);

  return parentEq && otherConstQualifiedType != nullptr;
}
