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

struct ReturnValue
{
  ReturnValue() :
  isVoid(false),
  isStruct(false),
  type("") {}
  bool isVoid;
  bool isStruct;
  std::string type;

  bool operator==(const ReturnValue &other) const;
  bool operator!=(const ReturnValue &other) const;
};

ReturnValue VoidReturnValue();
ReturnValue TypedReturnValue(std::string p_type);
ReturnValue StructReturnValue(std::string type);

#endif /* RETURNVALUE_H */

