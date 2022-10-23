#include "VoidFunParamNoNameFactory.h"

#include <Parameter.h>
#include <EasyMock_CType.h>

std::shared_ptr<FunctionDeclaration> VoidFunParamNoNameFactory::functionFactory()
{
  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::make_shared<CType>(CTYPE_INT), ""));
  pv.emplace_back(Parameter(std::make_shared<CType>(CTYPE_FLOAT), ""));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));

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
