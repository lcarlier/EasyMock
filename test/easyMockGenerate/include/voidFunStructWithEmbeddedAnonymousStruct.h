#ifndef VOIDFUNSTRUCTWITHEMBEDDEDANONYMOUSSTRUCT_H
#define VOIDFUNSTRUCTWITHEMBEDDEDANONYMOUSSTRUCT_H

#ifdef __cplusplus
extern "C"
{
#endif

  struct topEmbeddedAnonymous
  {
    struct
    {
      int a;
    } af;
  };

  void voidFunStructWithEmbeddedAnonymousStruct(struct topEmbeddedAnonymous s);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNSTRUCTWITHEMBEDDEDANONYMOUSSTRUCT_H */

