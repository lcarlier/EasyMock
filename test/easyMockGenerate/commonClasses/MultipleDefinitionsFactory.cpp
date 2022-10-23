#include "MultipleDefinitionsFactory.h"

#include <EasyMock_CType.h>

ElementToMockList MultipleDefinitionsFactory::functionFactoryArray()
{
  auto getCommonFunctionDeclaration = [](std::string functionName)
  {
    ReturnValue rv(std::make_shared<CType>(CTYPE_VOID));

    Parameter::Vector pv{};
    pv.emplace_back(Parameter(std::make_shared<CType>(CTYPE_INT), "a"));
    auto f1 = std::make_shared<FunctionDeclaration>(functionName, std::move(rv), std::move(pv));
    return f1;
  };
  ElementToMockList returnedList;

  returnedList.push_back(getCommonFunctionDeclaration(functionGetFunctionName()));
  returnedList.push_back(getCommonFunctionDeclaration(functionGetFunctionName()));

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
