#include <InlineVoidFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>

ElementToMockList InlineVoidFactory::functionFactoryArray()
{
  ElementToMockList returnedList;

  {
    FunctionDeclaration f1(functionGetFunctionName(), VoidReturnValue(), {});
    returnedList.push_back(std::move(f1));
  }

  {
    FunctionDeclaration f2("inline1", TypedReturnValue(CTYPE_INT, false), {});
    f2.setInlined(true);
    f2.setDoesThisDeclarationHasABody(true);
    returnedList.push_back(std::move(f2));
  }

  {
    FunctionDeclaration f3("inline2", TypedReturnValue(CTYPE_INT, false), {});
    f3.setInlined(true);
    f3.setDoesThisDeclarationHasABody(true);
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
