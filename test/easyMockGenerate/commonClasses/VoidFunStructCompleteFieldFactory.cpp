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

std::shared_ptr<FunctionDeclaration> VoidFunStructCompleteFieldFactory::functionFactory()
{
  auto forwardDecl2 = std::make_shared<StructType>("forwardDecl2", false);
  auto completeStruct = std::make_shared<StructType>("completeStruct", false);
  forwardDecl2->addField(ComposableField{std::make_shared<ConstQualifiedType>(std::make_shared<IncompleteType>( *completeStruct, IncompleteType::Type::STRUCT)), "c"});
  Parameter::Vector pvFd{};
  pvFd.emplace_back(Parameter { std::make_shared<Pointer>(forwardDecl2) , ""});
  auto ftPtr = std::make_shared<Pointer>( std::make_shared<FunctionType>(VoidReturnValue(), std::move(pvFd)));

  auto forwardDecl3 = std::make_shared<StructType>("forwardDecl3", false);
  forwardDecl3->addField(ComposableField{std::move(ftPtr), "fun"});

  completeStruct->addField(ComposableField{std::make_shared<Pointer>(forwardDecl3), "f"});

  Parameter::Vector pv{};
  pv.emplace_back(Parameter { std::make_shared<Pointer>(std::make_shared<ConstQualifiedType>(std::move(completeStruct))), "fp"});

  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), VoidReturnValue(), std::move(pv));
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
