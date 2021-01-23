#include <ConstQualifiedType.h>

ConstQualifiedType::ConstQualifiedType(TypeItf *p_type) :
QualifiedType { p_type }
{
}

ConstQualifiedType& ConstQualifiedType::operator=(ConstQualifiedType p_other)
{
  QualifiedType::operator=(p_other);
  swap(*this, p_other);

  return *this;
}

ConstQualifiedType::ConstQualifiedType(ConstQualifiedType&& p_other) :
QualifiedType { p_other }
{
  swap(*this, p_other);
}

bool ConstQualifiedType::isConst() const
{
  return true;
}

const char* ConstQualifiedType::getString() const
{
  return "const";
}

bool ConstQualifiedType::operator==(const ConstQualifiedType& p_other) const
{
  return isEqual(p_other);
}

bool ConstQualifiedType::operator!=(const ConstQualifiedType& p_other) const
{
  return !(*this == p_other);
}

void swap(ConstQualifiedType& first, ConstQualifiedType& second)
{
  swap(dynamic_cast<QualifiedType&>(first), dynamic_cast<QualifiedType&>(second));
}

TypeItf* ConstQualifiedType::clone() const
{
  return new ConstQualifiedType(*this);
}

bool ConstQualifiedType::isEqual(const TypeItf& p_other) const
{
  bool parentEq = QualifiedType::isEqual(p_other);
  const ConstQualifiedType* otherConstQualifiedType = dynamic_cast<const ConstQualifiedType*>(&p_other);

  return parentEq && otherConstQualifiedType != nullptr;
}
