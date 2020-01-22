#include <VoidFunStructPtrFactory.h>

#include <EasyMockStructHelper.h>

Function VoidFunStructPtrFactory::functionFactory()
{
  Parameter::Vector p = structS2Parameter();
  p[0].setPointer(true);
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), p);
  return f;
}

Function* VoidFunStructPtrFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string VoidFunStructPtrFactory::functionGetFunctionName()
{
  return std::string("voidFunStructPtr");
}

std::string VoidFunStructPtrFactory::getFilename()
{
   return "voidFunStructPtr.h";
}
