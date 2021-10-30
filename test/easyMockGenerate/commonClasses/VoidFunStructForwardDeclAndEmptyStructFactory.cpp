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
    StructType* fd = new StructType {"funStructForwardDecl", false};
    fd->setForwardDecl(true);
    StructType* es = new StructType { "funStructEmptyStruct", false};
    Parameter* p_fd = new Parameter{new Pointer{fd}, "fd"};
    fd = nullptr;
    Parameter* p_es = new Parameter{es, "es"};
    es = nullptr;
    FunctionDeclaration *f = new FunctionDeclaration{functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({p_fd, p_es})};
    p_fd = nullptr;
    p_es = nullptr;
    returnedList.push_back(f);
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
