#include <VoidFunVoidFactory.h>

std::string VoidFunVoidFactory::getFilename()
{
   return "voidFunVoid.h";
}

FunctionDeclaration VoidFunVoidFactory::functionFactory()
{
  FunctionDeclaration f(functionGetFunctionName(), VoidReturnValue(),{});
  return f;
}

FunctionDeclaration* VoidFunVoidFactory::newFunctionFactory()
{
  return functionFactory().clone();
}

std::string VoidFunVoidFactory::functionGetFunctionName()
{
  return std::string("voidFunVoid");
}

void VoidFunVoidFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
}
