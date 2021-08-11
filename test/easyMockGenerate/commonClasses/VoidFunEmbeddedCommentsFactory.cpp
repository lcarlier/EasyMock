#include <VoidFunEmbeddedCommentsFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>

ElementToMockList VoidFunEmbeddedCommentsFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {

    FunctionDeclaration *f = new FunctionDeclaration{functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({})};
    returnedList.push_back(f);
  }
  {
    FunctionDeclaration *f = new FunctionDeclaration{"voidFunEmbeddedComments2", TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({})};
    returnedList.push_back(f);
  }
  {
    Parameter *p = new Parameter{new CType{CTYPE_INT}, "a"};
    p->setDeclareString("myInt");
    FunctionDeclaration *f = new FunctionDeclaration{"voidFunEmbeddedComments3", TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({p})};
    returnedList.push_back(f);
  }
  {
    Parameter *p = new Parameter{new CType{CTYPE_INT}, "a"};
    p->setDeclareString("myInt");
    FunctionDeclaration *f = new FunctionDeclaration{"voidFunEmbeddedComments4", TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({p})};
    returnedList.push_back(f);
  }
  {
    FunctionDeclaration *f = new FunctionDeclaration{"voidFunEmbeddedOneLineComments", TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({})};
    returnedList.push_back(f);
  }
  {
    Parameter *p = new Parameter{new CType{CTYPE_INT}, "a"};
    p->setDeclareString("myInt");
    FunctionDeclaration *f = new FunctionDeclaration{"voidFunEmbeddedOneLineComments2", TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({p})};
    returnedList.push_back(f);
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
