#include <VoidFunStructWithEmbeddedStructFactory.h>

#include <StructType.h>

Function VoidFunStructWithEmbeddedStructFactory::functionFactory()
{
  bool isEmbeddedStruct = true;
  StructType* top = new StructType("top", !isEmbeddedStruct); //NOT EMBEDDED
  StructType* beingDefined = new StructType("embeddedStruct", isEmbeddedStruct);
  beingDefined->addStructField(new ComposableField(CTYPE_INT, "a"));
  top->addStructField(new ComposableField(beingDefined, "b"));
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({new Parameter(top, "t")}));
  return f;
}

Function* VoidFunStructWithEmbeddedStructFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string VoidFunStructWithEmbeddedStructFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithEmbeddedStruct");
}

std::string VoidFunStructWithEmbeddedStructFactory::getFilename()
{
   return "voidFunStructWithEmbeddedStruct.h";
}
