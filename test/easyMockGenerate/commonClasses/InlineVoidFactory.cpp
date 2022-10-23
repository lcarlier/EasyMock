#include <InlineVoidFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>

ElementToMockList InlineVoidFactory::functionFactoryArray()
{
  ElementToMockList returnedList;

  {
    auto f1 = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), VoidReturnValue(), Parameter::Vector {});
    returnedList.push_back(std::move(f1));
  }

  {
    auto f2 = std::make_shared<FunctionDeclaration>("inline1", TypedReturnValue(CTYPE_INT, false), Parameter::Vector {});
    f2->setInlined(true);
    f2->setDoesThisDeclarationHasABody(true);
    returnedList.push_back(std::move(f2));
  }

  {
    auto f3 = std::make_shared<FunctionDeclaration>("inline2", TypedReturnValue(CTYPE_INT, false), Parameter::Vector {});
    f3->setInlined(true);
    f3->setDoesThisDeclarationHasABody(true);
    returnedList.push_back(std::move(f3));
  }

  return returnedList;
}

std::string InlineVoidFactory::functionGetFunctionName()
{
  return std::string("inlineVoid");
}

std::string InlineVoidFactory::getFilename()
{
   return "inlineVoid.h";
}
