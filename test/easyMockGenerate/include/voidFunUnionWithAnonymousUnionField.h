#ifndef VOIDFUNUNIONWITHANONYMOUSUNIONFIELD_H
#define VOIDFUNUNIONWITHANONYMOUSUNIONFIELD_H

#ifdef __cplusplus
extern "C"
{
#endif

  union topAnonymousUnionField
  {
    int a;
    union
    {
      int s1;
      float s2;
    };
  };

  void voidFunUnionWithAnonymousUnionField(union topAnonymousUnionField u);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNUNIONWITHANONYMOUSUNIONFIELD_H */

