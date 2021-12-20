#include "VoidFunParamNoNameFactory.h"

#include <Parameter.h>
#include <EasyMock_CType.h>

FunctionDeclaration VoidFunParamNoNameFactory::functionFactory()
{
  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::make_shared<CType>(CTYPE_INT), ""));
  pv.emplace_back(Parameter(std::make_shared<CType>(CTYPE_FLOAT), ""));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));

  return f;
}

std::string VoidFunParamNoNameFactory::functionGetFunctionName()
{
  return std::string("voidFunParamNoName");
}

std::string VoidFunParamNoNameFactory::getFilename()
{
   return "voidFunParamNoName.h";
}
