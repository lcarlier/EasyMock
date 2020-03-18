#include "TypeItf.h"

TypeItf::TypeItf(const std::string p_name) :
TypeItf(p_name, "")
{ }

TypeItf::TypeItf(const std::string p_name, const std::string p_typed_def_name) :
m_name(p_name), m_typed_def_name(p_typed_def_name),
m_isCType(false), m_isStruct(false), m_isUnion(false)
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

void TypeItf::setName(std::string p_name)
{
  m_name = p_name;
}

void TypeItf::setTypedDefName(std::string p_typed_def_name)
{
  m_typed_def_name = p_typed_def_name;
}

bool TypeItf::isStruct() const
{
  return m_isStruct;
}

bool TypeItf::isUnion() const
{
  return m_isUnion;
}

const ComposableField::Vector* TypeItf::getContainedFields() const
{
  return NULL;
}

bool TypeItf::isCType() const
{
  return m_isCType;
}

bool TypeItf::isTypedDef() const
{
  return m_typed_def_name.size() != 0;
}

const easyMock_cTypes_t TypeItf::getCType() const
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
