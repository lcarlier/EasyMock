#include "TypeItf.h"
#include <cassert>

#include <cassert>
#include <boost/algorithm/string/replace.hpp>

TypeItf::TypeItf(const std::string p_name) :
TypeItf(p_name, "")
{
}

TypeItf::TypeItf(const std::string p_name, const std::string p_typed_def_name) :
TypeItf({.name = p_name, .typed_def_name = p_typed_def_name,
        .isCType = false, .isStruct = false, .isUnion = false})
{
}

TypeItf::TypeItf(TypeItf::attributes attrib)
{
  this->m_name = attrib.name;
  this->m_typed_def_name = attrib.typed_def_name;
  this->m_isCType = attrib.isCType;
  this->m_isStruct = attrib.isStruct;
  this->m_isUnion = attrib.isUnion;
}

const std::string &TypeItf::getName() const
{
  return m_name;
}

const std::string TypeItf::getFullDeclarationName() const
{
  if(!m_typed_def_name.empty())
  {
    return m_typed_def_name;
  }
  std::string fullDeclarationName("");
  if(m_isStruct)
  {
    fullDeclarationName.append("struct ");
  }
  if(m_isUnion)
  {
    fullDeclarationName.append("union ");
  }
  fullDeclarationName.append(this->getName());

  return fullDeclarationName;
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
          this->m_isUnion == other.m_isUnion;
}

bool TypeItf::operator!=(const TypeItf& other) const
{
  return (*this == other) == false;
}

TypeItf::~TypeItf()
{
}
