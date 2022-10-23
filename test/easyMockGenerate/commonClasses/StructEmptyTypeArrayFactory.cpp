#include <StructEmptyTypeArrayFactory.h>
#include <FunctionFactory.h>
#include <ReturnValue.h>
#include <StructType.h>
#include <TypedefType.h>
#include <ConstQualifiedType.h>

ElementToMockList StructEmptyTypeArrayFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    auto emptyType = std::make_shared<StructType>("emptyType", false);
    auto td_emptyType = std::make_shared<TypedefType>("t_emptyType", emptyType);

    auto emptyTypeArray = std::make_shared<StructType>("emptyTypeArray", false);
    emptyTypeArray->addField(ComposableField{emptyType, "f1", {.arraySize = 3}});
    emptyTypeArray->addField(ComposableField{td_emptyType, "f2", {.arraySize = 3}});
    emptyTypeArray->addField(ComposableField{std::make_shared<ConstQualifiedType>(emptyType), "f3", {.arraySize = 3}});
    emptyTypeArray->addField(ComposableField{std::make_shared<ConstQualifiedType>(td_emptyType), "f4", {.arraySize = 3}});

    Parameter::Vector pv{};
    pv.emplace_back(std::move(emptyTypeArray), "p");

    auto f = std::make_shared<FunctionDeclaration>( "funStructEmptyTypeArray", VoidReturnValue(), std::move(pv));

    returnedList.push_back(std::move(f));
  }
  return returnedList;
}

std::string StructEmptyTypeArrayFactory::functionGetFunctionName()
{
  return std::string("funStructEmptyTypeArray");
}

std::string StructEmptyTypeArrayFactory::getFilename()
{
  return "structEmptyTypeArray.h";
}
