#include "StructField.h"
#include "TypeItf.h"
#include "CType.h"

StructField::StructField(const easyMock_cTypes_t p_ctype, std::string p_name) :
type(new CType(p_ctype)), name(p_name)
{
}

StructField::StructField(TypeItf* p_type, std::string p_name) :
type(p_type),
name(p_name)
{
}

StructField::StructField(const StructField& other) :
type(other.type->clone()),
name(other.name) { }

StructField& StructField::operator=(StructField other)
{
  swap(*this, other);

  return *this;
}

StructField::StructField(StructField&& other) :
type(nullptr)
{
  swap(*this, other);
}

void swap(StructField &first, StructField &second)
{
  std::swap(first.name, second.name);
  std::swap(first.type, second.type);
}

bool StructField::operator==(const StructField& other) const
{
  return this->name == other.name && *this->type == *other.type;
}

bool StructField::operator!=(const StructField& other) const
{
  return (*this == other) == false;
}

const std::string& StructField::getName() const
{
  return name;
}

const TypeItf* StructField::getType() const
{
  return type;
}


StructField* StructField::clone() const
{
  return new StructField(*this);
}

StructField::~StructField()
{
  delete type;
}
