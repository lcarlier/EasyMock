#ifndef TEST_FLOATFUNFLOAT_H
#define TEST_FLOATFUNFLOAT_H

#include <FunctionFactory.h>

class FloatFunFloatFactory
{
public:
  static std::string getFilename() { return "floatFunFloat.h"; }
private:
  FloatFunFloatFactory();
};

template<>
Function functionFactory<FloatFunFloatFactory>()
{
  Function f("floatFunFloat", TypedReturnValue(CTYPE_FLOAT),{NamedParameter(CTYPE_FLOAT, "f")});
  return f;
}

template<>
Function* newFunctionFactory<FloatFunFloatFactory>()
{
  return new Function("floatFunFloat", TypedReturnValue(CTYPE_FLOAT),{NamedParameter(CTYPE_FLOAT, "f")});
}

#endif /* TEST_FLOATFUNFLOAT_H */

