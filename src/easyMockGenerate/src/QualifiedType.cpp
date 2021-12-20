#include <QualifiedType.h>
#include <boost/functional/hash.hpp>

QualifiedType::QualifiedType() :
QualifiedType{ nullptr }
{
}

QualifiedType::QualifiedType(std::shared_ptr<TypeItf> p_type) :
TypeItf { "" }, m_type { std::move(p_type) }
{
  setQualifiedType(true);
}

const TypeItf* QualifiedType::getUnqualifiedType() const
{
  return m_type.get();
}

void QualifiedType::setUnqualifiedType(std::shared_ptr<TypeItf> p_newUnqualifiedType)
{
  m_type = std::move(p_newUnqualifiedType);
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

std::size_t QualifiedType::getHash() const noexcept
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
}
