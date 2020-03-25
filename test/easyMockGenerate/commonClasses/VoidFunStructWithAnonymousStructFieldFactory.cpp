#include "VoidFunStructWithAnonymousStructFieldFactory.h"

#include <StructType.h>

Function VoidFunStructWithAnonymousStructFieldFactory::functionFactory()
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
  StructType* top = new StructType("topAnonymousStructField", !isEmbeddedStruct); //NOT EMBEDDED
  top->addStructField(new ComposableField(CTYPE_INT, "a"));
  StructType* beingDefined = new StructType("", isEmbeddedStruct);
  beingDefined->addStructField(new ComposableField(CTYPE_INT, "s1"));
  beingDefined->addStructField(new ComposableField(CTYPE_FLOAT, "s2"));
  top->addStructField(new ComposableField(beingDefined, ""));
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({new Parameter(top, "t")}));

  return f;
}

Function* VoidFunStructWithAnonymousStructFieldFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string VoidFunStructWithAnonymousStructFieldFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithAnonymousStructField");
}

std::string VoidFunStructWithAnonymousStructFieldFactory::getFilename()
{
   return "voidFunStructWithAnonymousStructField.h";
}
