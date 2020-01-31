/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReturnValue.h
 * Author: lcarlier
 *
 * Created on July 24, 2019, 11:42 PM
 */

#ifndef RETURNVALUE_H
#define RETURNVALUE_H

#include <string>
#include <EasyMockGenerateTypes.h>
#include "Declarator.h"

//Forward declare to avoid cycle dependencies
class TypeItf;
class StructType;

class ReturnValue : public Declarator
{
  ReturnValue();
  explicit ReturnValue(TypeItf *type);
  ReturnValue(TypeItf *type, bool isPointer);

  ReturnValue(const ReturnValue &other);
  ReturnValue& operator=(ReturnValue other);

  ReturnValue(ReturnValue &&other);
  //With elision pattern no need for move assignment

  bool operator==(const ReturnValue &other) const;
  bool operator!=(const ReturnValue &other) const;

  virtual ~ReturnValue();
private:
  friend void swap(ReturnValue &first, ReturnValue &second);
};

ReturnValue VoidReturnValue(bool p_isPointer = false);
ReturnValue TypedReturnValue(easyMock_cTypes_t p_type, bool p_isPointer = false);
ReturnValue StructReturnValue(StructType* type, bool p_isPointer = false);

#endif /* RETURNVALUE_H */

