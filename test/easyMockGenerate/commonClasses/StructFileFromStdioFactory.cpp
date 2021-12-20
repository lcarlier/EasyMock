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
  auto tFILE_T = std::make_shared<TypedefType>("T_MY_IO_FILE", std::make_shared<StructType>("MY_IO_FILE", isEmbeddedInOtherType));
  ComposableType *FILE_T = tFILE_T->getTypee()->asComposableType();
  auto IO_MARK = std::make_shared<StructType>("MY_IO_MARK", isEmbeddedInOtherType);

  IO_MARK->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*IO_MARK, IncompleteType::Type::STRUCT)), "_next"));
  IO_MARK->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*FILE_T, IncompleteType::Type::STRUCT)), "_sbuf"));

  FILE_T->addField(ComposableField(std::make_shared<Pointer>(std::move(IO_MARK)), "_markers"));

  FILE_T->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*FILE_T, IncompleteType::Type::STRUCT)), "_chain"));

  Parameter p{std::make_shared<Pointer>(std::move(tFILE_T)), "file"};
  Parameter::Vector pv{};
  pv.emplace_back(std::move(p));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));

  return f;
}

std::string StructFileFromStdioFactory::functionGetFunctionName()
{
  return std::string("structFileFromStdio");
}

std::string StructFileFromStdioFactory::getFilename()
{
   return "structFileFromStdio.h";
}
