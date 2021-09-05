#include <VoidFunEnumFactory.h>

#include <FunctionDeclaration.h>
#include <Enum.h>
#include <StructType.h>
#include <Pointer.h>
#include <EasyMock_CType.h>
#include <ComposableField.h>
#include <TypedefType.h>

ElementToMockList VoidFunEnumFactory::functionFactoryArray()
{
  Enum e("enumTestParam");
  e.addEnumValue(1, "ONE");
  e.addEnumValue(2, "TWO");
  ElementToMockList returnedList;
  {
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunEnum", VoidReturnValue(false), Parameter::Vector({new Parameter(e.clone(), "e")}));
    returnedList.push_back(fd);
  }
  {
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunPtrEnum", VoidReturnValue(false), Parameter::Vector({new Parameter(new Pointer(e.clone()), "e")}));
    returnedList.push_back(fd);
  }
  {
    TypedefType te { "t_enumTestRv", new Enum("") };
    Enum& eRv = dynamic_cast<Enum&>(*te.getTypee());
    eRv.addEnumValue(0, "ZERO");
    eRv.addEnumValue(4, "FOUR");
    FunctionDeclaration *fd = new FunctionDeclaration("enumFunVoid", ReturnValue(te.clone()), Parameter::Vector({}));
    returnedList.push_back(fd);
  }
  Enum eStr("enumStruct");
  eStr.addEnumValue(3, "THREE");
  eStr.addEnumValue(5, "FIVE");
  {
    StructType *s = new StructType("structTestEnum", false);
    ComposableField *enumField = new ComposableField(eStr.clone(), "e");
    s->addField(enumField);
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunStructEnum", VoidReturnValue(false), Parameter::Vector({new Parameter(s, "s")}));
    returnedList.push_back(fd);
  }
  {
    TypedefType te { "t_enumStruct", eStr.clone() };
    StructType *s = new StructType("structTestAnonyStructEnum", false);
    s->addField(new ComposableField(new CType(CTYPE_INT), "a"));
    StructType *as = new StructType("", true);
    as->addField(new ComposableField(te.clone(), "e"));
    s->addField(new ComposableField(as, ""));
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunStructAnonStructEnum", VoidReturnValue(false), Parameter::Vector({new Parameter(s, "s")}));

    returnedList.push_back(fd);
  }
  {
    Enum ee {""};
    ee.addEnumValue(9, "NINE");
    ee.addEnumValue(10, "TEN");
    StructType *s = new StructType { "structTestEmbeddedEnum" , false};
    s->addField(new ComposableField{ee.clone(), "embeddedEnum"});
    FunctionDeclaration *fd = new FunctionDeclaration{ "voidFunStructEmbeddedEnumType", VoidReturnValue(false), Parameter::Vector ({new Parameter{s, "s"}})};

    returnedList.push_back(fd);
  }
  {
    FunctionDeclaration *fd = new FunctionDeclaration{ "voidFunUnnamedEnumParam", VoidReturnValue(false), Parameter::Vector ({new Parameter{e.clone(), ""}})};

    returnedList.push_back(fd);
  }
  {
    ReturnValue rv{e.clone()};
    FunctionDeclaration *fd = new FunctionDeclaration{ "enumTest", rv, Parameter::Vector ({})};

    returnedList.push_back(fd);
  }
  {
    Enum onlyRv{"nonDefinedEnum"};

    FunctionDeclaration *fd = new FunctionDeclaration{ "nonDefinedEnumFunVoid", ReturnValue{onlyRv.clone()}, Parameter::Vector({})};

    returnedList.push_back(fd);
  }
  return returnedList;
}

std::string VoidFunEnumFactory::functionGetFunctionName()
{
  return std::string("voidFunEnum");
}

std::string VoidFunEnumFactory::getFilename()
{
  return "voidFunEnum.h";
}
