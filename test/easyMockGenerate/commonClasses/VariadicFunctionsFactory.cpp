#include "VariadicFunctionsFactory.h"

#include <EasyMock_CType.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>

ElementToMockList VariadicFunctionsFactory::functionFactoryArray()
{
  ElementToMockList returnedList;

  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter(std::make_shared<CType>(CTYPE_INT), "a"));
    auto f1 = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), VoidReturnValue(), std::move(pv));
    f1->setVariadic(true);
    returnedList.push_back(std::move(f1));
  }

  {
    auto constCtype = std::make_shared<Pointer>(std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_CHAR)));
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{constCtype, "fmt"});
    auto f2 = std::make_shared<FunctionDeclaration>("variadicFunctions2", VoidReturnValue(), std::move(pv));
    f2->setVariadic(true);
    returnedList.push_back(std::move(f2));
  }

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
