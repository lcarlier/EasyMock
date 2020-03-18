#ifndef UNIONTYPE_HPP
#define UNIONTYPE_HPP

#include "ComposableType.h"

class UnionType : public ComposableType {
public:
  explicit UnionType(const std::string p_name);
  UnionType(const std::string p_name, const std::string p_type_def_name);
  UnionType(const std::string p_name, const ComposableField::Vector p_elem);
  UnionType(const std::string p_name, const std::string p_type_def_name, const ComposableField::Vector p_elem);

  UnionType* clone() const override;

  virtual ~UnionType();
};

#endif /* UNIONTYPE_HPP */

