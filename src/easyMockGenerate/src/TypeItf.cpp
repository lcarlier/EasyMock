#include "TypeItf.h"

TypeItf::TypeItf(const std::string p_name, bool p_isPointer) :
m_name(p_name), m_isPointer(false)
{
  //Use the set pointer to also change the name
  this->setPointer(p_isPointer);
}

const std::string &TypeItf::getName() const
{
  return m_name;
}

void TypeItf::setName(std::string p_name)
{
  m_name = p_name;
  if(m_isPointer)
  {
    m_name.append("*");
  }
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

bool TypeItf::isPointer() const
{
  return m_isPointer;
}

bool TypeItf::setPointer(bool isPointer)
{
  if(!m_isPointer && isPointer)
  {
    m_name.push_back('*');
  } else if (m_isPointer && !isPointer)
  {
    m_name.pop_back(); //Remove *
  }
  m_isPointer = isPointer;
  return true;
}

bool TypeItf::operator==(const TypeItf& other) const
{
  return this->m_name == other.m_name && this->m_isPointer == other.m_isPointer;
}

bool TypeItf::operator!=(const TypeItf& other) const
{
  return (*this == other) == false;
}


TypeItf::~TypeItf()
{
}
