#include <VoidFunEmbeddedCommentsFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>

ElementToMockList VoidFunEmbeddedCommentsFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector {});
    returnedList.push_back(std::move(f));
  }
  {
    auto f = std::make_shared<FunctionDeclaration>("voidFunEmbeddedComments2", TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector {});
    returnedList.push_back(std::move(f));
  }
  {
    Parameter p{std::make_shared<CType>(CTYPE_INT), "a"};
    p.setDeclareString("myInt");
    Parameter::Vector pv{};
    pv.emplace_back(std::move(p));
    auto f = std::make_shared<FunctionDeclaration>("voidFunEmbeddedComments3", VoidReturnValue(), std::move(pv));
    returnedList.push_back(std::move(f));
  }
  {
    Parameter p{std::make_shared<CType>(CTYPE_INT), "a"};
    p.setDeclareString("myInt");
    Parameter::Vector pv{};
    pv.emplace_back(std::move(p));
    auto f = std::make_shared<FunctionDeclaration>("voidFunEmbeddedComments4", VoidReturnValue(), std::move(pv));
    returnedList.push_back(std::move(f));
  }
  {
    auto f = std::make_shared<FunctionDeclaration>("voidFunEmbeddedOneLineComments", VoidReturnValue(), Parameter::Vector {});
    returnedList.push_back(std::move(f));
  }
  {
    Parameter p{std::make_shared<CType>(CTYPE_INT), "a"};
    p.setDeclareString("myInt");
    Parameter::Vector pv{};
    pv.emplace_back(std::move(p));
    auto f = std::make_shared<FunctionDeclaration>("voidFunEmbeddedOneLineComments2", VoidReturnValue(), std::move(pv));
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
