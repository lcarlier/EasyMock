#include "VoidFunStructRecusNonTypedefFactory.h"

#include <StructType.h>
#include <ComposableField.h>
#include <EasyMock_CType.h>
#include <Pointer.h>
#include <IncompleteType.h>

FunctionDeclaration VoidFunStructRecusNonTypedefFactory::functionFactory()
{
  StructType *t_struct = new StructType("s_s1", "t_s1", false);
  ComposableField* cf = new ComposableField(new Pointer(new IncompleteType(*t_struct, IncompleteType::Type::STRUCT)), "recur");
  //When the recursive (incomplete) field is declared, it is not yet typed def
  cf->setDeclareString("struct s_s1*");
  t_struct->addField(cf);

  Parameter *p = new Parameter(new Pointer(t_struct), "s");
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
