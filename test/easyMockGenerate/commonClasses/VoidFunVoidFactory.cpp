#include <VoidFunVoidFactory.h>

std::string VoidFunVoidFactory::getFilename()
{
   return "voidFunVoid.h";
}

Function VoidFunVoidFactory::functionFactory()
{
  Function f(functionGetFunctionName(), VoidReturnValue(),{});
  return f;
}

Function* VoidFunVoidFactory::newFunctionFactory()
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
