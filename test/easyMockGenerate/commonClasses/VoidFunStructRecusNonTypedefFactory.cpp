#include "VoidFunStructRecusNonTypedefFactory.h"

#include <StructType.h>
#include <ComposableField.h>
#include <EasyMock_CType.h>
#include <Pointer.h>
#include <IncompleteType.h>
#include <TypedefType.h>

FunctionDeclaration VoidFunStructRecusNonTypedefFactory::functionFactory()
{
  TypedefType *tt_struct = new TypedefType("t_s1", new StructType("s_s1", false));
  StructType *t_struct = dynamic_cast<StructType*>(tt_struct->getTypee());
  ComposableField* cf = new ComposableField(new Pointer(new IncompleteType(*t_struct, IncompleteType::Type::STRUCT)), "recur");
  t_struct->addField(cf);

  Parameter *p = new Parameter(new Pointer(tt_struct), "s");
  t_struct = nullptr; //We lost the ownership
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({p}));
  p = nullptr; //We lost the ownership

  return f;
}

FunctionDeclaration* VoidFunStructRecusNonTypedefFactory::newFunctionFactory()
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
