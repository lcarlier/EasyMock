#include "StructFileFromStdioFactory.h"

#include <StructType.h>
#include <ComposableField.h>
#include <CType.h>
#include <Pointer.h>

Function StructFileFromStdioFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  StructType *FILE_T = new StructType("MY_IO_FILE", "T_MY_IO_FILE", isEmbeddedInOtherType);
  StructType *IO_MARK = new StructType("MY_IO_MARK", isEmbeddedInOtherType);

  ComposableField::attributes fieldAttr =
  {
    .isArray = false,
    .arraySize = 0,
    .isRecursiveTypeField = true
  };

  ComposableField* cf = new ComposableField(new Pointer(IO_MARK), "_next", fieldAttr);
  IO_MARK->addStructField(cf);
  cf = new ComposableField(new Pointer(FILE_T), "_sbuf", fieldAttr);
  //When the _sbuf field is declared, it is not yet typed def
  cf->setDeclareString("struct MY_IO_FILE*");
  IO_MARK->addStructField(cf);

  cf = new ComposableField(new Pointer(IO_MARK), "_markers");
  FILE_T->addStructField(cf);
  cf = new ComposableField(new Pointer(FILE_T), "_chain", fieldAttr);
  //When the _chain field is declared, it is not yet typed def
  cf->setDeclareString("struct MY_IO_FILE*");
  FILE_T->addStructField(cf);

  Parameter *p = new Parameter(new Pointer(FILE_T), "file");
  FILE_T = nullptr; //We lost the ownership
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({p}));
  p = nullptr; //We lost the ownership

  return f;
}

Function* StructFileFromStdioFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string StructFileFromStdioFactory::functionGetFunctionName()
{
  return std::string("structFileFromStdio");
}

std::string StructFileFromStdioFactory::getFilename()
{
   return "structFileFromStdio.h";
}
