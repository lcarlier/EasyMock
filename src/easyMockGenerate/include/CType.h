/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CType.h
 * Author: lcarlier
 *
 * Created on July 25, 2019, 8:24 PM
 */

#ifndef CTYPE_H
#define CTYPE_H

#include "TypeItf.h"
#include "easyMock_framework.h"

class CType : public TypeItf
{
public:
  CType();
  CType(const easyMock_cTypes_t p_cType);
  const easyMock_cTypes_t getCType() const override;
  bool setUnsigned(bool val);
  void setCType(easyMock_cTypes_t p_cType);

  CType(const CType &other) = default;
  CType& operator=(const CType &other) = default;
  CType(CType &&other) = default;
  CType& operator=(CType &&other) = default;
  bool operator==(const CType &other) const;
  bool operator!=(const CType &other) const;

  CType *clone() const override;
  /*
   * bool isEqual(const TypeItf &other);
   * Doesn't need to be overridden because the name is updated whenever the CType object changes.
   * Therefore relying on the operator== of TypeItf is good enough because the name is reliable
   */
private:
  easyMock_cTypes_t m_cType;
};

#endif /* CTYPE_H */

