#include <InlineVoidFactory.h>

#include <Function.h>
#include <CType.h>

ElementToMockList InlineVoidFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  ReturnValue rv(new CType(CTYPE_VOID));

  Function* f1 = new Function(functionGetFunctionName(), rv, Parameter::Vector({}));
  returnedList.push_back(f1);

  ReturnValue rv2(new CType(CTYPE_INT));
  Function* f2 = new Function("inline1", rv2, Parameter::Vector());
  f2->setInline(true);
  returnedList.push_back(f2);

  Function* f3 = new Function("inline2", rv2, Parameter::Vector());
  f3->setInline(true);
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