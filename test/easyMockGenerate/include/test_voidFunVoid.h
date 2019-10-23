#ifndef TEST_VOIDFUNVOID_H
#define TEST_VOIDFUNVOID_H

#include <FunctionFactory.h>

class VoidFunVoidFactory
{
public:
  static std::string getFilename() { return "voidFunVoid.h"; }
private:
  VoidFunVoidFactory();
};

template<>
Function functionFactory<VoidFunVoidFactory>()
{
  Function f("voidFunVoid", VoidReturnValue(),{});
  return f;
}

template<>
Function* newFunctionFactory<VoidFunVoidFactory>()
{
  return new Function("voidFunVoid", VoidReturnValue(),{});
}

#endif /* TEST_VOIDFUNVOID_H */

