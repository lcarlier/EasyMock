#ifndef COMPILETWOFUNCTIONS_H
#define COMPILETWOFUNCTIONS_H

#ifdef __cplusplus
extern "C"
{
#endif

  struct twoFunStruct
  {
    int a;
  };

  int compileTwoFunctions(struct twoFunStruct s);
  int f2(struct twoFunStruct s);

#ifdef __cplusplus
}
#endif

#endif /* COMPILETWOFUNCTIONS_H */

