#include "TypeItf.h"

#ifndef POINTER_H
#define POINTER_H

class Pointer : public TypeItf
{
public:
  Pointer(TypeItf *type, bool isConst = false);
  Pointer(const Pointer &other);
  Pointer& operator=(Pointer other);

  bool operator==(const Pointer &other) const;
  bool operator!=(const Pointer &other) const;

  Pointer(Pointer &&other);
  //With elision pattern no need for move assignment
  virtual ~Pointer();

  const TypeItf* getPointedType() const;
  TypeItf* getPointedType();

  bool setPointedType(TypeItf* newPointedType);
  void setRecursivePointer(bool value);

  bool isEqual(const TypeItf& other) const override;

  Pointer* clone() const override;

private:
  void swap(Pointer &first, Pointer &second);
  TypeItf* m_pointedType;
  bool m_isRecursivePointer;
};

#endif /* POINTER_H */

