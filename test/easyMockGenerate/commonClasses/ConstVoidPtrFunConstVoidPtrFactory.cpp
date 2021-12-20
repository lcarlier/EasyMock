#include <ConstVoidPtrFunConstVoidPtrFactory.h>

#include <ReturnValue.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>

FunctionDeclaration ConstVoidPtrFunConstVoidPtrFactory::functionFactory()
{
  auto getPointerToConstVoid=[]()
  {
    return std::make_shared<Pointer>(std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_VOID)) );
  };
  ReturnValue rv{ getPointerToConstVoid() };

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(getPointerToConstVoid(), "p"));
  FunctionDeclaration f(functionGetFunctionName(), std::move(rv), std::move(pv));
  return f;
}

std::string ConstVoidPtrFunConstVoidPtrFactory::functionGetFunctionName()
{
  return std::string("constVoidPtrFunConstVoidPtr");
}

std::string ConstVoidPtrFunConstVoidPtrFactory::getFilename()
{
  return "constVoidPtrFunConstVoidPtr.h";
}
