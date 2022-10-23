#include <IntFunStructPtrIntCharPtrFactory.h>

#include <EasyMockStructHelper.h>

#include <EasyMock_CType.h>
#include <Pointer.h>

std::shared_ptr<FunctionDeclaration> IntFunStructPtrIntCharPtrFactory::functionFactory()
{
  std::shared_ptr<TypeItf> s2 = newStructS2Type();
  Parameter structParam{std::make_shared<Pointer>(std::move(s2)), "s"};
  Parameter::Vector p{};
  p.emplace_back(std::move(structParam));
  p.emplace_back(Parameter(std::make_shared<CType>(CTYPE_INT), "a"));

  p.emplace_back(Parameter(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_CHAR)), "c"));
  auto  f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_INT), std::move(p));
  return f;
}

std::string IntFunStructPtrIntCharPtrFactory::functionGetFunctionName()
{
  return std::string("intFunStructPtrIntCharPtr");
}

std::string IntFunStructPtrIntCharPtrFactory::getFilename()
{
   return "intFunStructPtrIntCharPtr.h";
}
