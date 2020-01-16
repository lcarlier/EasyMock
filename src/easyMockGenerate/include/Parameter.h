/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parameter.h
 * Author: lcarlier
 *
 * Created on July 24, 2019, 11:40 PM
 */

#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

#include "EasyMockGenerateTypes.h"
#include "StructField.h"

//Forward declare TypeItf to avoid circular import dependency
class TypeItf;

class Parameter
{
public:
  Parameter(TypeItf *p_type, std::string p_name);

  typedef AutoCleanVectorPtr<Parameter> Vector;

  Parameter(const Parameter &other);
  Parameter& operator=(Parameter other);

  Parameter(Parameter &&other);
  //With elision pattern no need for move assignment

  bool operator==(const Parameter &other) const;
  bool operator!=(const Parameter &other) const;

  const TypeItf* getType() const;
  const std::string &getName() const;

  virtual ~Parameter();

  virtual Parameter* clone() const;

private:
  /* Do not make the member const otherwise they are not copyable anymore */
  TypeItf *type;
  std::string name;

  friend void swap(Parameter &first, Parameter &second);
};

Parameter *VoidParameter(std::string p_name);
Parameter *NamedParameter(easyMock_cTypes_t p_type, std::string p_name, bool p_isPointer = false);
Parameter *StructParameter(std::string type, std::string name, const StructField::Vector elem);


#endif /* PARAMETER_H */

