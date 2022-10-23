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
  auto getOneTwoEnumToTest = []()
  {
    auto e = std::make_shared<Enum>("enumTestParam");
    e->addEnumValue(1, "ONE");
    e->addEnumValue(2, "TWO");

    return e;
  };

  auto getThreeFiveToTest=[]()
  {
    auto eStr = std::make_shared<Enum>("enumStruct");
    eStr->addEnumValue(3, "THREE");
    eStr->addEnumValue(5, "FIVE");

    return eStr;
  };
  ElementToMockList returnedList;
  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter(getOneTwoEnumToTest(), "e"));
    auto fd = std::make_shared<FunctionDeclaration>("voidFunEnum", VoidReturnValue(false), std::move(pv));
    returnedList.push_back(std::move(fd));
  }
  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter(std::make_shared<Pointer>(
      getOneTwoEnumToTest()), "e"));
    auto fd = std::make_shared<FunctionDeclaration>("voidFunPtrEnum", VoidReturnValue(false), std::move(pv));
    returnedList.push_back(std::move(fd));
  }
  {
    auto te = std::make_shared<TypedefType>( "t_enumTestRv", std::make_shared<Enum>("") );
    Enum& eRv = *te->getTypee()->asEnum();
    eRv.addEnumValue(0, "ZERO");
    eRv.addEnumValue(4, "FOUR");
    auto fd = std::make_shared<FunctionDeclaration>("enumFunVoid", ReturnValue(std::move(te)), Parameter::Vector {});
    returnedList.push_back(std::move(fd));
  }
  {
    auto s = std::make_shared<StructType>("structTestEnum", false);
    s->addField(ComposableField(getThreeFiveToTest(), "e"));
    Parameter::Vector pv{};
    pv.emplace_back(Parameter(std::move(s), "s"));
    auto fd = std::make_shared<FunctionDeclaration>("voidFunStructEnum", VoidReturnValue(false), std::move(pv));
    returnedList.push_back(std::move(fd));
  }
  {
    auto te = std::make_shared<TypedefType>( "t_enumStruct", getThreeFiveToTest() );
    auto s = std::make_shared<StructType>("structTestAnonyStructEnum", false);
    s->addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "a"));
    auto as = std::make_shared<StructType>("", true);
    as->addField(ComposableField(std::move(te), "e"));
    s->addField(ComposableField(std::move(as), ""));

    Parameter::Vector pv{};
    pv.emplace_back(Parameter(std::move(s), "s"));
    auto fd = std::make_shared<FunctionDeclaration>("voidFunStructAnonStructEnum", VoidReturnValue(false), std::move(pv));

    returnedList.push_back(std::move(fd));
  }
  {
    auto ee = std::make_shared<Enum>("");
    ee->addEnumValue(9, "NINE");
    ee->addEnumValue(10, "TEN");
    auto s = std::make_shared<StructType>( "structTestEmbeddedEnum" , false);
    s->addField(ComposableField{std::move(ee), "embeddedEnum"});

    Parameter::Vector pv{};
    pv.emplace_back(Parameter{std::move(s), "s"});
    auto fd = std::make_shared<FunctionDeclaration>( "voidFunStructEmbeddedEnumType", VoidReturnValue(false), std::move(pv));

    returnedList.push_back(std::move(fd));
  }
  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{getOneTwoEnumToTest(), ""});
    auto fd = std::make_shared<FunctionDeclaration>( "voidFunUnnamedEnumParam", VoidReturnValue(false), std::move(pv));

    returnedList.push_back(std::move(fd));
  }
  {
    ReturnValue rv{getOneTwoEnumToTest()};
    auto fd = std::make_shared<FunctionDeclaration>( "enumTest", std::move(rv), Parameter::Vector {});

    returnedList.push_back(std::move(fd));
  }
  {
    auto onlyRv = std::make_shared<Enum>("nonDefinedEnum");

    auto fd = std::make_shared<FunctionDeclaration>( "nonDefinedEnumFunVoid", ReturnValue{std::move(onlyRv)}, Parameter::Vector {});

    returnedList.push_back(std::move(fd));
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
