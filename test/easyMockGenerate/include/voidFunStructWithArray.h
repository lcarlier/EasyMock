#ifndef VOIDFUNSTRUCTWITHARRAY_H
#define VOIDFUNSTRUCTWITHARRAY_H

#ifdef __cplusplus
extern "C"
{
#endif

#define ARRAYS_SIZE_MACRO 3

  struct structWithArray
  {
    int a[10];
    int c[ARRAYS_SIZE_MACRO + 1];
    int d[ARRAYS_SIZE_MACRO + 1], e[4], g[ARRAYS_SIZE_MACRO + 1];
    float f;
    int b[0];
  };

  void voidFunStructWithArray(struct structWithArray param);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNSTRUCTWITHARRAY_H */

