#include <VoidFunDeclAndDefFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>

ElementToMockList VoidFunDeclAndDefFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    FunctionDeclaration *f = new FunctionDeclaration{functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                          Parameter::Vector({new Parameter{new CType{CTYPE_CHAR}, ""},new Parameter{new CType{CTYPE_CHAR}, ""}})};
    FunctionAttribute fa{"unused"};
    f->addAttribute(std::move(fa));
    f->setDoesThisDeclarationHasABody(false);
    f->setIsStatic(true);
    returnedList.push_back(f);
  }
  {
    FunctionDeclaration *f = new FunctionDeclaration{functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({new Parameter{new CType{CTYPE_CHAR}, "a"},new Parameter{new CType{CTYPE_CHAR}, "b"}})};
    FunctionAttribute fa{"unused"};
    f->addAttribute(std::move(fa));
    f->setDoesThisDeclarationHasABody(true);
    f->setIsStatic(true);
    returnedList.push_back(f);
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
