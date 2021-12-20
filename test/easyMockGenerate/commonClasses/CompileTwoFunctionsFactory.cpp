#include <CompileTwoFunctionsFactory.h>

#include <ReturnValue.h>
#include <EasyMock_CType.h>
#include <StructType.h>
#include <ComposableField.h>

ElementToMockList CompileTwoFunctionsFactory::functionFactoryArray()
{
  auto getCommonParam = []()
  {
    auto curType = std::make_shared<StructType>("twoFunStruct", false);
    curType->addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "a"));

    Parameter::Vector pv{};
    pv.emplace_back(Parameter{curType, "s"});
    return pv;
  };

  auto getRv = []()
  {
    return ReturnValue{std::make_shared<CType>(CTYPE_INT)};
  };
  ElementToMockList returnedList;

  FunctionDeclaration f1(functionGetFunctionName(), getRv(), getCommonParam());
  returnedList.push_back(std::move(f1));

  FunctionDeclaration f2("f2", getRv(), getCommonParam());
  returnedList.push_back(std::move(f2));

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
