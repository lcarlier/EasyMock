#include <QualifiedType.h>

QualifiedType::QualifiedType() :
TypeItf{ "", "" }, m_type { nullptr }
{
}

QualifiedType::QualifiedType(TypeItf* p_type) :
TypeItf { "", "" }, m_type { p_type }
{
}

QualifiedType::QualifiedType(const QualifiedType& p_other) :
TypeItf { p_other }, m_type { p_other.m_type->clone() }
{
}

QualifiedType& QualifiedType::operator=(QualifiedType p_other)
{
  TypeItf::operator=(p_other);
  swap(*this, p_other);

  return *this;
}

/*QualifiedType::QualifiedType(const QualifiedType&& p_other) :
TypeItf { p_other }, m_type { nullptr }
{
  swap(*this, p_other);
}*/

const TypeItf* QualifiedType::getType() const
{
  return m_type;
}

TypeItf* QualifiedType::getType()
{
  return const_cast<TypeItf*>(static_cast<const QualifiedType &>(*this).getType());
}

bool QualifiedType::isConst() const
{
  return false;
}

const char* QualifiedType::getString() const
{
  return "QualifiedType::getString() must be overriden";
}

TypeItf* QualifiedType::clone() const
{
  return new QualifiedType(*this);
}

void swap(QualifiedType& first, QualifiedType& second)
{
  using std::swap;
  swap(first.m_type, second.m_type);
}

bool QualifiedType::operator==(const QualifiedType& p_other) const
{
  return isEqual(p_other);
}

bool QualifiedType::operator!=(const QualifiedType& p_other) const
{
  return !(*this == p_other);
}

bool QualifiedType::isEqual(const TypeItf& p_other) const
{
  bool parentEq = TypeItf::isEqual(p_other);
  const QualifiedType* otherQualifiedType = dynamic_cast<const QualifiedType*>(&p_other);
  if(!otherQualifiedType)
  {
    return false;
  }
  bool typeEq = *m_type == *otherQualifiedType->m_type;

  return parentEq && typeEq;
}

QualifiedType::~QualifiedType()
{
  delete m_type;
}

