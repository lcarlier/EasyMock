#include <VoidFunStructPtrFactory.h>

#include <EasyMockStructHelper.h>

#include <Pointer.h>

Function VoidFunStructPtrFactory::functionFactory()
{
  StructType *s2 = newStructS2Type();
  Parameter *p = new Parameter(new Pointer(s2), "s");
  s2 = nullptr; //We lost the ownership
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({p}));
  p = nullptr; //We lost the ownership

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
