#include <IntFunStructPtrIntCharPtrFactory.h>

#include <EasyMockStructHelper.h>

#include <CType.h>
#include <Pointer.h>

FunctionDeclaration IntFunStructPtrIntCharPtrFactory::functionFactory()
{
  StructType *s2 = newStructS2Type();
  Parameter *structParam = new Parameter(new Pointer(s2), "s");
  Parameter::Vector p = Parameter::Vector({structParam});
  structParam = nullptr; //We lost the ownership
  p.push_back(new Parameter(new CType(CTYPE_INT), "a"));

  p.push_back(new Parameter(new Pointer(new CType(CTYPE_CHAR)), "c"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_INT), p);
  return f;
}

FunctionDeclaration* IntFunStructPtrIntCharPtrFactory::newFunctionFactory()
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
