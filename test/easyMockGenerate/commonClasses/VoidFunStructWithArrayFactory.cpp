#include <VoidFunStructWithArrayFactory.h>

#include <EasyMockStructHelper.h>
#include <CType.h>
#include <voidFunStructWithArray.h>

Function VoidFunStructWithArrayFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  StructType *st = new StructType("structWithArray", isEmbeddedInOtherType);
  ComposableField::attributes composableFieldAttrib(
  {
    .arraySize = 10,
    .isRecursiveTypeField = false
  });
  st->addField(new ComposableField(new CType(CTYPE_INT), "a", composableFieldAttrib));
  st->addField(new ComposableField(CTYPE_FLOAT, "f"));

  composableFieldAttrib.arraySize = 0;
  st->addField(new ComposableField(new CType(CTYPE_INT), "b", composableFieldAttrib));
  Parameter::Vector p({new Parameter(st, "param")});
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), p);
  return f;
}

Function* VoidFunStructWithArrayFactory::newFunctionFactory()
{
  return functionFactory().clone();
}

std::string VoidFunStructWithArrayFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithArray");
}

std::string VoidFunStructWithArrayFactory::getFilename()
{
   return "voidFunStructWithArray.h";
}
