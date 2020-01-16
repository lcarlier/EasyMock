#ifndef STRUCTTYPE_H
#define STRUCTTYPE_H

#include "TypeItf.h"

class StructType : public TypeItf
{
public:
  explicit StructType(const std::string p_name);
  StructType(const std::string p_name, const StructField::Vector p_elem, bool p_isPointer = false);
  bool isStruct() const;
  const StructField::Vector *getContainedFields() const;
  void addStructField(StructField *newField);

  StructType(const StructType& other) = default;
  StructType& operator=(const StructType& other) = default;
  StructType(StructType &&other) = default;
  StructType& operator=(StructType &&other) = default;

  bool operator==(const StructType &other) const;
  bool operator!=(const StructType &other) const;

  StructType* clone() const;

  virtual ~StructType();
private:
  /* Don't make it constant otherwise the object is not copyable anymore */
  StructField::Vector elem;
};

#endif /* STRUCTTYPE_H */

