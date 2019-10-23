#ifndef TEST_UNSINTFUNUNSINTINT_H
#define TEST_UNSINTFUNUNSINTINT_H

#include <FunctionFactory.h>

class UnsIntFunUnsIntIntFactory
{
public:
  static std::string getFilename() { return "unsIntFunUnsIntInt.h"; }
private:
  UnsIntFunUnsIntIntFactory();
};

template<>
Parameter::Vector getIntFunIntIntPamrameters<UnsIntFunUnsIntIntFactory>()
{
  Parameter::Vector funParam = {
      NamedParameter(CTYPE_UINT, "a"),
      NamedParameter(CTYPE_INT, "b")
  };

  return funParam;
}

template<>
Function functionFactory<UnsIntFunUnsIntIntFactory>()
{
  Function f("unsIntFunUnsIntInt", TypedReturnValue(CTYPE_UINT), getIntFunIntIntPamrameters<UnsIntFunUnsIntIntFactory>());
  return f;
}

template<>
Function* newFunctionFactory<UnsIntFunUnsIntIntFactory>()
{
  return new Function("unsIntFunUnsIntInt", TypedReturnValue(CTYPE_UINT), getIntFunIntIntPamrameters<UnsIntFunUnsIntIntFactory>());
}


#endif /* TEST_UNSINTFUNUNSINTINT_H */

