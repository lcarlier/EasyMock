#ifndef VOIDFUNSTRUCTWITHFIRSTANONYMOUSSTRUCTFIELD_H
#define VOIDFUNSTRUCTWITHFIRSTANONYMOUSSTRUCTFIELD_H

#ifdef __cplusplus
extern "C" {
#endif

  struct topAnonymousFirstStructField
  {
    struct
    {
      int s1;
      float s2;
    };
    int a;
  };

  void voidFunStructWithFirstAnonymousStructField(struct topAnonymousFirstStructField t);


#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNSTRUCTWITHFIRSTANONYMOUSSTRUCTFIELD_H */

