#ifndef COMPOSABLEFIELD_H
#define COMPOSABLEFIELD_H

#include "AutoCleanVectorPtr.h"
#include "EasyMockGenerateTypes.h"

#include "Declarator.h"

#include <string>

//Forward declare TypeItf to avoid circular include dependencies
class TypeItf;
class ComposableType;

class ComposableField : public Declarator
{
public:
  typedef struct
  {
    bool isPointer;
    bool isArray;
    uint64_t arraySize; //Only valid if isArray is true
    bool isRecursiveTypeField;
  } attributes;
  ComposableField(const easyMock_cTypes_t p_ctype, std::string p_name);
  ComposableField(TypeItf *p_type, std::string p_name);
  ComposableField(TypeItf *p_type, std::string p_name, attributes p_attrib);

  void updateRecursiveTypePtr(const ComposableType *ptr, const ComposableType* toReplace);
  bool isRecursiveTypeField() const;

  typedef AutoCleanVectorPtr<ComposableField> Vector;

  ComposableField(const ComposableField &other);
  ComposableField &operator=(ComposableField other);

  ComposableField(ComposableField &&other);
  // No move assignment operator whenever using the elision pattern.

  bool operator==(const ComposableField &other) const;
  bool operator!=(const ComposableField &other) const;

  TypeItf* getType() override;
  const TypeItf* getType() const override;
  const std::string& getName() const;
  void setType(TypeItf* type) override;
  bool isArray() const;
  bool isBoundSpecifiedArray() const;
  bool isUnboundSpecifiedArray() const;
  bool isAnonymous() const;
  bool setArray(bool value);
  bool setArraySize(uint64_t size);
  uint64_t getArraySize() const;

  virtual ComposableField* clone() const;

  virtual ~ComposableField();

private:
  /* Do not make this constant otherwise the object is not copyable anymore */
  std::string m_name;
  //Shadow copy of recursive that which cannot be modified
  const ComposableType* m_recursiveType;
  bool m_isArray;
  uint64_t m_arraySize; //Only valid if m_isArray is true

  friend void swap(ComposableField &first, ComposableField &second);
};

#endif /* STRUCTFIELD_H */

