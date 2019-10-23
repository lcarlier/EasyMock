#ifndef TEST_LONGDOUBLEFUNLONGDOUBLE_H
#define TEST_LONGDOUBLEFUNLONGDOUBLE_H

#include <FunctionFactory.h>

class LongDoubleFunLongDoubleFactory
{
public:
  static std::string getFilename() { return "longDoubleFunLongDouble.h"; }
private:
  LongDoubleFunLongDoubleFactory();
};

template<>
Function functionFactory<LongDoubleFunLongDoubleFactory>()
{
  Function f("longDoubleFunLongDouble", TypedReturnValue(CTYPE_LONG_DOUBLE),{NamedParameter(CTYPE_LONG_DOUBLE, "ld")});
  return f;
}

template<>
Function* newFunctionFactory<LongDoubleFunLongDoubleFactory>()
{
  return new Function("longDoubleFunLongDouble", TypedReturnValue(CTYPE_LONG_DOUBLE),{NamedParameter(CTYPE_LONG_DOUBLE, "ld")});
}

#endif /* TEST_LONGDOUBLEFUNLONGDOUBLE_H */

