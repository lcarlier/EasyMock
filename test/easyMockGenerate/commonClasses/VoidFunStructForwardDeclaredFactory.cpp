#include "VoidFunStructForwardDeclaredFactory.h"

#include <StructType.h>
#include <Pointer.h>
#include <FunctionDeclaration.h>
#include <IncompleteType.h>
#include <ComposableField.h>

ElementToMockList VoidFunStructForwardDeclaredFactory::functionFactoryArray()
{
    ElementToMockList returnedList;
    StructType *forwardDeclaredParent = new StructType("forwardDeclaredParent", false);
    Pointer *ptrToForwardDeclaredParent = new Pointer(new IncompleteType(*forwardDeclaredParent));

    StructType *forwardDeclaredChild = new StructType("forwardDeclaredChild", false);
    forwardDeclaredChild->addField(new ComposableField(ptrToForwardDeclaredParent, "p"));

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
