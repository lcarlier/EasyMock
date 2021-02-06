#include <StructRecursiveMemberPtrTypeFactory.h>

#include <StructType.h>
#include <ComposableField.h>
#include <Pointer.h>
#include <IncompleteType.h>

FunctionDeclaration StructRecursiveMemberPtrTypeFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  StructType *recurStruct = new StructType("recurs", isEmbeddedInOtherType);
  ComposableField *valField = new ComposableField(new Pointer(new IncompleteType(*recurStruct, IncompleteType::Type::STRUCT)), "val");
  recurStruct->addField(valField);

  FunctionDeclaration f(functionGetFunctionName(), VoidReturnValue(), Parameter::Vector({new Parameter(recurStruct, "rec")}));
  recurStruct = nullptr; //Invalidate because we lost the ownership
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

