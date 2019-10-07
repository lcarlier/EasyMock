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
  CType(const easyMock_cTypes_t p_cType);
  bool isCType() const;
  const easyMock_cTypes_t getCType() const;

  CType(const CType &other) = default;
  CType& operator=(const CType &other) = default;
  CType(CType &&other) = default;
  CType& operator=(CType &&other) = default;
  bool operator==(const CType &other) const;
  bool operator!=(const CType &other) const;

  CType *clone() const;
private:
  easyMock_cTypes_t m_cType;
};

#endif /* CTYPE_H */

