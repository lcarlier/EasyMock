/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StructField.h
 * Author: lcarlier
 *
 * Created on July 24, 2019, 11:41 PM
 */

#ifndef STRUCTFIELD_H
#define STRUCTFIELD_H

#include <string>
#include "AutoCleanVectorPtr.h"
#include "EasyMockGenerateTypes.h"

#include "Declarator.h"

//Forward declare TypeItf to avoid circular include dependencies
class TypeItf;
class StructType;

class StructField : public Declarator
{
public:
  typedef struct
  {
    bool isPointer;
    bool isArray;
    uint64_t arraySize; //Only valid if isArray is true
    bool isRecursiveTypeField;
  } attributes;
  StructField(const easyMock_cTypes_t p_ctype, std::string p_name);
  StructField(TypeItf *p_type, std::string p_name);
  StructField(TypeItf *p_type, std::string p_name, attributes p_attrib);

  void updateRecursiveTypePtr(StructType *ptr);
  bool isRecursiveTypeField() const;

  typedef AutoCleanVectorPtr<StructField> Vector;

  StructField(const StructField &other);
  StructField &operator=(StructField other);

  StructField(StructField &&other);
  // No move assignment operator whenever using the elision pattern.

  bool operator==(const StructField &other) const;
  bool operator!=(const StructField &other) const;

  const TypeItf* getType() const override;
  const std::string& getName() const;
  void setType(TypeItf* type) override;
  bool isArray() const;
  bool isBoundSpecifiedArray() const;
  bool isUnboundSpecifiedArray() const;
  bool setArray(bool value);
  bool setArraySize(uint64_t size);
  uint64_t getArraySize() const;

  virtual StructField* clone() const;

  virtual ~StructField();

private:
  /* Do not make this constant otherwise the object is not copyable anymore */
  std::string m_name;
  //Shadow copy of recursive that which cannot be modified
  const TypeItf* m_recursiveType;
  bool m_isArray;
  uint64_t m_arraySize; //Only valid if m_isArray is true

  friend void swap(StructField &first, StructField &second);
};

#endif /* STRUCTFIELD_H */

