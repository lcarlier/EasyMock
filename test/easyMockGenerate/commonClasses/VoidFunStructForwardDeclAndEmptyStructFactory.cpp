#include <VoidFunStructForwardDeclAndEmptyStructFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>
#include <StructType.h>

ElementToMockList VoidFunStructForwardDeclAndEmptyStructFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    auto fd = std::make_shared<StructType>("funStructForwardDecl", false);
    fd->setForwardDecl(true);
    auto es = std::make_shared<StructType>("funStructEmptyStruct", false);
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{std::make_shared<Pointer>(std::move(fd)), "fd"});
    pv.emplace_back(Parameter{std::move(es), "es"});
    auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), VoidReturnValue(), std::move(pv));
    returnedList.push_back(std::move(f));
  }
  return returnedList;
}

std::string VoidFunStructForwardDeclAndEmptyStructFactory::functionGetFunctionName()
{
  return std::string("voidFunStructForwardDeclAndEmptyStruct");
}

std::string VoidFunStructForwardDeclAndEmptyStructFactory::getFilename()
{
  return "voidFunStructForwardDeclAndEmptyStruct.h";
}
