#ifndef VOIDSTRUCTTYPEDEF_H
#define VOIDSTRUCTTYPEDEF_H

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct foo
  {
    int a;
  } TypedDefStruct;

  TypedDefStruct structTypedDefFunStructTypedDef(TypedDefStruct s2);

#ifdef __cplusplus
}
#endif

#endif /* VOIDSTRUCTTYPEDEF_H */

