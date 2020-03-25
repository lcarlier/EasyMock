#ifndef VOIDFUNSTRUCTWITHEMBEDDEDSTRUCT_H
#define VOIDFUNSTRUCTWITHEMBEDDEDSTRUCT_H

#ifdef __cplusplus
extern "C"
{
#endif

  struct topEmbedded
  {
    struct embeddedStruct
    {
      int a;
    } b;
  };

  void voidFunStructWithEmbeddedStruct(struct topEmbedded t);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNSTRUCTWITHEMBEDDEDSTRUCT_H */

