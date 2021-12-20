#include "VoidFunStructRecusNonTypedefFactory.h"

#include <StructType.h>
#include <ComposableField.h>
#include <EasyMock_CType.h>
#include <Pointer.h>
#include <IncompleteType.h>
#include <TypedefType.h>

FunctionDeclaration VoidFunStructRecusNonTypedefFactory::functionFactory()
{
  auto tt_struct = std::make_shared<TypedefType>("t_s1", std::make_shared<StructType>("s_s1", false));
  ComposableType *t_struct = tt_struct->getTypee()->asComposableType();
  t_struct->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*t_struct, IncompleteType::Type::STRUCT)), "recur"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::make_shared<Pointer>(std::move(tt_struct)), "s"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));

  return f;
}

std::string VoidFunStructRecusNonTypedefFactory::functionGetFunctionName()
{
  return std::string("voidFunStructRecursNonTypedef");
}

std::string VoidFunStructRecusNonTypedefFactory::getFilename()
{
   return "voidFunStructRecursNonTypedef.h";
}
