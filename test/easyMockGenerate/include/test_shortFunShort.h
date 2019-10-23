#ifndef TEST_SHORTFUNSHORT_H
#define TEST_SHORTFUNSHORT_H

#include <FunctionFactory.h>

class ShortFunShortFactory
{
public:
  static std::string getFilename() { return "shortFunShort.h"; }
private:
  ShortFunShortFactory();
};

template<>
Function functionFactory<ShortFunShortFactory>()
{
  Function f("shortFunShort", TypedReturnValue(CTYPE_SHORT),{NamedParameter(CTYPE_SHORT, "s")});
  return f;
}

template<>
Function* newFunctionFactory<ShortFunShortFactory>()
{
  return new Function("shortFunShort", TypedReturnValue(CTYPE_SHORT),{NamedParameter(CTYPE_SHORT, "s")});
}

#endif /* TEST_CHARFUNVOID_H */

