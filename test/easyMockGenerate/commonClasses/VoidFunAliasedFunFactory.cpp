#include <VoidFunAliasedFunFactory.h>

#include <FunctionDeclaration.h>

ElementToMockList VoidFunAliasedFunFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    FunctionDeclaration f{"funToBeAliased", TypedReturnValue(CTYPE_VOID),
                                                     {}};
    returnedList.push_back(std::move(f));
  }
  {
    FunctionDeclaration f{functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                                                     {}};
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
