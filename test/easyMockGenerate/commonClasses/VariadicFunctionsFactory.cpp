#include "VariadicFunctionsFactory.h"

#include <CType.h>
#include <Pointer.h>

ElementToMockList VariadicFunctionsFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  ReturnValue rv((new CType(CTYPE_VOID)));

  Parameter *param = new Parameter(new CType(CTYPE_INT), "a");

  Function* f1 = new Function(functionGetFunctionName(), rv, Parameter::Vector({param}));
  param = nullptr;
  f1->setVariadic(true);
  returnedList.push_back(f1);

  Pointer *constCtype = new Pointer(new CType(CTYPE_CHAR));
  constCtype->getPointedType()->setConst(true);
  param = new Parameter(constCtype, "fmt");
  Function* f2 = new Function("variadicFunctions2", rv, Parameter::Vector({param}));
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
