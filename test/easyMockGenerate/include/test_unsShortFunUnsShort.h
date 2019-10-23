#ifndef TEST_UNSSHORTFUNUNSSHORT_H
#define TEST_UNSSHORTFUNUNSSHORT_H

#include <FunctionFactory.h>

class UnsShortFunUnsShortFactory
{
public:
  static std::string getFilename() { return "unsShortFunUnsShort.h"; }
private:
  UnsShortFunUnsShortFactory();
};

template<>
Function functionFactory<UnsShortFunUnsShortFactory>()
{
  Function f("unsShortFunUnsShort", TypedReturnValue(CTYPE_USHORT),{NamedParameter(CTYPE_USHORT, "s")});
  return f;
}

template<>
Function* newFunctionFactory<UnsShortFunUnsShortFactory>()
{
  return new Function("unsShortFunUnsShort", TypedReturnValue(CTYPE_USHORT),{NamedParameter(CTYPE_USHORT, "s")});
}

#endif /* TEST_UNSSHORTFUNUNSSHORT_H */

