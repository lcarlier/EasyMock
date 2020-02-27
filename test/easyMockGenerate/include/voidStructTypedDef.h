/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   voidStructTypeDef.h
 * Author: lcarlier
 *
 * Created on February 27, 2020, 8:07 AM
 */

#ifndef VOIDSTRUCTTYPEDEF_H
#define VOIDSTRUCTTYPEDEF_H

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct
  {
  } TypedDefAnonynousStruct;

  typedef struct foo
  {
  } TypedDefStruct;

  void voidStructTypedDef(TypedDefAnonynousStruct s1, TypedDefStruct s2);

#ifdef __cplusplus
}
#endif

#endif /* VOIDSTRUCTTYPEDEF_H */

