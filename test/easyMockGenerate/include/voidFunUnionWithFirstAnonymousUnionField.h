#ifndef VOIDFUNUNIONWITHFIRSTANONYMOUSUNIONFIELD_H
#define VOIDFUNUNIONWITHFIRSTANONYMOUSUNIONFIELD_H

#ifdef __cplusplus
extern "C" {
#endif

  union topAnonymousFirstUnionField
  {
    union
    {
      int s1;
      float s2;
    };
    int a;
  };

  void voidFunUnionWithFirstAnonymousUnionField(union topAnonymousFirstUnionField u);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNUNIONWITHFIRSTANONYMOUSUNIONFIELD_H */

