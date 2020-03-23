#ifndef VOIDFUNSTRUCTWITHEMBEDDEDSTRUCT_H
#define VOIDFUNSTRUCTWITHEMBEDDEDSTRUCT_H

#ifdef __cplusplus
extern "C"
{
#endif

  struct top
  {
    struct embeddedStruct
    {
      int a;
    } b;
  };

  void voidFunStructWithEmbeddedStruct(struct top t);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNSTRUCTWITHEMBEDDEDSTRUCT_H */

