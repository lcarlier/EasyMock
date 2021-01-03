#include "VariadicFunctionsFactory.h"

#include <EasyMock_CType.h>
#include <Pointer.h>

ElementToMockList VariadicFunctionsFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  ReturnValue rv((new CType(CTYPE_VOID)));

  Parameter *param = new Parameter(new CType(CTYPE_INT), "a");

  FunctionDeclaration* f1 = new FunctionDeclaration(functionGetFunctionName(), rv, Parameter::Vector({param}));
  param = nullptr;
  f1->setVariadic(true);
  returnedList.push_back(f1);

  Pointer *constCtype = new Pointer(new CType(CTYPE_CHAR));
  constCtype->getPointedType()->setConst(true);
  param = new Parameter(constCtype, "fmt");
  FunctionDeclaration* f2 = new FunctionDeclaration("variadicFunctions2", rv, Parameter::Vector({param}));
  param = nullptr;
  f2->setVariadic(true);
  returnedList.push_back(f2);

  return returnedList;
}

std::string VariadicFunctionsFactory::functionGetFunctionName()
{
  return std::string("variadicFunctions");
}

std::string VariadicFunctionsFactory::getFilename()
{
   return "variadicFunctions.h";
}
