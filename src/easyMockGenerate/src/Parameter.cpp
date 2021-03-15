#include "Parameter.h"
#include "TypeItf.h"
#include "EasyMock_CType.h"
#include "StructType.h"
#include "Pointer.h"

#include <boost/functional/hash.hpp>

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

Parameter* StructParameter(std::string p_type, std::string p_name, const ComposableFieldItf::Vector elem, bool p_is_embedded_in_other_type)
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
  return this->isEqual(other);
}

std::size_t Parameter::getHash() const
{
  std::size_t seed { Declarator::getHash() };
  //Parameters are equals only if type matches, name is not important

  return seed;
}

bool Parameter::isEqual(const Declarator& other) const
{
  //Parameters are equals only if type matches, name is not important
  return Declarator::isEqual(other);
}

bool Parameter::operator!=(const Parameter& other) const
{
  return (*this == other) == false;
}
