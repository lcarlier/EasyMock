#ifndef TEST_LONGLONGFUNLONGLONG_H
#define TEST_LONGLONGFUNLONGLONG_H

#include <FunctionFactory.h>

class LongLongFunLongLongFactory
{
public:
  static std::string getFilename() { return "longLongFunLongLong.h"; }
private:
  LongLongFunLongLongFactory();
};

template<>
Function functionFactory<LongLongFunLongLongFactory>()
{
  Function f("longLongFunLongLong", TypedReturnValue(CTYPE_LONG_LONG),{NamedParameter(CTYPE_LONG_LONG, "ll")});
  return f;
}

template<>
Function* newFunctionFactory<LongLongFunLongLongFactory>()
{
  return new Function("longLongFunLongLong", TypedReturnValue(CTYPE_LONG_LONG),{NamedParameter(CTYPE_LONG_LONG, "ll")});
}

#endif /* TEST_LONGLONGFUNLONGLONG_H */

