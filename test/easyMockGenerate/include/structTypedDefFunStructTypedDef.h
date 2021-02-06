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

  TypedDefStruct structTypedDefFunStructTypedDef(struct foo s2);

#ifdef __cplusplus
}
#endif

#endif /* VOIDSTRUCTTYPEDEF_H */

