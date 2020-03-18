#ifndef STRUCTTYPE_H
#define STRUCTTYPE_H

#include "ComposableType.h"

class StructType : public ComposableType
{
public:
  explicit StructType(const std::string p_name);
  StructType(const std::string p_name, const std::string p_type_def_name);
  StructType(const std::string p_name, const ComposableField::Vector p_elem);
  StructType(const std::string p_name, const std::string p_type_def_name, const ComposableField::Vector p_elem);
  virtual ~StructType();

  StructType* clone() const override;

  StructType(const StructType& other) = default;
  StructType& operator=(const StructType& other) = default;
  StructType(StructType &&other) = default;
};

#endif /* STRUCTTYPE_H */

