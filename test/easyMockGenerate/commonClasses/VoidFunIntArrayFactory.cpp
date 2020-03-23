#include <VoidFunIntArrayFactory.h>

#include <CType.h>
#include <EasyMockStructHelper.h>

Function VoidFunIntArrayFactory::functionFactory()
{
  //Even though an array is passed as parameter. C/C++ sees it as a pointer
  bool isPointer = true;
  Parameter::Vector p({new Parameter(new CType(CTYPE_INT), "a", isPointer)});
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
