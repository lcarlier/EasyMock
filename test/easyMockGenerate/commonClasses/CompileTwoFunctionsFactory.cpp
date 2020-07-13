#include <CompileTwoFunctionsFactory.h>

#include <ReturnValue.h>
#include <CType.h>
#include <StructType.h>

ElementToMockList CompileTwoFunctionsFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  ReturnValue rv((new CType(CTYPE_INT)));

  StructType* curType = new StructType("twoFunStruct", false);
  curType->addField(new ComposableField(new CType(CTYPE_INT), "a"));
  Parameter *param = new Parameter(curType, "s");

  Function* f1 = new Function(functionGetFunctionName(), rv, Parameter::Vector({param->clone()}));
  returnedList.push_back(f1);

  Function* f2 = new Function("f2", rv, Parameter::Vector({param}));
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
