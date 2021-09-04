#include <VoidFunAliasedFunFactory.h>

#include <FunctionDeclaration.h>

ElementToMockList VoidFunAliasedFunFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    FunctionDeclaration *f = new FunctionDeclaration{"funToBeAliased", TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({})};
    returnedList.push_back(f);
  }
  {
    FunctionDeclaration *f = new FunctionDeclaration{functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({})};
    returnedList.push_back(f);
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
