#include <VoidFunVoidFactory.h>

std::string VoidFunVoidFactory::getFilename()
{
   return "voidFunVoid.h";
}

std::shared_ptr<FunctionDeclaration> VoidFunVoidFactory::functionFactory()
{
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), VoidReturnValue(), Parameter::Vector {});
  return f;
}

std::string VoidFunVoidFactory::functionGetFunctionName()
{
  return std::string("voidFunVoid");
}

void VoidFunVoidFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
}
