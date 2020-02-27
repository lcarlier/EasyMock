#include <StructSubStructRecursiveTypeFactory.h>

#include "StructType.h"
#include <CType.h>

/*
 * struct s2;
 *
 * struct s1 {
 *    struct s1 *s1SubS1;
 *    struct s2 *s1SubS2;
 * }
 *
 * struct s2 {
 *    struct s1 s2SubS1;
 * }
 *
 */

Function StructSubStructRecursiveTypeFactory::functionFactory()
{
  StructType *st1 = new StructType("st1");
  StructType *st2 = new StructType("st2");
  st1->addStructField(new StructField(st2, "st1SubSt2"));
  //st1 is recursive in st2 because it is access via the parameter "st1Val" which is type st2 and has a st1 as field member
  st2->addStructField(new StructField(st1, "st2SubSt1", {.isPointer = true, .isArray = false, .arraySize=0, .isRecursiveTypeField=true}));
  st2->addStructField(new StructField(st2, "st2SubSt2", {.isPointer = true, .isArray = false, .arraySize=0, .isRecursiveTypeField=true}));
  Function f(functionGetFunctionName(), VoidReturnValue(), {new Parameter(st1, "st1Val")});
  return f;
}

std::string StructSubStructRecursiveTypeFactory::functionGetFunctionName()
{
  return "structSubStructRecursiveType";
}

std::string StructSubStructRecursiveTypeFactory::getFilename()
{
  return "structSubStructRecursiveType.h";
}
