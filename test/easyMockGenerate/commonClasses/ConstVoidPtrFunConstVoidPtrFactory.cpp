#include <ConstVoidPtrFunConstVoidPtrFactory.h>

#include <ReturnValue.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>

FunctionDeclaration ConstVoidPtrFunConstVoidPtrFactory::functionFactory()
{
  Pointer pointerToConstVoid{ new ConstQualifiedType(new CType(CTYPE_VOID)) };
  ReturnValue rv { pointerToConstVoid.clone() };

  Parameter *param = new Parameter(pointerToConstVoid.clone(), "p");
  
  FunctionDeclaration f(functionGetFunctionName(), rv, Parameter::Vector({param}));
  param = nullptr;
  return f;
}

FunctionDeclaration* ConstVoidPtrFunConstVoidPtrFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string ConstVoidPtrFunConstVoidPtrFactory::functionGetFunctionName()
{
  return std::string("constVoidPtrFunConstVoidPtr");
}

std::string ConstVoidPtrFunConstVoidPtrFactory::getFilename()
{
  return "constVoidPtrFunConstVoidPtr.h";
}
