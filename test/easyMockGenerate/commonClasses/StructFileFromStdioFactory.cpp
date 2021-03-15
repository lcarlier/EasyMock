#include "StructFileFromStdioFactory.h"

#include <StructType.h>
#include <ComposableField.h>
#include <EasyMock_CType.h>
#include <Pointer.h>
#include <IncompleteType.h>
#include <TypedefType.h>

FunctionDeclaration StructFileFromStdioFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  TypedefType *tFILE_T = new TypedefType("T_MY_IO_FILE", new StructType("MY_IO_FILE", isEmbeddedInOtherType));
  StructType *FILE_T = dynamic_cast<StructType*>(tFILE_T->getTypee());
  StructType *IO_MARK = new StructType("MY_IO_MARK", isEmbeddedInOtherType);

  ComposableField* cf = new ComposableField(new Pointer(new IncompleteType(*IO_MARK, IncompleteType::Type::STRUCT)), "_next");
  IO_MARK->addField(cf);
  cf = new ComposableField(new Pointer(new IncompleteType(*FILE_T, IncompleteType::Type::STRUCT)), "_sbuf");
  IO_MARK->addField(cf);

  cf = new ComposableField(new Pointer(IO_MARK), "_markers");
  FILE_T->addField(cf);
  cf = new ComposableField(new Pointer(new IncompleteType(*FILE_T, IncompleteType::Type::STRUCT)), "_chain");

  FILE_T->addField(cf);

  Parameter *p = new Parameter(new Pointer(tFILE_T), "file");
  tFILE_T = nullptr; //We lost the ownership
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
