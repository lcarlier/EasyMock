#ifndef TEST_UNSINTFUNVOID_H
#define TEST_UNSINTFUNVOID_H

#include <FunctionFactory.h>

class UnsIntFunVoidFactory
{
public:
  static std::string getFilename() { return "unsIntFunVoid.h"; }
private:
  UnsIntFunVoidFactory();
};

template<>
Function functionFactory<UnsIntFunVoidFactory>()
{
  Function f("unsIntFunVoid", TypedReturnValue(CTYPE_UINT),{});
  return f;
}

template<>
Function* newFunctionFactory<UnsIntFunVoidFactory>()
{
  return new Function("unsIntFunVoid", TypedReturnValue(CTYPE_UINT),{});
}

#endif /* TEST_UNSINTFUNVOID_H */

