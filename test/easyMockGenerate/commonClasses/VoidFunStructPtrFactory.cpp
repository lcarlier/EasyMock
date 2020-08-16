#include <VoidFunStructPtrFactory.h>

#include <EasyMockStructHelper.h>

#include <Pointer.h>

FunctionDeclaration VoidFunStructPtrFactory::functionFactory()
{
  StructType *s2 = newStructS2Type();
  Parameter *p = new Parameter(new Pointer(s2), "s");
  s2 = nullptr; //We lost the ownership
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({p}));
  p = nullptr; //We lost the ownership

  return f;
}

FunctionDeclaration* VoidFunStructPtrFactory::newFunctionFactory()
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
