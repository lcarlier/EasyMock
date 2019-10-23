#ifndef TEST_UNSLONGLONGFUNUNSLONGLONG_H
#define TEST_UNSLONGLONGFUNUNSLONGLONG_H

#include <FunctionFactory.h>

class UnsLongLongFunUnsLongLongFactory
{
public:
  static std::string getFilename() { return "unsLongLongFunUnsLongLong.h"; }
private:
  UnsLongLongFunUnsLongLongFactory();
};

template<>
Function functionFactory<UnsLongLongFunUnsLongLongFactory>()
{
  Function f("unsLongLongFunUnsLongLong", TypedReturnValue(CTYPE_ULONG_LONG),{NamedParameter(CTYPE_ULONG_LONG, "ull")});
  return f;
}

template<>
Function* newFunctionFactory<UnsLongLongFunUnsLongLongFactory>()
{
  return new Function("unsLongLongFunUnsLongLong", TypedReturnValue(CTYPE_ULONG_LONG),{NamedParameter(CTYPE_ULONG_LONG, "ull")});
}

#endif /* TEST_UNSLONGLONGFUNUNSLONGLONG_H */

