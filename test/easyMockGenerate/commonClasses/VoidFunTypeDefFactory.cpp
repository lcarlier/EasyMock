#include <VoidFunTypeDefFactory.h>

#include <EasyMock_CType.h>
#include <FunctionDeclaration.h>
#include <Pointer.h>

ElementToMockList VoidFunTypeDefFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  CType intType(CTYPE_INT, "MyType1", false);
  CType cIntType(CTYPE_INT, true);
  Pointer p(cIntType.clone(), "CMyType1", false);
  CType floatType1(CTYPE_FLOAT, "MyType2", false);
  CType floatType2(CTYPE_FLOAT, "MyType3", false);
  Parameter* typeDefPointerParam = new Parameter(p.clone(), "p4");

  {
    FunctionDeclaration *fd = new FunctionDeclaration(functionGetFunctionName(), VoidReturnValue(false), Parameter::Vector({new Parameter(intType.clone(), "p1"), new Parameter(floatType1.clone(), "p2"), new Parameter(floatType2.clone(), "p3"), typeDefPointerParam}));
    returnedList.push_back(fd);
  }

  {
    ReturnValue rv(p.clone());
    rv.setDeclareString("CMyType1");
    FunctionDeclaration *fd = new FunctionDeclaration("ptypedefFunVoid", rv, Parameter::Vector({}));
    returnedList.push_back(fd);
  }
  return returnedList;
}

std::string VoidFunTypeDefFactory::functionGetFunctionName()
{
  return std::string("voidFunTypeDef");
}

std::string VoidFunTypeDefFactory::getFilename()
{
  return "voidFunTypeDef.h";
}