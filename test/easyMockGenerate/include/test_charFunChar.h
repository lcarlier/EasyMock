#ifndef TEST_CHARFUNCHAR_H
#define TEST_CHARFUNCHAR_H

#include <FunctionFactory.h>

class CharFunCharFactory
{
public:
  static std::string getFilename() { return "charFunChar.h"; }
private:
  CharFunCharFactory();
};

template<>
Function functionFactory<CharFunCharFactory>()
{
  Function f("charFunChar", TypedReturnValue(CTYPE_CHAR),{NamedParameter(CTYPE_CHAR, "c")});
  return f;
}

template<>
Function* newFunctionFactory<CharFunCharFactory>()
{
  return new Function("charFunChar", TypedReturnValue(CTYPE_CHAR),{NamedParameter(CTYPE_CHAR, "c")});
}

#endif /* TEST_CHARFUNVOID_H */

