#include "VoidFunStructForwardDeclaredFactory.h"

#include <StructType.h>
#include <Pointer.h>
#include <FunctionDeclaration.h>
#include <IncompleteType.h>
#include <ComposableField.h>

ElementToMockList VoidFunStructForwardDeclaredFactory::functionFactoryArray()
{
    ElementToMockList returnedList;
    auto forwardDeclaredParent = std::make_shared<StructType>("forwardDeclaredParent", false);
    auto ptrToForwardDeclaredParent = std::make_shared<Pointer>(std::make_shared<IncompleteType>(*forwardDeclaredParent, IncompleteType::Type::STRUCT));

    auto forwardDeclaredChild = std::make_shared<StructType>("forwardDeclaredChild", false);
    forwardDeclaredChild->addField(ComposableField(std::move(ptrToForwardDeclaredParent), "p"));

    forwardDeclaredParent->addField(ComposableField(std::move(forwardDeclaredChild), "c"));

    Parameter::Vector pv{};
    pv.emplace_back(Parameter(std::move(forwardDeclaredParent), "p"));
    FunctionDeclaration fd (functionGetFunctionName(), VoidReturnValue(), std::move(pv));

    returnedList.push_back(std::move(fd));

    return returnedList;
}

std::string VoidFunStructForwardDeclaredFactory::functionGetFunctionName()
{
    return "voidFunStructForwardDeclared";
}

std::string VoidFunStructForwardDeclaredFactory::getFilename()
{
    return "voidFunStructForwardDeclared.h";
}
