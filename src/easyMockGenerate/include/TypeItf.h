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
  explicit TypeItf(const std::string p_name);
  TypeItf(const std::string p_name, const std::string p_typed_def_name);

  typedef AutoCleanVectorPtr<TypeItf> Vector;

  TypeItf(const TypeItf &other) = default;
  TypeItf& operator=(const TypeItf &other) = default;
  TypeItf(TypeItf &&other) = default;
  TypeItf& operator=(TypeItf &&other) = default;

  const std::string &getName() const;
  const std::string &getTypedDefName() const;
  virtual const easyMock_cTypes_t getCType() const;

  virtual bool isStruct() const;
  virtual const StructField::Vector *getContainedFields() const;
  virtual bool isCType() const;
  bool isTypedDef() const;

  bool operator==(const TypeItf &other) const;
  bool operator!=(const TypeItf &other) const;

  virtual TypeItf* clone() const = 0;
  virtual ~TypeItf();
protected:
  virtual bool isEqual(const TypeItf &other) const;
  void setName(std::string p_name);
  void setTypedDefName(std::string p_typed_def_name);
  std::string m_name;
  std::string m_typed_def_name;
};

#endif /* TYPEITF_H */

