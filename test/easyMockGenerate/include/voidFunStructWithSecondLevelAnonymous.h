#ifndef VOIDFUNSTRUCTWITHSECONDLEVELANONYMOUS_H
#define VOIDFUNSTRUCTWITHSECONDLEVELANONYMOUS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char u8;

typedef struct level2
{
  int a;
} level2_t;

typedef struct level1
{
  struct
  {
    level2_t l2;
    struct
    {
      int a;
      u8 b;
    };
    struct
    {
      int c;
      int d;
    };
  };
} level1_t;

typedef struct top
{
  struct level1 l1;
} top_t;
void voidFunStructWithSecondLevelAnonymous(top_t s);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNSTRUCTWITHSECONDLEVELANONYMOUS_H */

