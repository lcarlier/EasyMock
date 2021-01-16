#include <CompileTwoFunctionsFactory.h>

#include <ReturnValue.h>
#include <EasyMock_CType.h>
#include <StructType.h>
#include <ComposableField.h>

ElementToMockList CompileTwoFunctionsFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  ReturnValue rv((new CType(CTYPE_INT)));

  StructType* curType = new StructType("twoFunStruct", false);
  curType->addField(new ComposableField(new CType(CTYPE_INT), "a"));
  Parameter *param = new Parameter(curType, "s");

  FunctionDeclaration* f1 = new FunctionDeclaration(functionGetFunctionName(), rv, Parameter::Vector({param->clone()}));
  returnedList.push_back(f1);

  FunctionDeclaration* f2 = new FunctionDeclaration("f2", rv, Parameter::Vector({param}));
  returnedList.push_back(f2);
  param = nullptr;

  return returnedList;
}

std::string CompileTwoFunctionsFactory::functionGetFunctionName()
{
  return std::string("compileTwoFunctions");
}

std::string CompileTwoFunctionsFactory::getFilename()
{
   return "compileTwoFunctions.h";
}
