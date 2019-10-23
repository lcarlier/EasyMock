#ifndef TEST_UNSCHARFUNUNSCHAR_H
#define TEST_UNSCHARFUNUNSCHAR_H

#include <FunctionFactory.h>

class UnsCharFunUnsCharFactory
{
public:
  static std::string getFilename() { return "unsCharFunUnsChar.h"; }
private:
  UnsCharFunUnsCharFactory();
};

template<>
Function functionFactory<UnsCharFunUnsCharFactory>()
{
  Function f("unsCharFunUnsChar", TypedReturnValue(CTYPE_UCHAR),{NamedParameter(CTYPE_UCHAR, "uc")});
  return f;
}

template<>
Function* newFunctionFactory<UnsCharFunUnsCharFactory>()
{
  return new Function("unsCharFunUnsChar", TypedReturnValue(CTYPE_UCHAR),{NamedParameter(CTYPE_UCHAR, "uc")});
}

#endif

