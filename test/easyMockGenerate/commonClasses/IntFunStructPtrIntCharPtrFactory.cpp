#include <IntFunStructPtrIntCharPtrFactory.h>

#include <EasyMockStructHelper.h>

#include "CType.h"

Function IntFunStructPtrIntCharPtrFactory::functionFactory()
{
  Parameter::Vector p = structS2Parameter();
  p[0].setPointer(true);
  p.push_back(new Parameter(new CType(CTYPE_INT), "a"));
  bool isPointer = true;
  p.push_back(new Parameter(new CType(CTYPE_CHAR), "c", isPointer));
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_INT), p);
  return f;
}

Function* IntFunStructPtrIntCharPtrFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string IntFunStructPtrIntCharPtrFactory::functionGetFunctionName()
{
  return std::string("intFunStructPtrIntCharPtr");
}

std::string IntFunStructPtrIntCharPtrFactory::getFilename()
{
   return "intFunStructPtrIntCharPtr.h";
}
