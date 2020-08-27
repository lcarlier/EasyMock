#ifndef VOIDFUNENUM_H
#define VOIDFUNENUM_H

#ifdef __cplusplus
extern "C" {
#endif

  enum enumTest
  {
    ONE = 1,
    TWO = 2
  };

  void voidFunEnum(enum enumTest e);
  void voidFunPtrEnum(enum enumTest* e);

  enum enumTest enumFunVoid();

  struct structTestEnum
  {
    enum enumTest e;
  };

  void voidFunStructEnum(struct structTestEnum s);

  struct structTestAnonyStructEnum
  {
    int a;
    struct
    {
      enum enumTest e;
    };
  };

  void voidFunStructAnonStructEnum(struct structTestAnonyStructEnum s);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNENUM_H */

