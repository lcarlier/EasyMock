#include "MultipleDefinitionsFactory.h"

#include <EasyMock_CType.h>

ElementToMockList MultipleDefinitionsFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  ReturnValue rv((new CType(CTYPE_VOID)));

  Parameter *param = new Parameter(new CType(CTYPE_INT), "a");

  FunctionDeclaration* f1 = new FunctionDeclaration(functionGetFunctionName(), rv, Parameter::Vector({param}));
  param = nullptr;
  returnedList.push_back(f1->clone());
  returnedList.push_back(f1);

  return returnedList;
}

std::string MultipleDefinitionsFactory::functionGetFunctionName()
{
  return std::string("multipleDefinitions");
}

std::string MultipleDefinitionsFactory::getFilename()
{
   return "multipleDefinitions.h";
}
