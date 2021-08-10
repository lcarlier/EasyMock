#include <VoidFunUnnamedPtrParamFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>

ElementToMockList VoidFunUnnamedPtrParamFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    Parameter *p1 = new Parameter{new CType{CTYPE_INT}, "a"};
    Parameter *p2 = new Parameter{new Pointer{new ConstQualifiedType{new CType{CTYPE_CHAR}}}, ""};
    Parameter *p3 = new Parameter{new CType{CTYPE_INT}, "b"};
    FunctionDeclaration *f = new FunctionDeclaration{functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({p1, p2, p3})};
    p1 = nullptr; //We lost the ownership
    p2 = nullptr; //We lost the ownership
    p3 = nullptr; //We lost the ownership
    returnedList.push_back(f);
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