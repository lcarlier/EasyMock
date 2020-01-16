#include "StructType.h"

StructType::StructType(const std::string p_name) :
StructType(p_name, {}, false)
{ }

StructType::StructType(const std::string p_name, const StructField::Vector p_elem, bool p_isPointer) :
TypeItf(p_name, p_isPointer), elem(p_elem)
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

void StructType::addStructField(StructField* newField)
{
  elem.push_back(newField);
}


bool StructType::isStruct() const
{
  return true;
}

StructType::~StructType() { }

