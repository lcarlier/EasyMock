#ifndef VOIDFUNUNIONWITHEMBEDDEDANONYMOUSUNION_H
#define VOIDFUNUNIONWITHEMBEDDEDANONYMOUSUNION_H

#ifdef __cplusplus
extern "C"
{
#endif

  union topEmbeddedAnonymousUnion
  {
    union
    {
      int a;
      float b;
    } eau;
  };

  void voidFunUnionWithEmbeddedAnonymousUnion(union topEmbeddedAnonymousUnion u);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNUNIONWITHEMBEDDEDANONYMOUSUNION_H */

