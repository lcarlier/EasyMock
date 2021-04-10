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

  FunctionDeclaration *fd = getFunPtrDeclaration(0, functionGetFunctionName().c_str(), "", "funPtrType");
  Parameter &p = fd->getFunctionsParameters()[0];

  returnedList.push_back(fd);

  ReturnValue rv2(p.getType()->clone());
  FunctionDeclaration *fd2 = new FunctionDeclaration("TypedefFunPtrVoid", rv2, Parameter::Vector({}));
  returnedList.push_back(fd2);

  FunctionDeclaration *fd3 = getFunPtrDeclaration(4, "intFunStructTypeDefPtrFunField", "typeDefPtrFunField", "funPtrType");
  returnedList.push_back(fd3);

  FunctionDeclaration *fd4 = getFunPtrDeclaration(5, "intFunStructTypeDefPtrAnonFunField", "topAnonymousStructTypeDefPtrFunField", "funPtrType");
  returnedList.push_back(fd4);

  StructType* forwardDecl = new StructType {"forwardDecl", false};
  forwardDecl->addField(new ComposableField {CTYPE_INT, "a"});
  Pointer* pointerIncompleteStructForwardDecl = new Pointer { forwardDecl };
  FunctionType* forwardDeclFunType = new FunctionType {VoidReturnValue(), Parameter::Vector {new Parameter {pointerIncompleteStructForwardDecl, ""}}};
  Pointer* forwardDeclParamFunPtr = new Pointer {forwardDeclFunType};
  TypedefType* forwardDeclParamFunPtrTypeDef = new TypedefType {"forwardDeclParamFunPtr", forwardDeclParamFunPtr};
  FunctionDeclaration *fd5 = new FunctionDeclaration{"voidFunForwardDecl", VoidReturnValue(), Parameter::Vector{new Parameter{forwardDeclParamFunPtrTypeDef, "ptr"}}};
  returnedList.push_back(fd5);

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
