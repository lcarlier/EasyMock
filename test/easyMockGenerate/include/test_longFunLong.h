#ifndef TEST_LONGFUNLONG_H
#define TEST_LONGFUNLONG_H

#include <FunctionFactory.h>

class LongFunLongFactory
{
public:
  static std::string getFilename() { return "longFunLong.h"; }
private:
  LongFunLongFactory();
};

template<>
Function functionFactory<LongFunLongFactory>()
{
  Function f("longFunLong", TypedReturnValue(CTYPE_LONG),{NamedParameter(CTYPE_LONG, "l")});
  return f;
}

template<>
Function* newFunctionFactory<LongFunLongFactory>()
{
  return new Function("longFunLong", TypedReturnValue(CTYPE_LONG),{NamedParameter(CTYPE_LONG, "l")});
}

#endif /* TEST_LONGFUNLONG_H */

