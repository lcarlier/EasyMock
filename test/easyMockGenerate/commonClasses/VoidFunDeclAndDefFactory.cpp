#include <VoidFunDeclAndDefFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>

ElementToMockList VoidFunDeclAndDefFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_CHAR), ""});
    pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_CHAR), ""});
    FunctionDeclaration f{functionGetFunctionName(), VoidReturnValue(), std::move(pv)};
    FunctionAttribute fa{"unused"};
    f.addAttribute(std::move(fa));
    f.setDoesThisDeclarationHasABody(false);
    f.setIsStatic(true);
    returnedList.push_back(std::move(f));
  }
  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_CHAR), "a"});
    pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_CHAR), "b"});
    FunctionDeclaration f{functionGetFunctionName(), VoidReturnValue(), std::move(pv)};
    FunctionAttribute fa{"unused"};
    f.addAttribute(std::move(fa));
    f.setDoesThisDeclarationHasABody(true);
    f.setIsStatic(true);
    returnedList.push_back(std::move(f));
  }
  return returnedList;
}

std::string VoidFunDeclAndDefFactory::functionGetFunctionName()
{
  return std::string("voidFunDeclAndDef");
}

std::string VoidFunDeclAndDefFactory::getFilename()
{
  return "voidFunDeclAndDef.h";
}
