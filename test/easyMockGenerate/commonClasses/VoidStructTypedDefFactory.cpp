#include "VoidStructTypedDefFactory.h"

#include <StructType.h>

Function VoidStructTypedDefFactory::functionFactory()
{
  StructType *st1 = new StructType("", "TypedDefAnonynousStruct");
  StructType *st2 = new StructType("foo", "TypedDefStruct");

  Function f(functionGetFunctionName(), VoidReturnValue(), {new Parameter(st1, "s1"), new Parameter(st2, "s2")});
  return f;
}

std::string VoidStructTypedDefFactory::functionGetFunctionName()
{
  return "voidStructTypedDef";
}

std::string VoidStructTypedDefFactory::getFilename()
{
  return "voidStructTypedDef.h";
}

