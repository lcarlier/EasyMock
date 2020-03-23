#ifndef UNIONTYPE_HPP
#define UNIONTYPE_HPP

#include "ComposableType.h"

class UnionType : public ComposableType {
public:
  UnionType(const std::string p_name, bool p_is_embedded_in_other_type);
  UnionType(const std::string p_name, const std::string p_type_def_name, bool p_is_embedded_in_other_type);
  UnionType(const std::string p_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type);
  UnionType(const std::string p_name, const std::string p_type_def_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type);

  UnionType* clone() const override;

  virtual ~UnionType();
};

#endif /* UNIONTYPE_HPP */

