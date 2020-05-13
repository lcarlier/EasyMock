#include "VoidOutFactory.h"

#include <ReturnValue.h>
#include <Function.h>
#include <Parameter.h>
#include <CType.h>
#include <Pointer.h>

ElementToMockList VoidOutFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  ReturnValue rv(new CType(CTYPE_VOID));

  Function* f1 = new Function("voidOut", rv, Parameter::Vector({new Parameter(new Pointer(new CType(CTYPE_VOID)), "")}));
  returnedList.push_back(f1);

  Function* f2 = new Function("voidOutFirst", rv, Parameter::Vector({new Parameter(new Pointer(new CType(CTYPE_VOID)), ""), new Parameter(new CType(CTYPE_INT), ""), new Parameter(new Pointer(new CType(CTYPE_VOID)), ""), new Parameter(new CType(CTYPE_FLOAT), "")}));
  returnedList.push_back(f2);

  Function* f3 = new Function("voidOutSecond", rv, Parameter::Vector({new Parameter(new CType(CTYPE_INT), ""), new Parameter(new Pointer(new CType(CTYPE_VOID)), ""), new Parameter(new CType(CTYPE_FLOAT), ""), new Parameter(new Pointer(new CType(CTYPE_VOID)), "")}));
  returnedList.push_back(f3);

  return returnedList;
}

std::string VoidOutFactory::functionGetFunctionName()
{
  return std::string("voidOut");
}

std::string VoidOutFactory::getFilename()
{
   return "voidOut.h";
}
