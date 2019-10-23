#ifndef TEST_INTFUNINTINT_H
#define TEST_INTFUNINTINT_H

#include <FunctionFactory.h>

class IntFunIntIntFactory
{
public:
  static std::string getFilename() { return "intFunIntInt.h"; }
private:
  IntFunIntIntFactory();
};

template<>
Parameter::Vector getIntFunIntIntPamrameters<IntFunIntIntFactory>()
{
  Parameter::Vector funParam = {
      NamedParameter(CTYPE_INT, "a"),
      NamedParameter(CTYPE_INT, "b")
  };

  return funParam;
}

template<>
Function functionFactory<IntFunIntIntFactory>()
{
  Function f("intFunIntInt", TypedReturnValue(CTYPE_INT), getIntFunIntIntPamrameters<IntFunIntIntFactory>());
  return f;
}

template<>
Function* newFunctionFactory<IntFunIntIntFactory>()
{
  return new Function("intFunIntInt", TypedReturnValue(CTYPE_INT), getIntFunIntIntPamrameters<IntFunIntIntFactory>());
}

#endif /* TEST_INTFUNINTINT_H */

