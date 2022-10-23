#include <VoidFunStructPtrFactory.h>

#include <EasyMockStructHelper.h>

#include <Pointer.h>

std::shared_ptr<FunctionDeclaration> VoidFunStructPtrFactory::functionFactory()
{
  auto s2 = newStructS2Type();
  Parameter p{std::make_shared<Pointer>(std::move(s2)), "s"};
  Parameter::Vector pv{};
  pv.emplace_back(std::move(p));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));

  return f;
}

std::string VoidFunStructPtrFactory::functionGetFunctionName()
{
  return std::string("voidFunStructPtr");
}

std::string VoidFunStructPtrFactory::getFilename()
{
   return "voidFunStructPtr.h";
}
