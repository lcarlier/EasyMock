#ifndef STRUCTWITHUNIONFUNSTRUCTWITHUNION_H
#define STRUCTWITHUNIONFUNSTRUCTWITHUNION_H

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct
  {
    union ut
    {
      int a;
      float b;
    } u;
  } sWithUnion;

  sWithUnion structWithUnionFunStructWithUnion(sWithUnion st);

#ifdef __cplusplus
}
#endif

#endif /* STRUCTWITHUNIONFUNSTRUCTWITHUNION_H */

