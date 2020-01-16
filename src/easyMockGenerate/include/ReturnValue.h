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

//Forward declare to avoid cycle dependencies
class TypeItf;
class StructType;

class ReturnValue
{
  ReturnValue();
  ReturnValue(TypeItf *type);

  ReturnValue(const ReturnValue &other);
  ReturnValue& operator=(ReturnValue other);

  ReturnValue(ReturnValue &&other);
  //With elision pattern no need for move assignment

  const TypeItf* getType() const;
  void setType(TypeItf* type);
  const std::string& getTypeName() const;

  bool operator==(const ReturnValue &other) const;
  bool operator!=(const ReturnValue &other) const;

  virtual ~ReturnValue();
private:
  TypeItf *m_type;

  friend void swap(ReturnValue &first, ReturnValue &second);
};

ReturnValue VoidReturnValue(bool p_isPointer = false);
ReturnValue TypedReturnValue(easyMock_cTypes_t p_type);
ReturnValue StructReturnValue(StructType* type);

#endif /* RETURNVALUE_H */

