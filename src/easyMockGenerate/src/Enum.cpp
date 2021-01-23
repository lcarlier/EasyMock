#include "Enum.h"

Enum::Enum(const std::string p_name):
Enum { p_name, "" }
{
}

Enum::Enum(const std::string p_name, const std::string p_typed_def_name):
TypeItf { p_name, p_typed_def_name }
{
  setEnum(true);
}

Enum *Enum::clone() const
{
  return new Enum(*this);
}

Enum::~Enum() {
}

