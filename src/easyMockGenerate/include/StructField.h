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
  StructField(const easyMock_cTypes_t p_ctype, std::string p_name);
  StructField(TypeItf *p_type, std::string p_name);
  StructField(TypeItf *p_type, std::string p_name, bool p_recursiveTypeField);

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

  virtual StructField* clone() const;

  virtual ~StructField();

private:
  /* Do not make this constant otherwise the object is not copyable anymore */
  std::string m_name;
  TypeItf* m_recursiveType;

  friend void swap(StructField &first, StructField &second);
};

#endif /* STRUCTFIELD_H */

