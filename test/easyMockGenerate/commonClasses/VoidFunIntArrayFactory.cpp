#include <VoidFunIntArrayFactory.h>

#include <EasyMock_CType.h>
#include <EasyMockStructHelper.h>
#include <Pointer.h>

FunctionDeclaration VoidFunIntArrayFactory::functionFactory()
{
  //Even though an array is passed as parameter. C/C++ sees it as a pointer
  Parameter::Vector p({new Parameter(new Pointer(new CType(CTYPE_INT)), "array")});
  //Parameter is int array[10] so the string to declare the type of the array is 'int'
  p[0].setDeclareString("int");
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), p);
  return f;
}

FunctionDeclaration* VoidFunIntArrayFactory::newFunctionFactory()
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
