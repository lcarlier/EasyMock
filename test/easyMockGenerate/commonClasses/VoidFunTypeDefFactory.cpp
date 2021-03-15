#include <VoidFunTypeDefFactory.h>

#include <EasyMock_CType.h>
#include <FunctionDeclaration.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>
#include <TypedefType.h>

ElementToMockList VoidFunTypeDefFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  TypedefType intType { "MyType1", new CType(CTYPE_INT) };
  ConstQualifiedType cIntType{ new CType(CTYPE_INT) };
  TypedefType p { "CMyType1", new Pointer(cIntType.clone()) };
  TypedefType floatType1 { "MyType2", new CType(CTYPE_FLOAT) };
  TypedefType floatType2 { "MyType3", new CType(CTYPE_FLOAT) };
  Parameter* typeDefPointerParam = new Parameter(p.clone(), "p4");
  Pointer* myType4Type = new Pointer(new ConstQualifiedType(new TypedefType("MyType4", new CType(CTYPE_SHORT))));
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