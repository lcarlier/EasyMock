#include "VoidFunTypedefFunPtrFactory.h"
#include "ComposableType.h"
#include "StructType.h"
#include "ComposableField.h"
#include "TypedefType.h"
#include "IncompleteType.h"
#include "FunctionType.h"
#include "Pointer.h"
#include "EasyMock_CType.h"

#include <FunPtrCommonHelper.h>

ElementToMockList VoidFunTypedefFunPtrFactory::functionFactoryArray()
{
  ElementToMockList returnedList;

  {
    FunctionDeclaration fd = getFunPtrDeclaration(0, functionGetFunctionName().c_str(), "", "funPtrType");
    returnedList.push_back(std::move(fd));
  }

  {
    ReturnValue rv{std::make_shared<TypedefType>("funPtrType", getPointerToFunToTest())};
    FunctionDeclaration fd("TypedefFunPtrVoid", std::move(rv), {});
    returnedList.push_back(std::move(fd));
  }

  {
    FunctionDeclaration fd = getFunPtrDeclaration(4, "intFunStructTypeDefPtrFunField", "typeDefPtrFunField",
                                                  "funPtrType");
    returnedList.push_back(std::move(fd));
  }

  {
    FunctionDeclaration fd = getFunPtrDeclaration(5, "intFunStructTypeDefPtrAnonFunField",
                                                  "topAnonymousStructTypeDefPtrFunField", "funPtrType");
    returnedList.push_back(std::move(fd));
  }

  {
    auto forwardDecl = std::make_shared<StructType>("forwardDecl", false);
    forwardDecl->addField(ComposableField{CTYPE_INT, "a"});
    auto pointerIncompleteStructForwardDecl = std::make_shared<Pointer>(forwardDecl);
    Parameter::Vector pvfd{};
    pvfd.emplace_back(Parameter{std::move(pointerIncompleteStructForwardDecl), ""});
    auto forwardDeclFunType = std::make_shared<FunctionType>(VoidReturnValue(), std::move(pvfd));
    auto forwardDeclParamFunPtr = std::make_shared<Pointer>(forwardDeclFunType);
    auto forwardDeclParamFunPtrTypeDef = std::make_shared<TypedefType>("forwardDeclParamFunPtr", forwardDeclParamFunPtr);
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{std::move(forwardDeclParamFunPtrTypeDef), "ptr"});
    FunctionDeclaration fd5{"voidFunForwardDecl", VoidReturnValue(), std::move(pv)};
    returnedList.push_back(std::move(fd5));
  }

  return returnedList;
}

std::string VoidFunTypedefFunPtrFactory::functionGetFunctionName()
{
  return std::string("voidFunTypedefFunPtr");
}

std::string VoidFunTypedefFunPtrFactory::getFilename()
{
  return "voidFunTypedefFunPtr.h";
}
