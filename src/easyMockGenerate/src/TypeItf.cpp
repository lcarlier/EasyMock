#include "TypeItf.h"
#include "Pointer.h"
#include "FunctionType.h"
#include "QualifiedType.h"
#include "ConstQualifiedType.h"
#include "TypedefType.h"
#include "Enum.h"
#include "ComposableType.h"
#include "IncompleteType.h"
#include "EasyMock_CType.h"

#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/functional/hash.hpp>

#undef NDEBUG
#include <cassert>

TypeItf::TypeItf():
TypeItf("")
{
}

TypeItf::TypeItf(const std::string p_name) :
TypeItf({.name = p_name,
        .isCType = false,
        .isStruct = false,
        .isUnion = false,
        .isPointer = false,
        .isFunctionType = false,
        .isEnum = false,
        .isImplicit = false,
        .isIncompleteType = false,
        .isTypedefType = false,
        .isQualifiedType = false,
        .typedefName = {}
        })
{
}

TypeItf::TypeItf(TypeItf::attributes attrib)
{
  m_name = attrib.name;
  m_isCType = attrib.isCType;
  m_isStruct = attrib.isStruct;
  m_isUnion = attrib.isUnion;
  m_isPointer = attrib.isPointer;
  m_isFunctionType = attrib.isFunctionType;
  m_isEnum = attrib.isEnum;
  m_isImplicit = attrib.isImplicit;
  m_isIncompleteType = attrib.isIncompleteType;
  m_isTypedefType = attrib.isTypedefType;
  m_isQualifiedType = attrib.isQualifiedType;
  m_typedefName = attrib.typedefName;
}

const std::string &TypeItf::getName() const
{
  return m_name;
}

//Protected
void TypeItf::setName(std::string p_name)
{
  //It doesn't make sense that subclasses wants to clear the name.
  assert(!p_name.empty());
  m_name = p_name;
}

bool TypeItf::isStruct() const
{
  return !m_isIncompleteType && m_isStruct;
}

//Protected
void TypeItf::setStruct(bool value)
{
  m_isStruct = value;
}

bool TypeItf::isUnion() const
{
  return !m_isIncompleteType && m_isUnion;
}

//Protected
void TypeItf::setUnion(bool value)
{
  m_isUnion = value;
}

bool TypeItf::isConst() const
{
  return dynamic_cast<const ConstQualifiedType*>(this) != nullptr;
}

bool TypeItf::isImplicit() const
{
  return !m_isIncompleteType && m_isImplicit;
}

TypeItf* TypeItf::setImplicit(bool value)
{
  m_isImplicit = value;

  return this;
}

const TypeItf* TypeItf::unqualify() const
{
  const TypeItf* unqualifiedType = this;
  while(unqualifiedType->m_isQualifiedType)
  {
    unqualifiedType = static_cast<const QualifiedType*>(this)->getUnqualifiedType();
  }
  return unqualifiedType;
}

TypeItf* TypeItf::unqualify()
{
  return const_cast<TypeItf*>(static_cast<const TypeItf*>(this)->unqualify());
}

ComposableFieldItf::Vector& TypeItf::getContainedFields()
{
  return const_cast<ComposableFieldItf::Vector &>(static_cast<const TypeItf &>(*this).getContainedFields());
}

const ComposableFieldItf::Vector& TypeItf::getContainedFields() const
{
  fprintf(stderr, "THIS FUNCTION SHOULDN'T BE CALLED");
  assert(false);
  //NO return is OK
}

bool TypeItf::isCType() const
{
  return m_isCType;
}

const CType* TypeItf::asCType() const
{
  if(!this->isCType())
  {
    return nullptr;
  }
  return static_cast<const CType*>(this);
}

CType* TypeItf::asCType()
{
  return const_cast<CType*>(static_cast<const TypeItf*>(this)->asCType());
}

bool TypeItf::isTypedDef() const
{
  return m_isTypedefType;
}

const TypedefType* TypeItf::asTypedefType() const
{
  if(!this->isTypedDef())
  {
    return nullptr;
  }
  return static_cast<const TypedefType*>(this);
}

TypedefType* TypeItf::asTypedefType()
{
  return const_cast<TypedefType*>(static_cast<const TypeItf*>(this)->asTypedefType());
}

//Protected
void TypeItf::setCType(bool value)
{
  m_isCType = value;
}

void TypeItf::setPointer(bool value)
{
  m_isPointer = value;
}

void TypeItf::setFunction(bool value)
{
  m_isFunctionType = value;
}

void TypeItf::setEnum(bool value)
{
  m_isEnum = value;
}

void TypeItf::setIncompleteType(bool value)
{
  m_isIncompleteType = value;
}

void TypeItf::setTypedefType(bool value)
{
  m_isTypedefType = value;
}

void TypeItf::setQualifiedType(bool value)
{
  m_isQualifiedType = value;
}

bool TypeItf::isAnonymous() const
{
  const TypeItf* rawType = this->getRawType();
  /*
   * Note:
   * Only composable type or enum type can be anonymous
   */
  return (rawType->isComposableType() || rawType->isEnum()) && m_name.empty() && m_typedefName.empty();
}

bool TypeItf::isComposableType() const
{
  return !m_isIncompleteType && (m_isStruct || m_isUnion);
}

const ComposableType* TypeItf::asComposableType() const
{
  if(!isComposableType())
  {
    return nullptr;
  }
  return static_cast<const ComposableType*>(this);
}

ComposableType* TypeItf::asComposableType()
{
  return const_cast<ComposableType*>(static_cast<const TypeItf*>(this)->asComposableType());
}

