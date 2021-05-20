#include <VoidFunStructCompleteFieldFactory.h>

#include <Parameter.h>
#include <StructType.h>
#include <Pointer.h>
#include <EasyMock_CType.h>
#include <IncompleteType.h>
#include <ComposableField.h>
#include <FunctionDeclaration.h>
#include <FunctionType.h>
#include <ConstQualifiedType.h>

FunctionDeclaration VoidFunStructCompleteFieldFactory::functionFactory()
{
  StructType *forwardDecl2 = new StructType {"forwardDecl2", false};
  StructType *completeStruct = new StructType {"completeStruct", false};
  forwardDecl2->addField(new ComposableField{ new ConstQualifiedType {new IncompleteType { *completeStruct, IncompleteType::Type::STRUCT}}, "c"});
  Pointer *ftPtr = new Pointer { new FunctionType{VoidReturnValue(), Parameter::Vector {new Parameter { new Pointer{forwardDecl2} , ""}}}};

  StructType *forwardDecl3 = new StructType {"forwardDecl3", false};
  forwardDecl3->addField(new ComposableField{ftPtr, "fun"});

  completeStruct->addField(new ComposableField{new Pointer {forwardDecl3}, "f"});

  Parameter::Vector p({new Parameter { new Pointer {new ConstQualifiedType{ completeStruct }}, "fp"}});

  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), p);
  return f;
}

std::string VoidFunStructCompleteFieldFactory::functionGetFunctionName()
{
  return std::string("voidFunStructCompleteField");
}

std::string VoidFunStructCompleteFieldFactory::getFilename()
{
  return "voidFunStructCompleteField.h";
}

