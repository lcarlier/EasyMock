#ifndef TEST_UNSLONGFUNUNSLONG_H
#define TEST_UNSLONGFUNUNSLONG_H

#include <FunctionFactory.h>

class UnsLongFunUnsLongFactory
{
public:
  static std::string getFilename() { return "unsLongFunUnsLong.h"; }
private:
  UnsLongFunUnsLongFactory();
};

template<>
Function functionFactory<UnsLongFunUnsLongFactory>()
{
  Function f("unsLongFunUnsLong", TypedReturnValue(CTYPE_ULONG),{NamedParameter(CTYPE_ULONG, "ul")});
  return f;
}

template<>
Function* newFunctionFactory<UnsLongFunUnsLongFactory>()
{
  return new Function("unsLongFunUnsLong", TypedReturnValue(CTYPE_ULONG),{NamedParameter(CTYPE_ULONG, "ul")});
}

#endif /* TEST_UNSLONGFUNUNSLONG_H */

