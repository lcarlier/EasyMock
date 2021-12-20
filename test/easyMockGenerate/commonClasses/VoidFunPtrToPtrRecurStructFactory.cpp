#include "VoidFunPtrToPtrRecurStructFactory.h"

#include <StructType.h>
#include <FunctionDeclaration.h>
#include <Pointer.h>
#include <EasyMock_CType.h>
#include <IncompleteType.h>
#include <ComposableField.h>

ElementToMockList VoidFunPtrToPtrRecurStructFactory::functionFactoryArray()
{
  auto getp2pType = []()
  {
    auto t = std::make_shared<StructType>("ptrToPtrStructRecur", false);
    auto pField = std::make_shared<Pointer>(std::make_shared<IncompleteType>(*t, IncompleteType::Type::STRUCT));
    auto p2pField = std::make_shared<Pointer>(pField);
    t->addField(ComposableField(std::move(p2pField), "r"));

    auto pType = std::make_shared<Pointer>(t);
    auto p2pType = std::make_shared<Pointer>(pType);

    return p2pType;
  };
  ElementToMockList returnedList;
  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter(getp2pType(), "s"));
    FunctionDeclaration fd("voidFunPtrToPtrRecurStruct", VoidReturnValue(), std::move(pv));
    returnedList.push_back(std::move(fd));
  }

  {
    FunctionDeclaration fd("ptrToPtrRecurStructFunVoid", ReturnValue(getp2pType()), {});
    returnedList.push_back(std::move(fd));
  }
  {
    auto topS = std::make_shared<StructType>("structFieldptrToPtrStructRecur", false);
    topS->addField(ComposableField(getp2pType(), "f"));

    Parameter::Vector pv{};
    pv.emplace_back(Parameter(std::move(topS), "s"));
    FunctionDeclaration fd("voidFunStructFieldptrToPtrStructRecur", VoidReturnValue(), std::move(pv));
    returnedList.push_back(std::move(fd));
  }
  {
    auto topS = std::make_shared<StructType>("structAnonStructFieldptrToPtrStructRecur", false);
    topS->addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "a"));
    auto anonS = std::make_shared<StructType>("", true);
    anonS->addField(ComposableField(getp2pType(), "r"));
    topS->addField(ComposableField(std::move(anonS), ""));

    Parameter::Vector pv{};
    pv.emplace_back(Parameter(std::move(topS), "s"));
    FunctionDeclaration fd("voidFunStructAnonStructFieldptrToPtrStructRecur", VoidReturnValue(), std::move(pv));

    returnedList.push_back(std::move(fd));
  }
  return returnedList;
}

std::string VoidFunPtrToPtrRecurStructFactory::functionGetFunctionName()
{
  return std::string("voidFunPtrToPtrRecurStruct");
}

std::string VoidFunPtrToPtrRecurStructFactory::getFilename()
{
  return "voidFunPtrToPtrRecurStruct.h";
}
