#ifndef VOIDFUNFUNPTR_H
#define VOIDFUNFUNPTR_H

#ifdef __cplusplus
extern "C" {
#endif

  void voidFunFunPtr(int    (   *funPtr  )   (    int    ,    float    )   );

  /*
   * cdecl> declare funPtrFunPtr as function(param as pointer to function(float, float) returning pointer to function(char, char) returning double) returning int
   */
  int funPtrFunPtr(double (*(*)(float, float))(char, char));

  /*
   * cdecl> declare funPtrFunChar as function (char) returning pointer to function (int, float) returning int
   */
  int (*funPtrFunChar(char))(int,float);

  /*
   * cdecl> declare foo as function(int) returning pointer to function(float, float) returning pointer to function(char, char) returning double
   */
  double (* (* ptrFunToFunFunInt(int ))(float, float))(char, char);

  struct ptrFunField
  {
      int (*funPtr)(int, float);
  };

  int intFunStructPtrFunField(struct ptrFunField ptrToFunField);

  struct topAnonymousStructPtrFunField
  {
    int a;
    struct
    {
      int (*funPtr)(int, float);
    };
  };

  int intFunStructPtrAnonFunField(struct topAnonymousStructPtrFunField ptrToStructAnonFunField);

  /*
   * TO BE ENABLED WHEN SUPPORT OF CONST POINTER IS ADDED
   */
#if 0
  /*
   * cdecl> declare constFunPtrFunInt as function(int) returning const pointer to function(float) returning int
   */
  int (* const constFunPtrFunInt(int ))(float );
#endif

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNFUNPTR_H */

