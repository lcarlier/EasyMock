#include <VoidFunStructWithTypedefStructFactory.h>

#include <StructType.h>
#include <ComposableField.h>
#include <CType.h>

Function VoidFunStructWithTypedefStructFactory::functionFactory()
{
  StructType *t_subStructVar = new StructType("", "t_subStruct", false);
  t_subStructVar->addStructField(new ComposableField(new CType(CTYPE_INT), "a"));

  StructType *t_structVar = new StructType("", "t_struct", false);
  t_structVar->addStructField(new ComposableField(t_subStructVar, "sub"));
  t_subStructVar = nullptr; //We lost the ownership

  Parameter *p = new Parameter(t_structVar, "s");
  t_structVar = nullptr; //We lost the ownership
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({p}));
  p = nullptr; //We lost the ownership

  return f;
}

Function* VoidFunStructWithTypedefStructFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string VoidFunStructWithTypedefStructFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithTypedefStruct");
}

std::string VoidFunStructWithTypedefStructFactory::getFilename()
{
   return "voidFunStructWithTypedefStruct.h";
}
