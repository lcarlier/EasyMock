#include <StructRecursiveMemberPtrTypeFactory.h>

#include <StructType.h>
#include <ComposableField.h>
#include <Pointer.h>
#include <IncompleteType.h>

FunctionDeclaration StructRecursiveMemberPtrTypeFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  auto recurStruct = std::make_shared<StructType>("recurs", isEmbeddedInOtherType);
  ComposableField valField{std::make_shared<Pointer>(std::make_shared<IncompleteType>(*recurStruct, IncompleteType::Type::STRUCT)), "val"};
  recurStruct->addField(std::move(valField));

  Parameter::Vector pv;
  pv.emplace_back(Parameter(std::move(recurStruct), "rec"));
  FunctionDeclaration f(functionGetFunctionName(), VoidReturnValue(), std::move(pv));
  return f;
}

std::string StructRecursiveMemberPtrTypeFactory::functionGetFunctionName()
{
  return "structRecursivePtrType";
}

std::string StructRecursiveMemberPtrTypeFactory::getFilename()
{
  return "structRecursivePtrType.h";
}
