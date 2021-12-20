#include <VoidFunUnnamedPtrParamFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>

ElementToMockList VoidFunUnnamedPtrParamFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_INT), "a"});
    pv.emplace_back(Parameter{std::make_shared<Pointer>(std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_CHAR))), ""});
    pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_INT), "b"});
    FunctionDeclaration f{functionGetFunctionName(), VoidReturnValue(), std::move(pv)};
    returnedList.push_back(std::move(f));
  }
  return returnedList;
}

std::string VoidFunUnnamedPtrParamFactory::functionGetFunctionName()
{
  return std::string("voidFunUnnamedPtrParam");
}

std::string VoidFunUnnamedPtrParamFactory::getFilename()
{
  return "voidFunUnnamedPtrParam.h";
}
