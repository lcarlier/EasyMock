#include <StructRecursiveMemberPtrTypeFactory.h>

#include "StructType.h"
#include "ComposableField.h"

Function StructRecursiveMemberPtrTypeFactory::functionFactory()
{
  bool isRecursiveType = true;
  bool isEmbeddedInOtherType = false;
  StructType *recurStruct = new StructType("recurs", isEmbeddedInOtherType);
  ComposableField::attributes attrib = {.isPointer = false, .isArray = false, .arraySize = 0, .isRecursiveTypeField = isRecursiveType};
  ComposableField *valField = new ComposableField(recurStruct, "val", attrib);
  valField->setPointer(true);
  recurStruct->addStructField(valField);
  bool isPointer = false;
  Function f(functionGetFunctionName(), VoidReturnValue(), Parameter::Vector({new Parameter(recurStruct, "rec", isPointer)}));
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

