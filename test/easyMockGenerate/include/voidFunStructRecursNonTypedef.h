#ifndef VOIDFUNSTRUCTRECURSNONTYPEDEF_H
#define VOIDFUNSTRUCTRECURSNONTYPEDEF_H

#ifdef __cplusplus
extern "C"
{
#endif

  struct s_s1
  {
    struct s_s1* recur;
  };

  typedef struct s_s1 t_s1;

  void voidFunStructRecursNonTypedef(t_s1* s);


#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNSTRUCTRECURSNONTYPEDEF_H */

