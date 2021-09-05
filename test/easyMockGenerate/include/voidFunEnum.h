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

  struct structTestEmbeddedEnum
  {
    enum
    {
      NINE = 9,
      TEN = 10
    } embeddedEnum;
  };

  void voidFunStructEmbeddedEnumType(struct structTestEmbeddedEnum s);

  void voidFunUnnamedEnumParam(enum enumTestParam);

  //The name of the enum is a substring of the function name. This trigger a bug sometimes and needs to be tested
  enum enumTestParam enumTest();

  /*
   * C++ doesn't accept function declared with non defined enum while C is ok with that.
   */
#ifdef __cplusplus
  enum nonDefinedEnum{};
#endif
  enum nonDefinedEnum nonDefinedEnumFunVoid();

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNENUM_H */

