#include <VoidFunMultilineFactory.h>

#include <EasyMock_CType.h>
#include <Parameter.h>
#include <FunctionDeclaration.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>

FunctionDeclaration VoidFunMultilineFactory::functionFactory()
{
  Parameter::Vector pv{};
  pv.emplace_back(Parameter{std::make_shared<Pointer>( std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_ULONG))), "a"});
  pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_ULONG), "b"});
  pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_ULONG), "c"});
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));
  return f;
}

std::string VoidFunMultilineFactory::functionGetFunctionName()
{
  return std::string("voidFunMultiline");
}

std::string VoidFunMultilineFactory::getFilename()
{
  return "voidFunMultiline.h";
}
