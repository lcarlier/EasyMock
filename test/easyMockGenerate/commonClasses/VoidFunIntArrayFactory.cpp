#include <VoidFunIntArrayFactory.h>

#include <EasyMock_CType.h>
#include <EasyMockStructHelper.h>
#include <Pointer.h>

std::shared_ptr<FunctionDeclaration> VoidFunIntArrayFactory::functionFactory()
{
  //Even though an array is passed as parameter. C sees it as a pointer
  Parameter::Vector p{};
  p.emplace_back(Parameter(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)), "array"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(p));
  return f;
}

std::string VoidFunIntArrayFactory::functionGetFunctionName()
{
  return std::string("voidFunIntArray");
}

std::string VoidFunIntArrayFactory::getFilename()
{
   return "voidFunIntArray.h";
}
