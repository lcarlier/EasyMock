#include "Parameter.h"
#include "TypeItf.h"
#include "CType.h"
#include "StructType.h"

Parameter::Parameter(TypeItf* p_type, std::string p_name) :
Parameter(p_type, p_name, false)
{
}

Parameter::Parameter(TypeItf* p_type, std::string p_name, bool isPointer) :
Declarator(p_type, isPointer), m_name(p_name)
{
}

Parameter::Parameter(const Parameter& other) :
Parameter(other.m_type->clone(), other.m_name, other.m_isPointer)
{
}

Parameter::Parameter(Parameter&& other)
{
  swap(*this, other);
}

Parameter& Parameter::operator=(Parameter other)
{
  swap(*this, other);

  return *this;
}

void swap(Parameter& first, Parameter& second)
{
  swap(static_cast<Declarator &>(first), static_cast<Declarator &>(second));
  std::swap(first.m_name, second.m_name);
}

Parameter* Parameter::clone() const
{
  return new Parameter(*this);
}

Parameter::~Parameter()
{
}

Parameter* VoidParameter(std::string p_name)
{
  Parameter *p = new Parameter(new CType(CTYPE_VOID), p_name);

  return p;
}

Parameter* NamedParameter(easyMock_cTypes_t p_type, std::string p_name, bool p_isPointer)
{
  Parameter *p = new Parameter(new CType(p_type), p_name, p_isPointer);

  return p;
}

Parameter* StructParameter(std::string p_type, std::string p_name, const StructField::Vector elem)
{
  Parameter *p = new Parameter(new StructType(p_type, elem), p_name);

  return p;
}

const std::string& Parameter::getName() const
{
  return m_name;
}

bool Parameter::operator==(const Parameter& other) const
{
  if(Declarator::operator==(other))
  {
    return true; //Parameters are equals only if type matches, name is not important
  }
  else
  {
    return false;
  }
}

bool Parameter::operator!=(const Parameter& other) const
{
  return (*this == other) == false;
}
