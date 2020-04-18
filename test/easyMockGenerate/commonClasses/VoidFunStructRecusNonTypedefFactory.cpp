#include "VoidFunStructRecusNonTypedefFactory.h"

#include <StructType.h>
#include <ComposableField.h>
#include <CType.h>
#include <Pointer.h>

Function VoidFunStructRecusNonTypedefFactory::functionFactory()
{
  StructType *t_struct = new StructType("s_s1", "t_s1", false);
  ComposableField::attributes cmpAttr =
  {
    .isArray = false,
    .arraySize = 0,
    .isRecursiveTypeField = true
  };
  t_struct->addStructField(new ComposableField(new Pointer(t_struct), "recur", cmpAttr));

  Parameter *p = new Parameter(new Pointer(t_struct), "s");
  t_struct = nullptr; //We lost the ownership
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({p}));
  p = nullptr; //We lost the ownership

  return f;
}

Function* VoidFunStructRecusNonTypedefFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string VoidFunStructRecusNonTypedefFactory::functionGetFunctionName()
{
  return std::string("voidFunStructRecursNonTypedef");
}

std::string VoidFunStructRecusNonTypedefFactory::getFilename()
{
   return "voidFunStructRecursNonTypedef.h";
}
