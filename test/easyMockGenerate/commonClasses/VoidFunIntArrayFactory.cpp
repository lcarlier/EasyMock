#include <VoidFunIntArrayFactory.h>

#include <CType.h>
#include <EasyMockStructHelper.h>
#include <Pointer.h>

Function VoidFunIntArrayFactory::functionFactory()
{
  //Even though an array is passed as parameter. C/C++ sees it as a pointer
  Parameter::Vector p({new Parameter(new Pointer(new CType(CTYPE_INT)), "a")});
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), p);
  return f;
}

Function* VoidFunIntArrayFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string VoidFunIntArrayFactory::functionGetFunctionName()
{
  return std::string("voidFunIntArray");
}

std::string VoidFunIntArrayFactory::getFilename()
{
   return "voidFunIntArray.h";
}
