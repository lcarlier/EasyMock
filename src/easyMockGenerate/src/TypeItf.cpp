#include "TypeItf.h"

TypeItf::TypeItf(const std::string p_name) :
TypeItf(p_name, "")
{ }

TypeItf::TypeItf(const std::string p_name, const std::string p_typed_def_name) :
m_name(p_name), m_typed_def_name(p_typed_def_name)
{
}


const std::string &TypeItf::getName() const
{
  return m_name;
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
  return false;
}

const StructField::Vector* TypeItf::getContainedFields() const
{
  return NULL;
}

bool TypeItf::isCType() const
{
  return false;
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
  return this->m_name == other.m_name && this->m_typed_def_name == other.m_typed_def_name;
}

bool TypeItf::operator!=(const TypeItf& other) const
{
  return (*this == other) == false;
}

TypeItf::~TypeItf()
{
}
