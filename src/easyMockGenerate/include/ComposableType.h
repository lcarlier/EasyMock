#ifndef COMPOSABLETYPE_H
#define COMPOSABLETYPE_H

#include "TypeItf.h"

class ComposableType : public TypeItf
{
public:
  explicit ComposableType(const std::string p_name);
  ComposableType(const std::string p_name, const std::string p_type_def_name);
  ComposableType(const std::string p_name, const ComposableField::Vector p_elem);
  ComposableType(const std::string p_name, const std::string p_type_def_name, const ComposableField::Vector p_elem);
  const ComposableField::Vector *getContainedFields() const;
  void addStructField(ComposableField *newField);

  /*
   * There is no pointer to move so I decided not to use the
   * elision pattern
   */
  ComposableType(const ComposableType& other);
  ComposableType& operator=(const ComposableType& other);
  ComposableType(ComposableType &&other);
  //No move operator otherwise the object is not movable anymore (UT fails)

  bool operator==(const ComposableType &other) const;
  bool operator!=(const ComposableType &other) const;

  virtual ~ComposableType() = 0; //pure virtual. ComposableType shouldn't be instantiable
protected:
  bool isEqual(const TypeItf& other) const override;

private:
  /* Don't make it constant otherwise the object is not copyable anymore */
  ComposableField::Vector m_elem;

  void correctRecursiveType(const ComposableType *newPtr, const ComposableType* oldPtrToReplace);
  friend void ComposableField::updateRecursiveTypePtr(const ComposableType* newPtr, const ComposableType* oldPtrToReplace);
};

#endif /* COMPOSABLETYPE_H */

