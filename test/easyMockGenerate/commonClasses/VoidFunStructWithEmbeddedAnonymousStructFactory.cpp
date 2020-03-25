#include <VoidFunStructWithEmbeddedAnonymousStructFactory.h>

#include <StructType.h>

Function VoidFunStructWithEmbeddedAnonymousStructFactory::functionFactory()
{
  const unsigned int NB_ANONYMOUS_TYPE_IN_THIS_UT = 1;
  /*
   * with -fno-access-control we are able to set this static class variable to
   * decrement the number of anonymous composable type by the number of anonymous
   * type the UT contains.
   * Thanks to that, the following code will generate the same anonymous ID
   */
  ComposableType::m_number_of_anonymous_composable_type -= NB_ANONYMOUS_TYPE_IN_THIS_UT;
  bool isEmbeddedStruct = true;
  StructType* top = new StructType("topEmbeddedAnonymous", !isEmbeddedStruct); //NOT EMBEDDED
  StructType* beingDefined = new StructType("", isEmbeddedStruct);
  beingDefined->addStructField(new ComposableField(CTYPE_INT, "a"));
  top->addStructField(new ComposableField(beingDefined, "af"));
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({new Parameter(top, "s")}));

  return f;
}

Function* VoidFunStructWithEmbeddedAnonymousStructFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string VoidFunStructWithEmbeddedAnonymousStructFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithEmbeddedAnonymousStruct");
}

std::string VoidFunStructWithEmbeddedAnonymousStructFactory::getFilename()
{
   return "voidFunStructWithEmbeddedAnonymousStruct.h";
}
