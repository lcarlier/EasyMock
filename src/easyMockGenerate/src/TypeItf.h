/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Type.h
 * Author: lcarlier
 *
 * Created on July 24, 2019, 11:39 PM
 */

#ifndef TYPEITF_H
#define TYPEITF_H

#include <string>
#include "CodeParserItf.h"
#include "AutoCleanVectorPtr.h"
#include "StructField.h"

class TypeItf
{
public:
  TypeItf(const std::string p_name);

  typedef AutoCleanVectorPtr<TypeItf> Vector;

  TypeItf(const TypeItf &other) = default;
  TypeItf& operator=(const TypeItf &other) = default;
  TypeItf(TypeItf &&other) = default;
  TypeItf& operator=(TypeItf &&other) = default;

  const std::string &getName() const;
  virtual bool isStruct() const;
  virtual const StructField::Vector *getContainedFields() const;
  virtual bool isCType() const;
  virtual const easyMock_cTypes_t getCType() const;

  bool operator==(const TypeItf &other) const;
  bool operator!=(const TypeItf &other) const;

  virtual TypeItf* clone() const = 0;
  virtual ~TypeItf();
private:
  //Don't make it const because otherwise TypeItf objects and its derivatives are not assignable or movable anymore
  /* const */std::string m_name;
};

#endif /* TYPEITF_H */

