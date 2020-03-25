#include <VoidFunUnionWithEmbeddedUnionFactory.h>

#include <UnionType.h>

Function VoidFunUnionWithEmbeddedUnionFactory::functionFactory()
{
  bool isEmbeddedStruct = true;
  UnionType* top = new UnionType("topEmbeddedUnion", !isEmbeddedStruct); //NOT EMBEDDED
  UnionType* beingDefined = new UnionType("embeddedUnion", isEmbeddedStruct);
  beingDefined->addStructField(new ComposableField(CTYPE_INT, "a"));
  beingDefined->addStructField(new ComposableField(CTYPE_FLOAT, "b"));
  top->addStructField(new ComposableField(beingDefined, "eu"));
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({new Parameter(top, "u")}));
  return f;
}

Function* VoidFunUnionWithEmbeddedUnionFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string VoidFunUnionWithEmbeddedUnionFactory::functionGetFunctionName()
{
  return std::string("voidFunUnionWithEmbeddedUnion");
}

std::string VoidFunUnionWithEmbeddedUnionFactory::getFilename()
{
   return "voidFunUnionWithEmbeddedUnion.h";
}
