#include <StructRecursiveMemberPtrTypeFactory.h>

#include "StructType.h"

Function StructRecursiveMemberPtrTypeFactory::functionFactory()
{
  bool isRecursiveType = true;
  StructType *recurStruct = new StructType("recurs");
  StructField *valField = new StructField(recurStruct, "val", isRecursiveType);
  valField->setPointer(true);
  recurStruct->addStructField(valField);
  bool isPointer = false;
  Function f(functionGetFunctionName(), VoidReturnValue(), {new Parameter(recurStruct, "rec", isPointer)});
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

