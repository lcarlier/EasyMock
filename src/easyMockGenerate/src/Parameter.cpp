#include "Parameter.h"
#include "TypeItf.h"
#include "CType.h"
#include "StructType.h"
#include "Pointer.h"

Parameter::Parameter(TypeItf* p_type, std::string p_name) :
Declarator(p_type), m_name(p_name)
{
}

Parameter::Parameter(const Parameter& other) :
Declarator(other), m_name(other.m_name)
{
}

Parameter::Parameter(Parameter&& other):
Declarator(other)
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
  TypeItf *curType = new CType(p_type);
  if(p_isPointer)
  {
    curType = new Pointer(curType);
  }
  Parameter *p = new Parameter(curType, p_name);

  return p;
}

Parameter* StructParameter(std::string p_type, std::string p_name, const ComposableField::Vector elem, bool p_is_embedded_in_other_type)
{
  Parameter *p = new Parameter(new StructType(p_type, elem, p_is_embedded_in_other_type), p_name);

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
