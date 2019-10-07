#include "StructType.h"

StructType::StructType(const std::string p_name, const StructField::Vector p_elem) :
TypeItf(p_name), elem(p_elem)
{ }

bool StructType::operator==(const StructType& other) const
{
  return TypeItf::operator==(other) && this->elem == other.elem;
}

bool StructType::operator!=(const StructType& other) const
{
  return (*this == other) == false;
}

StructType* StructType::clone() const
{
  return new StructType(*this);
}

const StructField::Vector* StructType::getContainedFields() const
{
  return &elem;
}

bool StructType::isStruct() const
{
  return true;
}

StructType::~StructType() { }

