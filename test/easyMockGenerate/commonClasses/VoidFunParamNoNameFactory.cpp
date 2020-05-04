#include "VoidFunParamNoNameFactory.h"

#include <Parameter.h>
#include <CType.h>

Function VoidFunParamNoNameFactory::functionFactory()
{
  Parameter* p1 = new Parameter(new CType(CTYPE_INT), "");
  Parameter* p2 = new Parameter(new CType(CTYPE_FLOAT), "");
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({p1, p2}));
  p1 = nullptr; //We lost the ownership
  p2 = nullptr; //We lost the ownership

  return f;
}

Function* VoidFunParamNoNameFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string VoidFunParamNoNameFactory::functionGetFunctionName()
{
  return std::string("voidFunParamNoName");
}

std::string VoidFunParamNoNameFactory::getFilename()
{
   return "voidFunParamNoName.h";
}
