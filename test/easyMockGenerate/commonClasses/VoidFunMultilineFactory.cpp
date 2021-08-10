#include <VoidFunMultilineFactory.h>

#include <EasyMock_CType.h>
#include <Parameter.h>
#include <FunctionDeclaration.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>

FunctionDeclaration VoidFunMultilineFactory::functionFactory()
{
  Parameter::Vector p({new Parameter { new Pointer { new ConstQualifiedType {new CType{CTYPE_ULONG}}}, "a"},
                       new Parameter{new CType{CTYPE_ULONG}, "b"},
                       new Parameter{new CType{CTYPE_ULONG}, "c"}});
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), p);
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
