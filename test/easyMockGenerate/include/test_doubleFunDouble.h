#ifndef TEST_DOUBLEFUNDOUBLE_H
#define TEST_DOUBLEFUNDOUBLE_H

#include <FunctionFactory.h>

class DoubleFunDoubleFactory
{
public:
  static std::string getFilename() { return "doubleFunDouble.h"; }
private:
  DoubleFunDoubleFactory();
};

template<>
Function functionFactory<DoubleFunDoubleFactory>()
{
  Function f("doubleFunDouble", TypedReturnValue(CTYPE_DOUBLE),{NamedParameter(CTYPE_DOUBLE, "d")});
  return f;
}

template<>
Function* newFunctionFactory<DoubleFunDoubleFactory>()
{
  return new Function("doubleFunDouble", TypedReturnValue(CTYPE_DOUBLE),{NamedParameter(CTYPE_DOUBLE, "d")});
}

#endif /* TEST_DOUBLEFUNDOUBLE_H */

