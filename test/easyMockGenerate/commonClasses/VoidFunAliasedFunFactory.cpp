#include <VoidFunAliasedFunFactory.h>

#include <FunctionDeclaration.h>

ElementToMockList VoidFunAliasedFunFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    auto f = std::make_shared<FunctionDeclaration>("funToBeAliased", TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector {});
    returnedList.push_back(std::move(f));
  }
  {
    auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector {});
    returnedList.push_back(std::move(f));
  }
  return returnedList;
}

ElementToMockContext::MacroDefinitionList VoidFunAliasedFunFactory::getDefinedMacroList()
{
  ElementToMockContext::MacroDefinitionList macroDefinitionList;

  macroDefinitionList.try_emplace("funToBeAliased", "funToBeAliased", "voidFunAliasedFun");

  return macroDefinitionList;
}

std::string VoidFunAliasedFunFactory::functionGetFunctionName()
{
  return std::string("voidFunAliasedFun");
}

std::string VoidFunAliasedFunFactory::getFilename()
{
  return "voidFunAliasedFun.h";
}
