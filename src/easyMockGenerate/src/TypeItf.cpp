#include "TypeItf.h"

TypeItf::TypeItf(const std::string p_name) :
m_name(p_name)
{}

const std::string &TypeItf::getName() const
{
  return m_name;
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

const easyMock_cTypes_t TypeItf::getCType() const
{
  return CTYPE_INVALID;
}

bool TypeItf::operator==(const TypeItf& other) const
{
  return this->m_name == other.m_name;
}

bool TypeItf::operator!=(const TypeItf& other) const
{
  return (*this == other) == false;
}


TypeItf::~TypeItf()
{
}
