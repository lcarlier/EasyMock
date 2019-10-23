#ifndef TEST_INTFUNVOID_H
#define TEST_INTFUNVOID_H

#include <FunctionFactory.h>

class IntFunVoidFactory
{
public:
  static std::string getFilename() { return "intFunVoid.h"; }
private:
  IntFunVoidFactory();
};

template<>
Function functionFactory<IntFunVoidFactory>()
{
  Function f("intFunVoid", TypedReturnValue(CTYPE_INT),{});
  return f;
}

template<>
Function* newFunctionFactory<IntFunVoidFactory>()
{
  return new Function("intFunVoid", TypedReturnValue(CTYPE_INT),{});
}

#endif /* TEST_INTFUNVOID_H */

