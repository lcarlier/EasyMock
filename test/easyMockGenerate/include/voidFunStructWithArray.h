#ifndef VOIDFUNSTRUCTWITHARRAY_H
#define VOIDFUNSTRUCTWITHARRAY_H

#ifdef __cplusplus
extern "C"
{
#endif

  struct structWithArray
  {
    int a[10];
    float f;
    int b[0];
  };

  void voidFunStructWithArray(struct structWithArray param);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNSTRUCTWITHARRAY_H */

