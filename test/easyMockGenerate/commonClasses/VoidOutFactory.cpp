#include "VoidOutFactory.h"

#include <ReturnValue.h>
#include <Function.h>
#include <Parameter.h>
#include <EasyMock_CType.h>
#include <Pointer.h>

ElementToMockList VoidOutFactory::functionFactoryArray()
{
  ElementToMockList returnedList;

  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), ""));
    auto f1 = std::make_shared<FunctionDeclaration>("voidOut", VoidReturnValue(), std::move(pv));

    returnedList.push_back(std::move(f1));
  }

  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), ""});
    pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_INT), ""});
    pv.emplace_back(Parameter{std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), ""});
    pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_FLOAT), ""});

    auto f2 = std::make_shared<FunctionDeclaration>("voidOutFirst", VoidReturnValue(), std::move(pv));

    returnedList.push_back(std::move(f2));
  }

  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_INT), ""});
    pv.emplace_back(Parameter{std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), ""});
    pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_FLOAT), ""});
    pv.emplace_back(Parameter{std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), ""});

    auto f3 = std::make_shared<FunctionDeclaration>("voidOutSecond", VoidReturnValue(), std::move(pv));
    returnedList.push_back(std::move(f3));
  }

  return returnedList;
}

std::string VoidOutFactory::functionGetFunctionName()
{
  return std::string("voidOut");
}

std::string VoidOutFactory::getFilename()
{
   return "voidOut.h";
}
