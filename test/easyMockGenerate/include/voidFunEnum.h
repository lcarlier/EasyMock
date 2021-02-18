#ifndef VOIDFUNENUM_H
#define VOIDFUNENUM_H

#ifdef __cplusplus
extern "C" {
#endif

  enum enumTestParam
  {
    ONE = 1,
    TWO = 2
  };

  void voidFunEnum(enum enumTestParam e);
  void voidFunPtrEnum(enum enumTestParam* e);

  typedef enum
  {
    ZERO,
    FOUR = 4
  } t_enumTestRv;
  t_enumTestRv enumFunVoid();

  typedef enum enumStruct
  {
    THREE = 3,
    FIVE = 5
  } t_enumStruct;
  struct structTestEnum
  {
    enum enumStruct e;
  };

  void voidFunStructEnum(struct structTestEnum s);

  struct structTestAnonyStructEnum
  {
    int a;
    struct
    {
      t_enumStruct e;
    };
  };

  void voidFunStructAnonStructEnum(struct structTestAnonyStructEnum s);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNENUM_H */

