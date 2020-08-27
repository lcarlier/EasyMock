#ifndef VOIDFUNFUNTYPEDEFFUNPTR_H
#define VOIDFUNFUNTYPEDEFFUNPTR_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef int(*funPtrType)(int, float);

  void voidFunTypedefFunPtr(funPtrType funPtr);

  funPtrType TypedefFunPtrVoid();

  struct typeDefPtrFunField
  {
    funPtrType funPtr;
  };

  int intFunStructTypeDefPtrFunField(struct typeDefPtrFunField ptrToFunField);

  struct topAnonymousStructTypeDefPtrFunField
  {
    int a;
    struct
    {
      funPtrType funPtr;
    };
  };

  int intFunStructTypeDefPtrAnonFunField(struct topAnonymousStructTypeDefPtrFunField ptrToStructAnonFunField);


#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNFUNTYPEDEFFUNPTR_H */

