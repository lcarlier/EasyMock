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
  ElementToMockList returnedList;
  {
    Enum e("enumTestParam");
    e.addEnumValue(1, "ONE");
    e.addEnumValue(2, "TWO");
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunEnum", VoidReturnValue(false), Parameter::Vector({new Parameter(e.clone(), "e")}));
    returnedList.push_back(fd);
  }
  {
    Enum e("enumTestParam");
    e.addEnumValue(1, "ONE");
    e.addEnumValue(2, "TWO");
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunPtrEnum", VoidReturnValue(false), Parameter::Vector({new Parameter(new Pointer(e.clone()), "e")}));
    returnedList.push_back(fd);
  }
  {
    TypedefType te { "t_enumTestRv", new Enum("") };
    Enum& e = dynamic_cast<Enum&>(*te.getTypee());
    e.addEnumValue(0, "ZERO");
    e.addEnumValue(4, "FOUR");
    FunctionDeclaration *fd = new FunctionDeclaration("enumFunVoid", ReturnValue(te.clone()), Parameter::Vector({}));
    returnedList.push_back(fd);
  }
  Enum e("enumStruct");
  e.addEnumValue(3, "THREE");
  e.addEnumValue(5, "FIVE");
  {
    StructType *s = new StructType("structTestEnum", false);
    ComposableField *enumField = new ComposableField(e.clone(), "e");
    s->addField(enumField);
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunStructEnum", VoidReturnValue(false), Parameter::Vector({new Parameter(s, "s")}));
    returnedList.push_back(fd);
  }
  {
    TypedefType te { "t_enumStruct", e.clone() };
    StructType *s = new StructType("structTestAnonyStructEnum", false);
    s->addField(new ComposableField(new CType(CTYPE_INT), "a"));
    StructType *as = new StructType("", true);
    as->addField(new ComposableField(te.clone(), "e"));
    s->addField(new ComposableField(as, ""));
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunStructAnonStructEnum", VoidReturnValue(false), Parameter::Vector({new Parameter(s, "s")}));

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
