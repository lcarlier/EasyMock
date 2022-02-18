#include <CppVoidFunVoidFactory.h>

#include <FunctionFactory.h>

FunctionDeclaration CppVoidFunVoidFactory::functionFactory()
{
  return FunctionDeclaration { functionGetFunctionName(), VoidReturnValue(), Parameter::Vector{}};
}

ElementToMockList CppVoidFunVoidFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  returnedList.push_back(functionFactory());
  return returnedList;
}

std::string CppVoidFunVoidFactory::functionGetFunctionName()
{
  return std::string("cppVoidFunVoid");
}

std::string CppVoidFunVoidFactory::getFilename()
{
  return "cppVoidFunVoid.h";
}

void CppVoidFunVoidFactory::setupTestCase(EasyMockTestCase::TestCase)
{
}
