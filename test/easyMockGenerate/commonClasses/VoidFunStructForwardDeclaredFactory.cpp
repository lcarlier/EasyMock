#include "VoidFunStructForwardDeclaredFactory.h"

#include <StructType.h>
#include <Pointer.h>
#include <FunctionDeclaration.h>

ElementToMockList VoidFunStructForwardDeclaredFactory::functionFactoryArray()
{
    ElementToMockList returnedList;
    StructType *forwardDeclaredParent = new StructType("forwardDeclaredParent", false);
    Pointer *ptrToForwardDeclaredParent = new Pointer(forwardDeclaredParent);

    StructType *forwardDeclaredChild = new StructType("forwardDeclaredChild", false);
    ComposableField::attributes fAttr = {.arraySize = -1, .isIncompleteTypeField = true};
    forwardDeclaredChild->addField(new ComposableField(ptrToForwardDeclaredParent, "p", fAttr));

    forwardDeclaredParent->addField(new ComposableField(forwardDeclaredChild, "c"));

    FunctionDeclaration *fd = new FunctionDeclaration(functionGetFunctionName(), VoidReturnValue(), Parameter::Vector({new Parameter(forwardDeclaredParent, "p")}));

    returnedList.push_back(fd);

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