#include "Parameter.h"
#include "TypeItf.h"
#include "CType.h"
#include "StructType.h"

Parameter::Parameter(TypeItf* p_type, std::string p_name) :
type(p_type),
name(p_name) { }

Parameter::Parameter(const Parameter& other) :
type(other.type->clone()),
name(other.name) { }

Parameter::Parameter(Parameter&& other) :
type(nullptr)
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
  std::swap(first.name, second.name);
  std::swap(first.type, second.type);
}

Parameter* Parameter::clone() const
{
  return new Parameter(*this);
}

Parameter::~Parameter()
{
  delete type;
}

Parameter* VoidParameter(std::string p_name)
{
  Parameter *p = new Parameter(new CType(CTYPE_VOID), p_name);

  return p;
};

Parameter* NamedParameter(easyMock_cTypes_t p_type, std::string p_name)
{
  Parameter *p = new Parameter(new CType(p_type), p_name);

  return p;
};

Parameter* StructParameter(std::string p_type, std::string p_name, const StructField::Vector elem)
{
  Parameter *p = new Parameter(new StructType(p_type, elem), p_name);

  return p;
};

const std::string& Parameter::getName() const
{
  return name;
}

const TypeItf* Parameter::getType() const
{
  return type;
}


bool Parameter::operator==(const Parameter& other) const
{
  return *this->type == *other.type; //Parameters are equals only if type matches, name is not important
}

bool Parameter::operator!=(const Parameter& other) const
{
  return (*this == other) == false;
}
