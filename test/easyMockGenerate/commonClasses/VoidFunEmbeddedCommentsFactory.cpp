#include <VoidFunEmbeddedCommentsFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>

ElementToMockList VoidFunEmbeddedCommentsFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    FunctionDeclaration f{functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                                                     {}};
    returnedList.push_back(std::move(f));
  }
  {
    FunctionDeclaration f{"voidFunEmbeddedComments2", TypedReturnValue(CTYPE_VOID),
                                                     {}};
    returnedList.push_back(std::move(f));
  }
  {
    Parameter p{std::make_shared<CType>(CTYPE_INT), "a"};
    p.setDeclareString("myInt");
    Parameter::Vector pv{};
    pv.emplace_back(std::move(p));
    FunctionDeclaration f{"voidFunEmbeddedComments3", VoidReturnValue(), std::move(pv)};
    returnedList.push_back(std::move(f));
  }
  {
    Parameter p{std::make_shared<CType>(CTYPE_INT), "a"};
    p.setDeclareString("myInt");
    Parameter::Vector pv{};
    pv.emplace_back(std::move(p));
    FunctionDeclaration f{"voidFunEmbeddedComments4", VoidReturnValue(), std::move(pv)};
    returnedList.push_back(std::move(f));
  }
  {
    FunctionDeclaration f{"voidFunEmbeddedOneLineComments", VoidReturnValue(), {}};
    returnedList.push_back(std::move(f));
  }
  {
    Parameter p{std::make_shared<CType>(CTYPE_INT), "a"};
    p.setDeclareString("myInt");
    Parameter::Vector pv{};
    pv.emplace_back(std::move(p));
    FunctionDeclaration f{"voidFunEmbeddedOneLineComments2", VoidReturnValue(), std::move(pv)};
    returnedList.push_back(std::move(f));
  }
  return returnedList;
}

std::string VoidFunEmbeddedCommentsFactory::functionGetFunctionName()
{
  return std::string("voidFunEmbeddedComments");
}

std::string VoidFunEmbeddedCommentsFactory::getFilename()
{
  return "voidFunEmbeddedComments.h";
}

ElementToMockContext::MacroDefinitionList VoidFunEmbeddedCommentsFactory::getDefinedMacroList()
{
  ElementToMockContext::MacroDefinitionList ml;
  ml.try_emplace("myInt", "myInt", "int");

  return ml;
}
