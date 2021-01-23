#include "TypeItf.h"
#include "Pointer.h"
#include "FunctionType.h"
#include "QualifiedType.h"
#include "ConstQualifiedType.h"

#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>

#undef NDEBUG
#include <cassert>

TypeItf::TypeItf():
TypeItf("")
{
}

TypeItf::TypeItf(const std::string p_name) :
TypeItf(p_name, "")
{
}

TypeItf::TypeItf(const std::string p_name, const std::string p_typed_def_name) :
TypeItf({.name = p_name, .typedDefName = p_typed_def_name,
        .isCType = false,
        .isStruct = false,
        .isUnion = false,
        .isPointer = false,
        .isFunction = false,
        .isEnum = false,
        .isImplicit = false,
        .isIncompleteType = false
        })
{
}

TypeItf::TypeItf(TypeItf::attributes attrib)
{
  this->m_name = attrib.name;
  this->m_typedDefName = attrib.typedDefName;
  this->m_isCType = attrib.isCType;
  this->m_isStruct = attrib.isStruct;
  this->m_isUnion = attrib.isUnion;
  this->m_isPointer = attrib.isPointer;
  this->m_isFunction = attrib.isFunction;
  this->m_isEnum = attrib.isEnum;
  this->m_isImplicit = attrib.isImplicit;
  this->m_isIncompleteType = attrib.isIncompleteType;
}

const std::string &TypeItf::getName() const
{
  return m_name;
}

//static
std::string TypeItf::s_getFullDeclarationName(const TypeItf* type, bool fullyQualified, bool naked)
{
  const Pointer *ptrType = dynamic_cast<const Pointer*>(type);
  const TypeItf *pointedType = ptrType ? ptrType->getPointedType() : nullptr;
  const FunctionType* pointedFuncType = dynamic_cast<const FunctionType*>(pointedType);
  const QualifiedType* qualifiedType = dynamic_cast<const QualifiedType*>(type);
  std::string fullDeclarationName("");
  if(ptrType)
  {
    if(pointedFuncType)
    {
      const FunctionType* funcType = dynamic_cast<const FunctionType*>(pointedType);
      fullDeclarationName.append(funcType->getReturnType()->getDeclareString(naked));
      fullDeclarationName.append("(*");
      if(!type->m_typedDefName.empty())
      {
        fullDeclarationName.append(type->m_typedDefName);
        fullDeclarationName.append(")(");
        bool firstParam = true;
        for(const Parameter *p : funcType->getFunctionsParameters())
        {
          if(!firstParam)
          {
            fullDeclarationName.append(", ");
          }
          fullDeclarationName.append(p->getDeclareString(naked));
          firstParam = false;
        }
        fullDeclarationName.push_back(')');
      }
    }
    else
    {
      if(ptrType->isTypedDef() && !naked)
      {
        fullDeclarationName.append(pointedType->getTypedDefName());
      }
      else
      {
        fullDeclarationName.append(s_getFullDeclarationName(pointedType, fullyQualified, naked));
      }
      if(ptrType->getTypedDefName().empty() || naked)
      {
        fullDeclarationName.append("* ");
        if(pointedFuncType)
        {
          fullDeclarationName.pop_back(); //Pop the trailing space
        }
      }
    }
  }
  if(qualifiedType)
  {
    fullDeclarationName.append(s_getFullDeclarationName(qualifiedType->getType(), fullyQualified, naked));
    fullDeclarationName.push_back(' ');
    if(fullyQualified)
    {
      fullDeclarationName.append(qualifiedType->getString());
      fullDeclarationName.push_back(' ');
    }
  }
  if(!type->m_typedDefName.empty() && !naked && !pointedFuncType)
  {
    fullDeclarationName.append(type->m_typedDefName);
    return fullDeclarationName;
  }
  if(type->m_isStruct)
  {
    fullDeclarationName.append("struct ");
  }
  if(type->m_isUnion)
  {
    fullDeclarationName.append("union ");
  }
  if(type->m_isEnum)
  {
    fullDeclarationName.append("enum ");
  }
  fullDeclarationName.append(type->m_name);
  boost::trim_right(fullDeclarationName);

  return fullDeclarationName;
}

std::string TypeItf::getFullDeclarationName(bool p_naked) const
{
  return s_getFullDeclarationName(this, true, p_naked);
}

std::string TypeItf::getFullNonQualifiedDeclarationName(bool p_naked) const
{
  return s_getFullDeclarationName(this, false, p_naked);
}

const std::string& TypeItf::getTypedDefName() const
{
  return m_typedDefName;
}

const std::string& TypeItf::getMostDefinedName() const
{
  if(!m_typedDefName.empty())
  {
    return m_typedDefName;
  }
  else
  {
    return m_name;
  }
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
  m_isFunction = value;
}

void TypeItf::setEnum(bool value)
{
  m_isEnum = value;
}

void TypeItf::setIncompleteType(bool value)
{
  m_isIncompleteType = value;
}

bool TypeItf::isTypedDef() const
{
  return m_typedDefName.size() != 0;
}

bool TypeItf::isAnonymous() const
{
  //Pointer types are never anonymous
  const ConstQualifiedType* constType = dynamic_cast<const ConstQualifiedType*>(this);
  return !constType && !m_isPointer && m_name.empty() && m_typedDefName.empty();
}

bool TypeItf::isComposableType() const
{
  return !m_isIncompleteType && (m_isStruct || m_isUnion);
}

bool TypeItf::isPointer() const
{
  return !m_isIncompleteType && m_isPointer;
}

bool TypeItf::isFunction() const
{
  return !m_isIncompleteType && m_isFunction;
}

bool TypeItf::isEnum() const
{
  return !m_isIncompleteType && m_isEnum;
}

bool TypeItf::isIncompleteType() const
{
  return m_isIncompleteType;
}

easyMock_cTypes_t TypeItf::getCType() const
{
  return CTYPE_INVALID;
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
          this->m_typedDefName == other.m_typedDefName &&
          this->m_isCType == other.m_isCType &&
          this->m_isStruct == other.m_isStruct &&
          this->m_isUnion == other.m_isUnion &&
          this->m_isPointer == other.m_isPointer &&
          this->m_isFunction == other.m_isFunction &&
          this->m_isEnum == other.m_isEnum &&
          this->m_isImplicit == other.m_isImplicit &&
          this->m_isIncompleteType == other.m_isIncompleteType;
}

bool TypeItf::operator!=(const TypeItf& other) const
{
  return (*this == other) == false;
}

TypeItf::~TypeItf()
{
}
