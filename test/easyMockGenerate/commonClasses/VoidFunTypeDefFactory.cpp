#include <VoidFunTypeDefFactory.h>

#include <EasyMock_CType.h>
#include <FunctionDeclaration.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>

ElementToMockList VoidFunTypeDefFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  CType intType(CTYPE_INT, "MyType1");
  ConstQualifiedType cIntType{ new CType(CTYPE_INT) };
  Pointer p(cIntType.clone(), "CMyType1");
  CType floatType1(CTYPE_FLOAT, "MyType2");
  CType floatType2(CTYPE_FLOAT, "MyType3");
  Parameter* typeDefPointerParam = new Parameter(p.clone(), "p4");
  Pointer* myType4Type = new Pointer(new ConstQualifiedType(new CType(CTYPE_SHORT, "MyType4")));
  {
    FunctionDeclaration *fd = new FunctionDeclaration(functionGetFunctionName(), VoidReturnValue(false),
            Parameter::Vector({
              new Parameter(intType.clone(), "p1"),
              new Parameter(floatType1.clone(), "p2"),
              new Parameter(floatType2.clone(), "p3"),
              typeDefPointerParam,
              new Parameter(myType4Type, "p5")
            }
    ));
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