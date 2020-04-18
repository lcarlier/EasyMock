#ifndef VOIDFUNSTRUCTWITHTYPEDEFSTRUCT_H
#define VOIDFUNSTRUCTWITHTYPEDEFSTRUCT_H

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct
  {
    int a;
  } t_subStruct;

  typedef struct
  {
    t_subStruct sub;
  } t_struct;

  void voidFunStructWithTypedefStruct(t_struct s);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNSTRUCTWITHTYPEDEFSTRUCT_H */

