#include <VoidFunStructWithArrayFactory.h>

#include <EasyMockStructHelper.h>
#include <CType.h>
#include <voidFunStructWithArray.h>

Function VoidFunStructWithArrayFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  StructType *st = new StructType("structWithArray", isEmbeddedInOtherType);
  st->addStructField(new ComposableField(new CType(CTYPE_INT), "a", {.isPointer = false, .isArray = true, .arraySize = 10, .isRecursiveTypeField = false}));
  st->addStructField(new ComposableField(CTYPE_FLOAT, "f"));
  st->addStructField(new ComposableField(new CType(CTYPE_INT), "b", {.isPointer = false, .isArray = true, .arraySize = 0, .isRecursiveTypeField = false}));
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
