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

//Forward declare TypeItf to avoid circular include dependencies
class TypeItf;

class StructField
{
public:
  StructField(const easyMock_cTypes_t p_ctype, std::string p_name);
  StructField(TypeItf *p_type, std::string p_name);;

  typedef AutoCleanVectorPtr<StructField> Vector;

  StructField(const StructField &other);
  StructField &operator=(StructField other);

  StructField(StructField &&other);
  // No move assignment operator whenever using the elision pattern.

  bool operator==(const StructField &other) const;
  bool operator!=(const StructField &other) const;

  const TypeItf* getType() const;
  const std::string& getName() const;

  virtual StructField* clone() const;

  virtual ~StructField();

private:
  /* Do not make this constant otherwise the object is not copyable anymore */
  TypeItf *type;
  std::string name;

  friend void swap(StructField &first, StructField &second);
};

#endif /* STRUCTFIELD_H */

