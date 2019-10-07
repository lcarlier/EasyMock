#ifndef STRUCTFUNSTRUCT_H
#define STRUCTFUNSTRUCT_H

#ifdef __cplusplus
extern "C"
{
#endif

  struct s1
  {
    int a;
    float b;
  };

  struct s2
  {
    int c;
    float d;
    struct s1 s;
  };

  struct s1 structFunStruct(s2 s);


#ifdef __cplusplus
}
#endif

#endif /* STRUCTFUNSTRUCT_H */

