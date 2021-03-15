#ifndef VOIDSTRUCTANONTYPEDEF_H
#define VOIDSTRUCTANONTYPEDEF_H

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct
  {
    int a;
  } TypedDefAnonymousStruct;

  typedef struct
  {
    int a;
  } TypedDefAnonymousStruct2;

  TypedDefAnonymousStruct structAnonymousTypedDefFunStructAnonymousTypedDef(TypedDefAnonymousStruct s1, TypedDefAnonymousStruct2 s2);

#ifdef __cplusplus
}
#endif

#endif /* VOIDSTRUCTANONTYPEDEF_H */

