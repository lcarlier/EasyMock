#ifndef VOIDFUNUNIONWITHEMBEDDEDUNION_H
#define VOIDFUNUNIONWITHEMBEDDEDUNION_H

#ifdef __cplusplus
extern "C"
{
#endif

  union topEmbeddedUnion
  {
    union embeddedUnion
    {
      int a;
      float b;
    } eu;
  };

  void voidFunUnionWithEmbeddedUnion(union topEmbeddedUnion u);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNUNIONWITHEMBEDDEDUNION_H */

