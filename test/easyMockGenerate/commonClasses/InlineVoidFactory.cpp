#include <InlineVoidFactory.h>

#include <FunctionDeclaration.h>
#include <CType.h>

ElementToMockList InlineVoidFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  ReturnValue rv(new CType(CTYPE_VOID));

  FunctionDeclaration* f1 = new FunctionDeclaration(functionGetFunctionName(), rv, Parameter::Vector({}));
  returnedList.push_back(f1);

  ReturnValue rv2(new CType(CTYPE_INT));
  FunctionDeclaration* f2 = new FunctionDeclaration("inline1", rv2, Parameter::Vector());
  f2->setInlined(true);
  returnedList.push_back(f2);

  FunctionDeclaration* f3 = new FunctionDeclaration("inline2", rv2, Parameter::Vector());
  f3->setInlined(true);
  returnedList.push_back(f3);

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