bool TypeItf::isPointer() const
{
  return !m_isIncompleteType && unqualify()->m_isPointer;
}

const Pointer* TypeItf::asPointer() const
{
  if(!isPointer())
  {
    return nullptr;
  }
  return static_cast<const Pointer*>(unqualify());
}

Pointer* TypeItf::asPointer()
{
  return const_cast<Pointer*>(static_cast<const TypeItf*>(this)->asPointer());
}

bool TypeItf::isFunctionType() const
{
  return !m_isIncompleteType && m_isFunctionType;
}

const FunctionType* TypeItf::asFunctionType() const
{
  if(!this->isFunctionType())
  {
    return nullptr;
  }
  return static_cast<const FunctionType*>(this);
}

FunctionType* TypeItf::asFunctionType()
{
  return const_cast<FunctionType*>(static_cast<const TypeItf*>(this)->asFunctionType());
}

bool TypeItf::isEnum() const
{
  return !m_isIncompleteType && m_isEnum;
}

const Enum* TypeItf::asEnum() const
{
  if(!m_isEnum)
  {
    return nullptr;
  }
  return static_cast<const Enum*>(this);
}

Enum* TypeItf::asEnum()
{
  return const_cast<Enum*>(static_cast<const TypeItf*>(this)->asEnum());
}

bool TypeItf::isIncompleteType() const
{
  return m_isIncompleteType;
}

const IncompleteType* TypeItf::asIncompleteType() const
{
  if(!m_isIncompleteType)
  {
    return nullptr;
  }
  return static_cast<const IncompleteType*>(this);
}

IncompleteType* TypeItf::asIncompleteType()
{
  return const_cast<IncompleteType*>(static_cast<const TypeItf*>(this)->asIncompleteType());
}

bool TypeItf::isQualified() const
{
  return m_isQualifiedType;
}

const QualifiedType* TypeItf::asQualifiedType() const
{
  if(!m_isQualifiedType)
  {
    return nullptr;
  }
  return static_cast<const QualifiedType*>(this);
}

QualifiedType* TypeItf::asQualifiedType()
{
  return const_cast<QualifiedType*>(static_cast<const TypeItf*>(this)->asQualifiedType());
}

/*
 * int var <--> t_int var;            // typedef int t_int
 * int (*var) <--> p_a (var);         // typedef int* var
 * struct f (var) <--> t_f (var);     // typedef struct f t_f
 * const int (var) <--> c_int (var);  // typedef const int c_int
 */
std::string TypeItf::getFullDeclarationName(bool p_naked) const
{
  const std::string prefix = getDeclarationPrefix(p_naked);
  const std::string postfix = getDeclarationPostfix(p_naked);
  std::string toReturn { prefix + std::string { " " } + postfix};

  while(toReturn.back() == ' ')
  {
    toReturn.pop_back();
  }
  return toReturn;
}

easyMock_cTypes_t TypeItf::getCType() const
{
  return CTYPE_INVALID;
}


const TypeItf* TypeItf::getRawType() const
{
  const Pointer* pointerType = asPointer();
  if(pointerType)
  {
    return pointerType->getPointedType()->getRawType();
  }

  const QualifiedType* qualifiedType = asQualifiedType();
  if(qualifiedType)
  {
    return qualifiedType->getUnqualifiedType()->getRawType();
  }

  const TypedefType* typedefType = asTypedefType();
  if(typedefType)
  {
    return typedefType->getTypee()->getRawType();
  }

  return this;
}

TypeItf* TypeItf::getRawType()
{
  return const_cast<TypeItf*>(static_cast<const TypeItf*>(this)->getRawType());
}

std::string TypeItf::getDeclarationPostfix(bool p_naked) const
{
  return "";
}

std::size_t TypeItf::getHash() const
{
  std::size_t seed { 0 };
  boost::hash_combine(seed, m_name);
  boost::hash_combine(seed, m_isCType);
  boost::hash_combine(seed, m_isStruct);
  boost::hash_combine(seed, m_isUnion);
  boost::hash_combine(seed, m_isPointer);
  boost::hash_combine(seed, m_isFunctionType);
  boost::hash_combine(seed, m_isEnum);
  boost::hash_combine(seed, m_isImplicit);
  boost::hash_combine(seed, m_isIncompleteType);
  boost::hash_combine(seed, m_isTypedefType);
  boost::hash_combine(seed, m_isQualifiedType);
  boost::hash_combine(seed, m_typedefName);

  return seed;
}

bool TypeItf::operator==(const TypeItf& other) const
{
  return this->isEqual(other);
}

bool TypeItf::isEqual(const TypeItf& other) const
{
  bool isAnonymousEqual = this->isAnonymous() == other.isAnonymous();
  return isAnonymousEqual &&
          this->m_name == other.m_name &&
          this->m_isCType == other.m_isCType &&
          this->m_isStruct == other.m_isStruct &&
          this->m_isUnion == other.m_isUnion &&
          this->m_isPointer == other.m_isPointer &&
          this->m_isFunctionType == other.m_isFunctionType &&
          this->m_isEnum == other.m_isEnum &&
          this->m_isImplicit == other.m_isImplicit &&
          this->m_isIncompleteType == other.m_isIncompleteType &&
          this->m_isTypedefType == other.m_isTypedefType &&
          this->m_isQualifiedType == other.m_isQualifiedType &&
          this->m_typedefName == other.m_typedefName;
}

bool TypeItf::operator!=(const TypeItf& other) const
{
  return (*this == other) == false;
}
