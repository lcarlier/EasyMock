#include "TypeItf.h"
#include "Pointer.h"
#include <cassert>

#include <cassert>
#include <boost/algorithm/string/replace.hpp>

TypeItf::TypeItf():
TypeItf("")
{
}

TypeItf::TypeItf(const std::string p_name) :
TypeItf(p_name, "")
{
}

TypeItf::TypeItf(const std::string p_name, const std::string p_typed_def_name) :
TypeItf({.name = p_name, .typed_def_name = p_typed_def_name,
        .isCType = false,
        .isStruct = false,
        .isUnion = false,
        .isPointer = false,
        .isConst = false
        })
{
}

TypeItf::TypeItf(TypeItf::attributes attrib)
{
  this->m_name = attrib.name;
  this->m_typed_def_name = attrib.typed_def_name;
  this->m_isCType = attrib.isCType;
  this->m_isStruct = attrib.isStruct;
  this->m_isUnion = attrib.isUnion;
  this->m_isPointer = attrib.isPointer;
  this->m_isConst = attrib.isConst;
}

const std::string &TypeItf::getName() const
{
  return m_name;
}

//static
std::string TypeItf::s_getFullDeclarationName(const TypeItf* type, bool fullyQualified)
{
  std::string fullDeclarationName("");
  if(type->m_isPointer)
  {
    const Pointer *ptrType = dynamic_cast<const Pointer*>(type);
    fullDeclarationName.append(s_getFullDeclarationName(ptrType->getPointedType(), fullyQualified));
    fullDeclarationName.append("* ");
  }
  if(type->m_isConst && fullyQualified)
  {
    fullDeclarationName.append("const ");
  }
  if(!type->m_typed_def_name.empty())
  {
    fullDeclarationName.append(type->m_typed_def_name);
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
  fullDeclarationName.append(type->m_name);

  return fullDeclarationName;
}

std::string TypeItf::getFullDeclarationName() const
{
  return s_getFullDeclarationName(this, true);
}

std::string TypeItf::getFullNonQualifiedDeclarationName() const
{
  return s_getFullDeclarationName(this, false);
}

const std::string& TypeItf::getTypedDefName() const
{
  return m_typed_def_name;
}

const std::string& TypeItf::getMostDefinedName() const
{
  if(!m_typed_def_name.empty())
  {
    return m_typed_def_name;
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

//Protected
void TypeItf::setTypedDefName(std::string p_typed_def_name)
{
  //It doesn't make sense that subclasses wants to clear the typedef name.
  assert(!p_typed_def_name.empty());
  m_typed_def_name = p_typed_def_name;
}

bool TypeItf::isStruct() const
{
  return m_isStruct;
}

//Protected
void TypeItf::setStruct(bool value)
{
  m_isStruct = value;
}

bool TypeItf::isUnion() const
{
  return m_isUnion;
}

//Protected
void TypeItf::setUnion(bool value)
{
  m_isUnion = value;
}

bool TypeItf::isConst() const
{
  return m_isConst;
}

TypeItf* TypeItf::setConst(bool value)
{
  m_isConst = value;

  return this;
}

ComposableField::Vector& TypeItf::getContainedFields()
{
  return const_cast<ComposableField::Vector &>(static_cast<const TypeItf &>(*this).getContainedFields());
}

const ComposableField::Vector& TypeItf::getContainedFields() const
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

bool TypeItf::isTypedDef() const
{
  return m_typed_def_name.size() != 0;
}

bool TypeItf::isAnonymous() const
{
  return m_name.empty() && m_typed_def_name.empty();
}

bool TypeItf::isComposableType() const
{
  return m_isStruct || m_isUnion;
}

bool TypeItf::isPointer() const
{
  return m_isPointer;
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
  return this->m_name == other.m_name &&
          this->m_typed_def_name == other.m_typed_def_name &&
          this->m_isCType == other.m_isCType &&
          this->m_isStruct == other.m_isStruct &&
          this->m_isUnion == other.m_isUnion &&
          this->m_isPointer == other.m_isPointer &&
          this->m_isConst == other.m_isConst;
}

bool TypeItf::operator!=(const TypeItf& other) const
{
  return (*this == other) == false;
}

TypeItf::~TypeItf()
{
}
