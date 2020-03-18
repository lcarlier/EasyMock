#ifndef UNIONFUNUNION_H
#define UNIONFUNUNION_H

#ifdef __cplusplus
extern "C"
{
#endif

  union u1
  {
    int a;
  };

  union u2
  {
    int b;
  };

  union u1 unionFunUnion(union u2 u);

#ifdef __cplusplus
}
#endif

#endif /* UNIONFUNUNION_H */

