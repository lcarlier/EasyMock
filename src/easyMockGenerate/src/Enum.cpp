#include "Enum.h"

Enum::Enum(const std::string p_name, const std::string p_typed_def_name, const bool p_is_const):
TypeItf(p_name, p_typed_def_name)
{
  setConst(p_is_const);
  setEnum(true);
}

Enum *Enum::clone() const
{
  return new Enum(*this);
}

Enum::~Enum() {
}

