#ifndef VOIDFUNSTRUCTWITHANONYMOUSSTRUCTFIELD_H
#define VOIDFUNSTRUCTWITHANONYMOUSSTRUCTFIELD_H

#ifdef __cplusplus
extern "C"
{
#endif

  struct topAnonymousStructField
  {
    int a;
    struct
    {
      int s1;
      float s2;
    };
  };

  void voidFunStructWithAnonymousStructField(struct topAnonymousStructField t);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNSTRUCTWITHANONYMOUSSTRUCTFIELD_H */

