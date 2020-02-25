#ifndef STRUCTTYPE_H
#define STRUCTTYPE_H

#include "TypeItf.h"

class StructType : public TypeItf
{
public:
  explicit StructType(const std::string p_name);
  StructType(const std::string p_name, const StructField::Vector p_elem);
  bool isStruct() const;
  const StructField::Vector *getContainedFields() const;
  void addStructField(StructField *newField);

  /*
   * There is no pointer to move so I decided not to use the
   * elision pattern
   */
  StructType(const StructType& other);
  StructType& operator=(const StructType& other);
  StructType(StructType &&other);
  //No move operator otherwise the object is not movable anymore (UT fails)

  bool operator==(const StructType &other) const;
  bool operator!=(const StructType &other) const;

  StructType* clone() const;

  virtual ~StructType();
protected:
  bool isEqual(const TypeItf& other) const override;

private:
  /* Don't make it constant otherwise the object is not copyable anymore */
  StructField::Vector m_elem;

  void correctRecursiveType(const StructType *newPtr, const StructType* oldPtrToReplace);
  friend void StructField::updateRecursiveTypePtr(const StructType* newPtr, const StructType* oldPtrToReplace);
};

#endif /* STRUCTTYPE_H */

