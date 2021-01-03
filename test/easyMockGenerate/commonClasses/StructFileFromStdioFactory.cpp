#include "StructFileFromStdioFactory.h"

#include <StructType.h>
#include <ComposableField.h>
#include <EasyMock_CType.h>
#include <Pointer.h>
#include <IncompleteType.h>

FunctionDeclaration StructFileFromStdioFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  StructType *FILE_T = new StructType("MY_IO_FILE", "T_MY_IO_FILE", isEmbeddedInOtherType);
  StructType *IO_MARK = new StructType("MY_IO_MARK", isEmbeddedInOtherType);

  ComposableField* cf = new ComposableField(new Pointer(new IncompleteType(*IO_MARK)), "_next");
  IO_MARK->addField(cf);
  cf = new ComposableField(new Pointer(new IncompleteType(*FILE_T)), "_sbuf");
  //When the _sbuf field is declared, it is not yet typed def
  cf->setDeclareString("struct MY_IO_FILE*");
  IO_MARK->addField(cf);

  cf = new ComposableField(new Pointer(IO_MARK), "_markers");
  FILE_T->addField(cf);
  cf = new ComposableField(new Pointer(new IncompleteType(*FILE_T)), "_chain");
  //When the _chain field is declared, it is not yet typed def
  cf->setDeclareString("struct MY_IO_FILE*");
  FILE_T->addField(cf);

  Parameter *p = new Parameter(new Pointer(FILE_T), "file");
  FILE_T = nullptr; //We lost the ownership
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({p}));
  p = nullptr; //We lost the ownership

  return f;
}

FunctionDeclaration* StructFileFromStdioFactory::newFunctionFactory()
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
