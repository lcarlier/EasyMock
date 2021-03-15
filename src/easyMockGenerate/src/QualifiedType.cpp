#include <QualifiedType.h>
#include <boost/functional/hash.hpp>

QualifiedType::QualifiedType() :
QualifiedType{ nullptr }
{
}

QualifiedType::QualifiedType(TypeItf* p_type) :
TypeItf { "" }, m_type { p_type }
{
  setQualifiedType(true);
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

const TypeItf* QualifiedType::getUnqualifiedType() const
{
  return m_type;
}

TypeItf* QualifiedType::getUnqualifiedType()
{
  return const_cast<TypeItf*>(static_cast<const QualifiedType &>(*this).getUnqualifiedType());
}

bool QualifiedType::isConst() const
{
  return false;
}

const char* QualifiedType::getQualifierString() const
{
  return "QualifiedType::getString() must be overridden";
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

std::size_t QualifiedType::getHash() const
{
  std::size_t seed { TypeItf::getHash() };
  boost::hash_combine(seed, *m_type);

  return seed;
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

std::string QualifiedType::getDeclarationPrefix(bool p_naked) const
{
  return m_type->getFullDeclarationName(p_naked) + std::string { " " } + std::string { getQualifierString() };
}

QualifiedType::~QualifiedType()
{
  delete m_type;
}
