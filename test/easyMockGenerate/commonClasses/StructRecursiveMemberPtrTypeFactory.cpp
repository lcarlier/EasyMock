#include <StructRecursiveMemberPtrTypeFactory.h>

#include <StructType.h>
#include <ComposableField.h>
#include <Pointer.h>

FunctionDeclaration StructRecursiveMemberPtrTypeFactory::functionFactory()
{
  bool isRecursiveType = true;
  bool isEmbeddedInOtherType = false;
  StructType *recurStruct = new StructType("recurs", isEmbeddedInOtherType);
  ComposableField::attributes attrib =
  {
    .arraySize = -1,
    .isRecursiveTypeField = isRecursiveType
  };
  ComposableField *valField = new ComposableField(new Pointer(recurStruct), "val", attrib);
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

